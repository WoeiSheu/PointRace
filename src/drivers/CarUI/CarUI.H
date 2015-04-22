#ifndef __UI_H__
#define __UI_H__
 
#include "Device.h"

/****************************外部使用****************************/
 void InitUI(void); 
 void ShowNum(void);
 void ScopeShow();
 void SetScopeCh(uint8 n);
 void SetScope(int16 num,uint8 id);
 
 
 void Display(int num);
 void LED_print(uint8 num,uint8 nID);    
 void Test(void);  
 
#define Minus 10
 
#endif  //__UI_H__