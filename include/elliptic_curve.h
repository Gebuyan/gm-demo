#ifndef ELLIPTIC_CURVE_H
#define ELLIPTIC_CURVE_H

#include <string.h>
#include <stdio.h>
#include "miracl.h"

/*
SM2椭圆曲线默认参数
*/
#define SM2_P "FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFF"
#define SM2_N "FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFF7203DF6B21C6052B53BBF40939D54123"
#define SM2_A "FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFC"
#define SM2_B "28E9FA9E9D9F5E344D5A9E4BCF6509A7F39789F515AB8F92DDBCBD414D940E93"
#define SM2_GX "32C4AE2C1F1981195F9904466A39C9948FE30BBFF2660BE1715A4589334C74C7"
#define SM2_GY "BC3736A2F4F6779C59BDCEE36B692153D0A9877CC62A474002DF32E52139F0A0"

/*
初始化miracl系统时大数字的位数
*/
#define NUMBERSIZE 512

/*
初始化miracl系统时的大数字进制
*/
#define NUMBERBASE 16

/*
系统的参数
*/
typedef struct {
    big a, b, p, Gx, Gy, n ;
    epoint* G;
    miracl* mip;
}sm2systemparameter;
extern sm2systemparameter* sm2system;


/**************************************
*
* 外部接口
*
**************************************/

/*
@brief sm2SystemInit        初始化SM2系统,必须先初始化系统后才能调用SM2和SM3算法相关的函数
@return char*               错误信息
*/
extern char* sm2SystemInit(void);

/*
@brief sm2SystemKill        关闭SM2系统
@return char*               错误信息
*/
extern char* sm2SystemKill(void);

/*
@brief test					测试函数
@param a					第一个加数
@param b					第二个加数
@return int					返回2个数的和
*/
extern int test(int, int);

/**************************************
* 
* 条件编译
* 
**************************************/

/*
@brief strcat_sm2           字符串拼接
@param char* str1           第一个拼接字符串
@param int len              拼接后的字符串长度
@param char* str2           第二个拼接的字符串
@return int                 错误状态
*/
extern int strcat_sm2(char*, int, char*);

/*
@brief fopen_sm2            文件访问
@param FILE** file          文件指针
@param char* path           文件路径
@param char* mode           访问模式
return int                  错误状态
*/
extern int fopen_sm2(FILE**, char*, char*);



#endif // !ELLIPTIC_CURVE_H

