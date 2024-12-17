package main

import (
	"crypto/rand"
	"net/http"
	"sync"

	"github.com/gin-gonic/gin"
	"github.com/tjfoc/gmsm/sm2"
	"github.com/tjfoc/gmsm/x509"
)

// UserRegistrationRequest 是注册请求的数据结构
type UserRegistrationRequest struct {
	Username string `json:"username" binding:"required"`
	Password string `json:"password" binding:"required"`
}

// UserLoginRequest 是登录请求的数据结构
type UserLoginRequest struct {
	Username string `json:"username" binding:"required"`
	Password string `json:"password" binding:"required"`
	Sign     []byte `json:"sign" binding:"required"`
}

// UserSignRequest 是签名请求的数据结构
type UserSignRequest struct {
	Username      string `json:"username" binding:"required"`
	Password      string `json:"password" binding:"required"`
	PrivatekeyPem string `json:"privatekeypem" binding:"required"`
}

// UserInfo 存储用户信息
type UserInfo struct {
	Username     string
	Password     string // 注意：实际应用中密码不应该这样存储，应使用哈希值
	PublickeyPem string
}

// userDB 模拟数据库，存储用户信息
var userDB = make(map[string]UserInfo)
var dbMutex = &sync.Mutex{} // 用于同步访问 userDB

func main() {
	router := gin.Default()

	// 允许所有CORS请求，适用于开发环境
	router.Use(func(c *gin.Context) {
		c.Writer.Header().Set("Access-Control-Allow-Origin", "*")
		c.Writer.Header().Set("Access-Control-Allow-Credentials", "true")
		c.Writer.Header().Set("Access-Control-Allow-Headers", "Content-Type, Content-Length, Accept-Encoding, X-CSRF-Token, Authorization, accept, origin, Cache-Control, X-Requested-With")
		c.Writer.Header().Set("Access-Control-Allow-Methods", "POST, OPTIONS, GET, PUT")

		if c.Request.Method == "OPTIONS" {
			c.AbortWithStatus(204)
			return
		}

		c.Next()
	})

	// 注册路由
	router.POST("/register", registerHandler)
	router.POST("/login", loginHandler)
	router.POST("/sign", userSign)

	// 启动服务
	router.Run(":8080")
}

func registerHandler(c *gin.Context) {
	// 绑定请求数据到 UserRegistrationRequest 结构体
	var req UserRegistrationRequest
	if err := c.ShouldBindJSON(&req); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	// 生成 SM2 密钥对
	privateKey, err := sm2.GenerateKey(rand.Reader)
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": "无法生成密钥对"})
		return
	}

	// 将公钥序列化为 PEM 格式
	pubPem, err := x509.WritePublicKeyToPem(&privateKey.PublicKey)
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": "无法序列化公钥"})
		return
	}

	// 将私钥序列化为 PEM 格式，并使用用户提供的密码加密
	priPem, err := x509.WritePrivateKeyToPem(privateKey, []byte(req.Password))
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": "无法序列化私钥"})
		return
	}

	// 使用互斥锁确保线程安全地更新 userDB
	dbMutex.Lock()
	userDB[req.Username] = UserInfo{
		Username:     req.Username,
		Password:     req.Password, // 注意：实际应用中应该存储密码的哈希值
		PublickeyPem: string(pubPem),
	}
	dbMutex.Unlock()

	// 实际应用中不应该将私钥返回给用户，这里仅作为演示
	c.JSON(http.StatusOK, gin.H{
		"message":       "注册成功",
		"username":      req.Username,
		"privatekeypem": string(priPem),
	})
}

func userSign(c *gin.Context) {
	var req UserSignRequest
	if err := c.ShouldBindJSON(&req); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}
	msg := []byte(req.Username + req.Password)
	PriPemBytes := []byte(req.PrivatekeyPem)
	pwd := []byte(req.Password)
	privateKey, err := x509.ReadPrivateKeyFromPem(PriPemBytes, pwd)
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": "无法读取私钥"})
	}
	sign, err := privateKey.Sign(rand.Reader, msg, nil)
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": "签名失败"})
	}

	c.JSON(http.StatusOK, gin.H{
		"message": "签名成功",
		"sign":    sign,
	})
}

func loginHandler(c *gin.Context) {
	// 绑定请求数据到 UserLoginRequest 结构体
	var req UserLoginRequest
	if err := c.ShouldBindJSON(&req); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
		return
	}

	// 使用互斥锁确保线程安全地访问 userDB
	dbMutex.Lock()
	userInfo, exists := userDB[req.Username]
	dbMutex.Unlock()

	if !exists {
		c.JSON(http.StatusUnauthorized, gin.H{"error": "用户不存在"})
		return
	}

	// 检查密码是否匹配（注意：实际应用中应比较密码的哈希值）
	if req.Password != userInfo.Password {
		c.JSON(http.StatusUnauthorized, gin.H{"error": "密码错误"})
		return
	}

	//验签
	publicKey, err := x509.ReadPublicKeyFromPem([]byte(userInfo.PublickeyPem))
	if err != nil {
		c.JSON(http.StatusInternalServerError, gin.H{"error": "解析公钥失败"})
	}
	msg := []byte(req.Username + req.Password)
	verify := publicKey.Verify(msg, req.Sign)
	if verify {
		c.JSON(http.StatusOK, gin.H{
			"message":   "登录成功",
			"username":  userInfo.Username,
			"publicKey": userInfo.PublickeyPem,
		})
	} else {
		c.JSON(http.StatusOK, gin.H{
			"message": "登录失败",
		})
	}

}
