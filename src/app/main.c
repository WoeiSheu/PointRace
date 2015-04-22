/******************** (C) COPYRIGHT 2013 Jack *************************
 * 文件名       ：main.c
 * 描述         ：主函数
 *
 * 实验平台     ：Browser电磁组
 * 库版本       ：1.0
 * 嵌入系统     ：无
 *
 * 说明         ：user文件夹中为电磁车主体部分
 *                其中，所有控制函数在isr.c的PIT0中断引用
 *                
 * 作者         ：Jack
************************************************************************/

#include "Device.h" 
  
void main()
{   
    InitAll();
    
    while(1) {
      
      if(Tick % 100 == 0) {
        GetData(SpeedSet,D,P,CurSpd);
        OutputData();            
      }
      
    }
}