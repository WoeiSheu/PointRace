/*
 * InitAll.c
 *  初始化所有模块
 *  Created on: 2015-04-21
 *      Author:Hypocrisy
 */

#include "Device.h"

void InitAll() {
    InitGlobalVars();
    InitSensor();
    InitActuator();
    InitUI();           //此函数要最后初始化,否则显示不正常    
    InitReedPipe();     //初始化干簧管的检测   
    LCD_Init();
    InitUltraSound();
    
    pit_init_ms(PIT0,1);
    pit_init_ms(PIT1,1);
    
    //set_irq_priority(69,0);
    //set_irq_priority(68,1);
    //DELAY_MS(2000);
}


void InitSensor() {   
    //AD初始化  
    adc_init(ADC0, AD8);
    adc_init(ADC0, AD9);    
    adc_init(ADC0, AD12);
    adc_init(ADC0, AD13);
    adc_init(ADC1, AD14);
    adc_init(ADC1, AD15);
    adc_init(ADC0, AD14);
    adc_init(ADC0, AD15);

    //Norm=(ad_ave(ADC0, AD18,WEI, AVE)+ad_ave(ADC1, AD8 ,WEI, AVE))/2;

    //编码器初始化   
    FTM1_QUAD_Iint(); 
}
void InitActuator() {
    //2015-03-30修改,将PTC2、PTC3的端口设为1、0,若反转,为0、1
    gpio_init(PORTC,2,GPO,0);
    gpio_init(PORTC,3,GPO,1);
    FTM_PWM_init(FTM0, CH3 ,16000 ,50);//motor 
    FTM_PWM_init(FTM2, CH0 ,200   ,13);//steer
}
/*************************************************************************
*                          Hypocrisy
*  函数名称：InitUltraSound
*  功能说明：超声波测距初始化,包括设置PORTD2口的接收中断以及PIT2的中断初始化
*  参数说明：无
*  函数返回：无
*  修改时间：2015-4-10    已测试
*  备    注：
*************************************************************************/ 
void InitUltraSound() {
    //初始化两个引脚为输入,并接受中断
    //gpio_init(PORTD,2,GPI,0);             //PTD2为超声波脉冲输出DO端
    //gpio_init(PORTD,3,GPI,0);             //PTD3为状态输出STATE端

    SIM_SCGC5|=SIM_SCGC5_PORTD_MASK;
    PORT_PCR_REG(PORTD_BASE_PTR, 2)&=~(PORT_PCR_MUX_MASK);
    PORT_PCR_REG(PORTD_BASE_PTR, 2) = PORT_PCR_MUX(1);

    GPIO_PDDR_REG(PTD_BASE_PTR) &=~(1 << 2);
    PORT_PCR_REG(PORTD_BASE_PTR, 2)&=~(PORT_PCR_PS_MASK);
    PORT_PCR_REG(PORTD_BASE_PTR, 2)|=~(PORT_PCR_PE_MASK);

    PORT_PCR_REG(PORTD_BASE_PTR, 2)|= PORT_PCR_IRQC((uint8)0x0B);


    //exti_init(PORTD,2,rising_down);

    set_irq_priority(PORTD+87,0);         //设置PORTD的中断优先级最高
    enable_irq(PORTD + 87);

    SIM_SCGC6   |= SIM_SCGC6_PIT_MASK;//module clock  
    PIT_MCR     &= ~PIT_MCR_MDIS_MASK;//pit module enable
    PIT_LDVAL2   = 0xFFFFFFFF;          //bus_clk_khz

    PIT_TFLG2   |= PIT_TFLG_TIF_MASK;//clear by writing 1
    set_irq_priority(70,1);          //设置PIT2的中断优先级次之,实际中并未用到PIT2的中断函数
}

/*************************************************************************
*                           Hypocrisy
*  函数名称：InitUI
*  功能说明：初始化人机交互
*  参数说明：无
*  函数返回：无
*  修改时间：2015-4-6    已测试
*  备    注：
*************************************************************************/
void InitUI() { 
    //------------------------------------------
    //蓝牙数据的处理在isr.c中
    //蓝牙模块初始化
  
    uart_init(UART0,9600);
    UART_IRQ_EN(UART0);
    
    //拨码开关初始化
    for( uint8 i = 10; i <= 17; i++ ) {
        gpio_init(PORTC,i,GPI_DOWN,0);
    }
    
    //LCD显示屏初始化
    LCD_Fill(0xff);//亮屏 
    DELAY_MS(1000); 
    LCD_Fill(0x00);//黑屏
    DELAY_MS(1000);      
    LCD_Print(2,0,"北京理工大学电磁组");  //汉字字符串显示
    LCD_Print(33,2,"1.调试模式");   //汉字字符串显示
    LCD_Print(33,4,"2.查看电感值");   //汉字字符串显示
    LCD_Print(33,6,"3.查看参数");   //汉字字符串显示
    DELAY_MS(1000);
}

//初始化干簧管的检测
void InitReedPipe() {
    gpio_init(PORTE,1,GPI,0);
    exti_init(PORTE,1,zero_up); 
}