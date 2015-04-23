#include "Device.h"

/*************************************************************************
*                            Jack
*  函数名称：SamplingISR
*  功能说明：PIT0 定时中断服务函数，用作采样、控制
*  参数说明：无
*  函数返回：无
*  修改时间：2013-4-6   已测试
*  备    注：
*************************************************************************/

void SamplingISR(void) {
    #define T 10
    static uint8 count; 
    DisableInterrupts;     //关总中断

    GetPosInfo();
    FuzzyCtrl();    
    if(count>T) { 
      count = 0;
      SpeedCtrl(); 
      if(StopDelay<30*T+10)
        StopDelay++;
        //ScopeShow();  
    } else {
        count++;
    }

    PIT_Flag_Clear(PIT0);       //清中断标志位
    EnableInterrupts;		//开总中断
}
       
/*************************************************************************
*                            Jack
*
*  函数名称：BluetoothISR
*  功能说明：串口0 中断 接收 服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2013-4-6    已测试
*  备    注：
*************************************************************************/
void BluetoothISR(void)
{
    DisableInterrupts;

    char ch[80];
    int i, tempData[4];
    
    uart_pendstr(UART0,ch);    //接收到一个字符串

    for(i=0;i<8;i++)
        uart_putchar(UART0,ch[i]-'0');
    
    for(i = 0; i < 4; i++) {
        tempData[i] = (ch[i]-'0') * 10 + ch[i+1]-'0';
    }
    
    //IsStop   = tempData[0];
    //SpeedSet = tempData[1];
    
    EnableInterrupts;	    //开总中断 
} 

/*************************************************************************
*                            Jack
*
*  函数名称：SysTimerISR
*  功能说明：PIT1中断，用作系统时钟
*  参数说明：无
*  函数返回：无
*  修改时间：2013-4-9   已测试
*  备    注：
*************************************************************************/
void SysTimerISR(void)
{   
    for( uint8 i = 0; i <= 7; i++ ) {
      PB[i] = gpio_get(PORTC,i+10);
    }
    Tick++;
    
    PIT_Flag_Clear(PIT1);       //清中断标志位
}
 
/*************************************************************************
*                            Jack
*
*  函数名称：ReedPipeISR
*  功能说明：PORTE端口中断服务函数，用作干簧管
*  参数说明：无
*  函数返回：无
*  修改时间：2013-4-6    已测试
*  备    注：引脚号需要自己初始化来清除
*************************************************************************/
void ReedPipeISR()
{
  //PTE1触发中断使停车
    if(PORTE_ISFR & (1 << 1))
    {
      PORTE_ISFR |= (1<<1);     //写1清中断标志位
      //DELAY_MS(1);
      if(!gpio_get(PORTE,1)&&StopDelay>=30*T)
      { IsStop = TRUE; return; }
    }
}

/*************************************************************************
*                             野火嵌入式开发工作室
*
*  函数名称：HardFault_Handler
*  功能说明：硬件上访中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-4    已测试
*  备    注：可以用LED闪烁来指示发生了硬件上访
*************************************************************************/
void HardFault_Handler(void)
{
    while (1)
    {
        printf("\n****硬件错误!!!*****\r\n\n");
    }
} 
/*************************************************************************
*                             野火嵌入式开发工作室
*
*  函数名称：FTM1_IRQHandler
*  功能说明：FTM1输入捕捉中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-25
*  备    注：引脚号需要根据自己初始化来修改，参考现有的代码添加自己的功能
*************************************************************************/
void FTM1_IRQHandler()
{
    u8 s = FTM1_STATUS;             //读取捕捉和比较状态  All CHnF bits can be checked using only one read of STATUS.
    u8 n;
    FTM1_STATUS = 0x00;               //清中断标志位

    n = 0;
    if( s & (1 << n) )
    {
        FTM_CnSC_REG(FTM1_BASE_PTR, n) &= ~FTM_CnSC_CHIE_MASK; //禁止输入捕捉中断
        /*     用户任务       */
        
        /*********************/
        //不建议在这里开启输入捕捉中断，而是在main函数里根据需要来开启
        //通道 CH0、CH1、Ch2、Ch3 有滤波器
        //FTM_CnSC_REG(FTM1_BASE_PTR,n) |= FTM_CnSC_CHIE_MASK;  //开启输入捕捉中断
        //delayms(10);        //因为输入的信号跳变过程不稳定，容易触发多次输入捕捉，所以添加延时
        //但考虑到中断不应该过长延时，所以开输入捕捉中断就放在main函数里，根据需要来开启
    }

    n = 1;
    if( s & (1 << n) )
    {
        FTM_CnSC_REG(FTM1_BASE_PTR, n) &= ~FTM_CnSC_CHIE_MASK; //禁止输入捕捉中断
        /*     用户任务       */


        /*********************/
        //不建议在这里开启输入捕捉中断
        //FTM_CnSC_REG(FTM1_BASE_PTR,n) |= FTM_CnSC_CHIE_MASK;  //开启输入捕捉中断
    }

}

/*************************************************************************
*                           Hypocrisy
*  函数名称：PORTD_IRQHandler()
*  功能说明：PORTD 中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2015-04-09
*  备    注：引脚号需要根据自己初始化来修改，参考现有的代码添加自己的功能
*************************************************************************/
void PORTD_IRQHandler() {
  //PORTD_ISFR|= 0xFFFFFFFFu;   //清除标志位
  PORTD_ISFR |= (1<<2);

  if((GPIOD_PDIR & (0x01<<2)))//检测到IO口是高电平，那么就是上升沿
  {
    //如果是上升沿中断

    PIT_TCTRL2  &= ~PIT_TCTRL_TEN_MASK;//停止定时器
    PIT_LDVAL2  = 0xFFFFFFFF;//32位定时器，装最大值即可
    PIT_TCTRL2  |= PIT_TCTRL_TEN_MASK;//启动定时器
  }
  else
  {
    ultraSoundTime = (0xFFFFFFFF - PIT_CVAL2)/50;//50M总线时钟，计算得到时间，单位是微秒
    ABDistance = ultraSoundTime * 340/1000;//一秒钟的声音速度假设为340米，由于ultraSoundTime单位是微秒，/1000后得到单位是mm
    
    PIT_TCTRL2  &= ~PIT_TCTRL_TEN_MASK;//停止定时器
  }    
}
/*************************************************************************
*                            Hypocrisy
*  函数名称：PIT2ISR
*  功能说明：PIT2 定时中断服务函数，测试用
*  参数说明：无
*  函数返回：无
*  修改时间：2015-4-6   已测试
*  备    注：
*************************************************************************/
void PIT2ISR() {
  //test[3]++;
}