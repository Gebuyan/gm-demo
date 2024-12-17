#ifndef SM3_H
#define SM3_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "elliptic_curve.h"

#define SM3_INPUT_BIT 512
#define SM3_OUTPUT_BIT 256

/**************************************
*
* 工具函数
*
**************************************/

/*
@brief sm3			SM3杂凑算法
@param message		大小小于512比特的字符串
@return char*		256比特大小的杂凑值(字符串形式)	
*/
extern char* sm3(char*);

/*
@brief sm3ToBig		SM3杂凑算法
@param message		大小小于512比特的字符串
@return char*		256比特大小的杂凑值(big结构体)
*/
extern big sm3ToBig(char*);

#endif

