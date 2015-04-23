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

    LCD_Fill(0xff);//亮屏 
    DELAY_MS(1000); 
    LCD_Fill(0x00);//黑屏
    DELAY_MS(1000);      
    LCD_Print(2,0,"北京理工大学电磁组");  //汉字字符串显示
    LCD_Print(33,2,"1.调试模式");   //汉字字符串显示
    LCD_Print(33,4,"2.查看电感值");   //汉字字符串显示
    LCD_Print(33,6,"3.查看参数");   //汉字字符串显示
    DELAY_MS(1000);
  
    while(1) {
        if(Tick % 100 == 0) {
          GetData(SpeedSet,D,P,CurSpd);
          OutputData();            
        }
    }
}