#include "include.h"
/*==================================================================================
	CH SHELL 是一个灵活的串口组件，利用它可以用串口调用程序中任何的参数 V1.0
===================================================================================*/
//这里包含你的串口驱动头文件 

//1个demo 测试函数
u8 CHS_TestFun(u8* str1,u8 num1,u8* str2,u8 num2,u8* str3)
{
	printf("进入TestFun函数\r\n");
	printf("参数1: %s\r\n",str1);
	printf("参数2: %d\r\n",num1);
	printf("参数3: %s\r\n",str2);
	printf("参数4: %d\r\n",num2);
	printf("参数5: %s\r\n",str3);
	return 100;
}

//函数管理列表
//添加希望管理的函数
struct T_CHS_FunTab CHS_FunTab[]=
{
	(u32*) CHS_TestFun,         "u8 CHS_TestFun(u8* str1,u8 num1,u8* str2,u8 num2,u8* str3)", //测试函数
        (void*) PrintAD,            "void PrintAD(void)",
        (void*) SetSteerAngle,      "void SetSteerAngle(int16 Angle)",
        (void*) SetMotorSpeed,      "void SetMotorSpeed(int16 nSpeed)", 
        (void*) SetPID,             "void SetPID(float p,float i,float d)"
	//(void*) SPILCD_DrawLine,     "SPILCD_DrawLine(u16 x1,u16 y1,u16 x2,u16 y2)",               //测试函数
};	

//Shell系统初始化
//实现 初始化系统系统
void CHS_Init(void)
{
		//在这里包含你的串口初始化函数
		//初始化调试串口 //默认 UART3 115200 在UART.H中定义
}

//CHSHELL控制管理器 无需修改
struct T_CHS_DEV CHS_Dev=
{
	  CHS_FunTab,
		CHS_Init,
		0,
		sizeof(CHS_FunTab)/sizeof(struct T_CHS_FunTab),//函数数量
};


