package test

import (
	"crypto/rand"
	"fmt"
	"github.com/tjfoc/gmsm/sm2"
	"testing"
)

func TestName(t *testing.T) {
	//sm3测试
	//data := []byte("The quick brown fox jumps over the lazy dog")
	//hash := sm3.Sm3Sum(data)
	//fmt.Printf("SM3 Hash: %x\n", hash)

	//sm4测试
	//// 16字节的密钥
	//key := []byte("1234567890abcdef")
	//// 16字节的原文
	//data := []byte("hello, world!1234")
	//
	//// 加密
	//cipherText, err := sm4.Sm4Ecb(key, data, true)
	//if err != nil {
	//	panic(err)
	//}
	//fmt.Printf("Encrypted: %x\n", cipherText)
	//
	//// 解密
	//plainText, err := sm4.Sm4Ecb(key, cipherText, false)
	//if err != nil {
	//	panic(err)
	//}
	//fmt.Printf("Decrypted: %s\n", plainText)

	//sm2测试
	// 生成SM2密钥对
	privateKey, err := sm2.GenerateKey(rand.Reader) // 生成密钥对
	if err != nil {
		panic(err)
	}
	publicKey := &privateKey.PublicKey
	fmt.Println("publicKey:", publicKey)

	// 待签名的消息
	message := []byte("hello, world")

	// 签名
	sign, err := privateKey.Sign(rand.Reader, message, nil) // 签名
	if err != nil {
		panic(err)
	}
	fmt.Printf("Signature: %x\n", sign)

	// 验证签名
	verify := publicKey.Verify(message, sign)
	fmt.Printf("Verify result: %v\n", verify)
}
