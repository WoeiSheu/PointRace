#include "include.h"
/*==================================================================================
	CH SHELL ��һ�����Ĵ�������������������ô��ڵ��ó������κεĲ��� V1.0
===================================================================================*/
//���������Ĵ�������ͷ�ļ� 

//1��demo ���Ժ���
u8 CHS_TestFun(u8* str1,u8 num1,u8* str2,u8 num2,u8* str3)
{
	printf("����TestFun����\r\n");
	printf("����1: %s\r\n",str1);
	printf("����2: %d\r\n",num1);
	printf("����3: %s\r\n",str2);
	printf("����4: %d\r\n",num2);
	printf("����5: %s\r\n",str3);
	return 100;
}

//���������б�
//���ϣ������ĺ���
struct T_CHS_FunTab CHS_FunTab[]=
{
	(u32*) CHS_TestFun,         "u8 CHS_TestFun(u8* str1,u8 num1,u8* str2,u8 num2,u8* str3)", //���Ժ���
        (void*) PrintAD,            "void PrintAD(void)",
        (void*) SetSteerAngle,      "void SetSteerAngle(int16 Angle)",
        (void*) SetMotorSpeed,      "void SetMotorSpeed(int16 nSpeed)", 
        (void*) SetPID,             "void SetPID(float p,float i,float d)"
	//(void*) SPILCD_DrawLine,     "SPILCD_DrawLine(u16 x1,u16 y1,u16 x2,u16 y2)",               //���Ժ���
};	

//Shellϵͳ��ʼ��
//ʵ�� ��ʼ��ϵͳϵͳ
void CHS_Init(void)
{
		//�����������Ĵ��ڳ�ʼ������
		//��ʼ�����Դ��� //Ĭ�� UART3 115200 ��UART.H�ж���
}

//CHSHELL���ƹ����� �����޸�
struct T_CHS_DEV CHS_Dev=
{
	  CHS_FunTab,
		CHS_Init,
		0,
		sizeof(CHS_FunTab)/sizeof(struct T_CHS_FunTab),//��������
};


