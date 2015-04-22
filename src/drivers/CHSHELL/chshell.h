#ifndef __CHSHELL_H_
#define __CHSHELL_H_	
#include "common.h"
//�ض��峣�����ݱ�������  
#define MAX_FNAME_LEN 	30	 //��������󳤶ȣ�Ӧ������Ϊ��С����������ĳ��ȡ�	
#define MAX_PARM 		    10	   //���Ϊ10������ ,�޸Ĵ˲���,�����޸�usmart_exe��֮��Ӧ.
#define PARM_LEN 		    200	 //���в���֮�͵ĳ��Ȳ�����PARM_LEN���ֽ�,ע�⴮�ڽ��ղ���Ҫ��֮��Ӧ(��С��PARM_LEN)

//����������Ϣ�ṹ��
struct T_CHS_PInfo
{
	u8 Type[MAX_PARM];    //���� 1 ���� 2 �ַ���
        u32 ParmData[MAX_PARM];    //������Ϣ:����������Ͳ������Ų�����ֵ��������ַ����Ͳ������Ų�����ʼ��ַ(ָ��ParmBuf)
	u8 OffSet[MAX_PARM];  //�������ַ�����ƫ��
	u8 Long[MAX_PARM];    //�����ĳ���
        u8 ParmBuf[PARM_LEN];     //�ַ����Ͳ�������ڴ���
};

//�������б�	 
struct T_CHS_FunTab
{
	void* func;			//����ָ��
	const u8* name;		//������(���Ҵ�)	 
};
//CHS_SHELL������
struct T_CHS_DEV
{
		struct T_CHS_FunTab *funs;	//������ָ��
		void (*init)(void);				//��ʼ��
	  u16 USART_STAT;
	  u8 fnum; //��������
	  u8 pnum; //��������
	  u8 id;   //����ID��
		u8 USART_BUF[MAX_FNAME_LEN+PARM_LEN];         //���ڽ��ջ�����
		struct T_CHS_PInfo PInfo;                          //������Ϣ�ṹ��
};
extern struct T_CHS_DEV CHS_Dev;				//��usmart_config.c���涨��
extern void CHS_Rev1(u8 ch);                   //��ֲ���� ����Ĵ��ڽ����ж��е���
u8  CHS_Scan(void);                     //CHSִ��������
void CHS_Init(void);                    //CHS ��ʼ������ 
#endif
