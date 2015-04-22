#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include  "common.h"

/*
 * Include 用户自定义的头文件
 */


#include  "gpio.h"       //IO口操作
#include  "CarUI.H"      //人机交互
//#include  "chshell.h"    //串口调试助手
#include  "exti.h"       //EXTI外部GPIO中断
#include  "uart.h"       //串口
#include  "lptmr.h"      //低功耗定时器(延时)
#include  "adc.h"
#include  "FTM.h"
#include  "pit.h"  

#endif  //__INCLUDE_H__
