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
* ���ߺ���
*
**************************************/

/*
@brief sm3			SM3�Ӵ��㷨
@param message		��СС��512���ص��ַ���
@return char*		256���ش�С���Ӵ�ֵ(�ַ�����ʽ)	
*/
extern char* sm3(char*);

/*
@brief sm3ToBig		SM3�Ӵ��㷨
@param message		��СС��512���ص��ַ���
@return char*		256���ش�С���Ӵ�ֵ(big�ṹ��)
*/
extern big sm3ToBig(char*);

#endif

