/*
 * InitAll.c
 *  ��ʼ������ģ��
 *  Created on: 2015-04-21
 *      Author:Hypocrisy
 */

#include "Device.h"

void InitAll() {
    InitGlobalVars();
    InitSensor();
    InitActuator();
    InitUltraSound();
    InitUI();           //�˺���Ҫ����ʼ��,������ʾ������    
    InitReedPipe();     //��ʼ���ɻɹܵļ��   
    LCD_Init();
    
    pit_init_ms(PIT0,1);
    pit_init_ms(PIT1,1);
    //DELAY_MS(2000);
}


void InitSensor() {   
    //AD��ʼ��  
    adc_init(ADC0, AD8);
    adc_init(ADC0, AD9);    
    adc_init(ADC0, AD12);
    adc_init(ADC0, AD13);
    adc_init(ADC1, AD14);
    adc_init(ADC1, AD15);
    adc_init(ADC0, AD14);
    adc_init(ADC0, AD15);

    //Norm=(ad_ave(ADC0, AD18,WEI, AVE)+ad_ave(ADC1, AD8 ,WEI, AVE))/2;

    //��������ʼ��   
    FTM1_QUAD_Iint(); 
}
void InitActuator() {
    //2015-03-30�޸�,��PTC2��PTC3�Ķ˿���Ϊ1��0,����ת,Ϊ0��1
    gpio_init(PORTC,2,GPO,0);
    gpio_init(PORTC,3,GPO,1);
    FTM_PWM_init(FTM0, CH3 ,16000 ,50);//motor 
    FTM_PWM_init(FTM2, CH0 ,200   ,13);//steer
}
/*************************************************************************
*                          Hypocrisy
*  �������ƣ�InitUltraSound
*  ����˵��������������ʼ��,��������PORTD2�ڵĽ����ж��Լ�PIT2���жϳ�ʼ��
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2015-4-10    �Ѳ���
*  ��    ע��
*************************************************************************/ 
void InitUltraSound() {
    //��ʼ����������Ϊ����,�������ж�
    //gpio_init(PORTD,2,GPI,0);             //PTD2Ϊ�������������DO��
    //gpio_init(PORTD,3,GPI,0);             //PTD3Ϊ״̬���STATE��

    SIM_SCGC5|=SIM_SCGC5_PORTD_MASK;
    PORT_PCR_REG(PORTD_BASE_PTR, 2)&=~(PORT_PCR_MUX_MASK);
    PORT_PCR_REG(PORTD_BASE_PTR, 2) = PORT_PCR_MUX(1);

    GPIO_PDDR_REG(PTD_BASE_PTR) &=~(1 << 2);
    PORT_PCR_REG(PORTD_BASE_PTR, 2)&=~(PORT_PCR_PS_MASK);
    PORT_PCR_REG(PORTD_BASE_PTR, 2)|=~(PORT_PCR_PE_MASK);

    PORT_PCR_REG(PORTD_BASE_PTR, 2)|= PORT_PCR_IRQC((uint8)0x0B);


    //exti_init(PORTD,2,rising_down);

    set_irq_priority(PORTD+87,0);         //����PORTD���ж����ȼ����
    enable_irq(PORTD + 87);

    SIM_SCGC6   |= SIM_SCGC6_PIT_MASK;//module clock  
    PIT_MCR     &= ~PIT_MCR_MDIS_MASK;//pit module enable
    PIT_LDVAL2   = 0xFFFFFFFF;          //bus_clk_khz

    PIT_TFLG2   |= PIT_TFLG_TIF_MASK;//clear by writing 1
    set_irq_priority(70,1);          //����PIT2���ж����ȼ���֮,ʵ���в�δ�õ�PIT2���жϺ���
}

/*************************************************************************
*                           Hypocrisy
*  �������ƣ�InitUI
*  ����˵������ʼ���˻�����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2015-4-6    �Ѳ���
*  ��    ע��
*************************************************************************/
void InitUI() { 
    //------------------------------------------
    //�������ݵĴ�����isr.c��
    //����ģ���ʼ��     
    uart_init(UART0,9600);
    UART_IRQ_EN(UART0);
    
    //���뿪�س�ʼ��
    for( uint8 i = 10; i <= 17; i++ ) {
        gpio_init(PORTC,i,GPI_DOWN,0);
    }
}

//��ʼ���ɻɹܵļ��
void InitReedPipe() {
    gpio_init(PORTE,1,GPI,0);
    exti_init(PORTE,1,zero_up); 
}