#ifndef PEM_H
#define PEM_H

#include <stdio.h>
#include <stdlib.h>  
#include <string.h>
#include "elliptic_curve.h"

#define PUBLIC 0
#define PRIVATE 1
#define PUBLIC_BEGIN_LEN 26
#define PUBLIC_END_LEN 24

/**************************************
* 
* 工具函数
* 
**************************************/

/*
@brief writePemFile         写一个pem文件
@param path                 路径
@param mode                 公私钥信息
@param key                  需要保存的密钥
@return int                 错误状态
*/
extern int writePemFile(char*, int, char*);

/*
@brief writePemFile         读一个pem文件
@param path                 路径
@param mode                 公私钥信息
@param key                  读取得到的密钥字符串
@return int                 错误状态
*/
extern int readPemFile(char*, int, char*);

/*
@brief base64_encode		进行base64编码
@param str					待编码的数据
@return char*				编码后的数据
*/
extern unsigned char* base64Encode(unsigned char*);

/*
@brief base64_encode		进行base64解码
@param str					待解码的数据
@return char*				解码后的数据
*/
extern unsigned char* bae64Decode(unsigned char*);




#endif // !PEM_H





