#ifndef ELLIPTIC_CURVE_H
#define ELLIPTIC_CURVE_H

#include <string.h>
#include <stdio.h>
#include "miracl.h"

/*
SM2��Բ����Ĭ�ϲ���
*/
#define SM2_P "FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFF"
#define SM2_N "FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFF7203DF6B21C6052B53BBF40939D54123"
#define SM2_A "FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFC"
#define SM2_B "28E9FA9E9D9F5E344D5A9E4BCF6509A7F39789F515AB8F92DDBCBD414D940E93"
#define SM2_GX "32C4AE2C1F1981195F9904466A39C9948FE30BBFF2660BE1715A4589334C74C7"
#define SM2_GY "BC3736A2F4F6779C59BDCEE36B692153D0A9877CC62A474002DF32E52139F0A0"

/*
��ʼ��miraclϵͳʱ�����ֵ�λ��
*/
#define NUMBERSIZE 512

/*
��ʼ��miraclϵͳʱ�Ĵ����ֽ���
*/
#define NUMBERBASE 16

/*
ϵͳ�Ĳ���
*/
typedef struct {
    big a, b, p, Gx, Gy, n ;
    epoint* G;
    miracl* mip;
}sm2systemparameter;
extern sm2systemparameter* sm2system;


/**************************************
*
* �ⲿ�ӿ�
*
**************************************/

/*
@brief sm2SystemInit        ��ʼ��SM2ϵͳ,�����ȳ�ʼ��ϵͳ����ܵ���SM2��SM3�㷨��صĺ���
@return char*               ������Ϣ
*/
extern char* sm2SystemInit(void);

/*
@brief sm2SystemKill        �ر�SM2ϵͳ
@return char*               ������Ϣ
*/
extern char* sm2SystemKill(void);

/*
@brief test					���Ժ���
@param a					��һ������
@param b					�ڶ�������
@return int					����2�����ĺ�
*/
extern int test(int, int);

/**************************************
* 
* ��������
* 
**************************************/

/*
@brief strcat_sm2           �ַ���ƴ��
@param char* str1           ��һ��ƴ���ַ���
@param int len              ƴ�Ӻ���ַ�������
@param char* str2           �ڶ���ƴ�ӵ��ַ���
@return int                 ����״̬
*/
extern int strcat_sm2(char*, int, char*);

/*
@brief fopen_sm2            �ļ�����
@param FILE** file          �ļ�ָ��
@param char* path           �ļ�·��
@param char* mode           ����ģʽ
return int                  ����״̬
*/
extern int fopen_sm2(FILE**, char*, char*);



#endif // !ELLIPTIC_CURVE_H

