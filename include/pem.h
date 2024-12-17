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
* ���ߺ���
* 
**************************************/

/*
@brief writePemFile         дһ��pem�ļ�
@param path                 ·��
@param mode                 ��˽Կ��Ϣ
@param key                  ��Ҫ�������Կ
@return int                 ����״̬
*/
extern int writePemFile(char*, int, char*);

/*
@brief writePemFile         ��һ��pem�ļ�
@param path                 ·��
@param mode                 ��˽Կ��Ϣ
@param key                  ��ȡ�õ�����Կ�ַ���
@return int                 ����״̬
*/
extern int readPemFile(char*, int, char*);

/*
@brief base64_encode		����base64����
@param str					�����������
@return char*				����������
*/
extern unsigned char* base64Encode(unsigned char*);

/*
@brief base64_encode		����base64����
@param str					�����������
@return char*				����������
*/
extern unsigned char* bae64Decode(unsigned char*);




#endif // !PEM_H





