/******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
 * �ļ���       ��isr.h
 * ����         �����º궨���жϺţ���ӳ���ж�����������жϺ�����ַ��
 *                ʹ��ָ��������������жϷ������������жϷ�����
 *                ���棺ֻ����"vectors.c"���������ұ�����"vectors.h"�����ĺ��棡����
 *
 * ʵ��ƽ̨     ��Ұ��kinetis������
 * ��汾       ��
 * Ƕ��ϵͳ     ��
 *
 * ����         ��Ұ��Ƕ��ʽ����������
 * �Ա���       ��http://firestm32.taobao.com
 * ����֧����̳ ��http://www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008
**********************************************************************************/

#ifndef __ISR_H
#define __ISR_H 1

#include  "include.h"

/*                          ���¶����ж�������
 *  ��ȡ��Ĭ�ϵ��ж�����Ԫ�غ궨��       #undef  VECTOR_xxx
 *  �����¶��嵽�Լ���д���жϺ���       #define VECTOR_xxx    xxx_IRQHandler
 *  ���磺
 *       #undef  VECTOR_003
 *       #define VECTOR_003    HardFault_Handler    ���¶���Ӳ���Ϸ��жϷ�����
 */

#undef  VECTOR_061
#define VECTOR_061    BluetoothISR  //UART0
#undef  VECTOR_084
#define VECTOR_084    SamplingISR   //PIT0    
#undef  VECTOR_085
#define VECTOR_085    SysTimerISR   //PIT1
#undef  VECTOR_086
#define VECTOR_086    PIT2ISR   //PIT2
/*
#undef  VECTOR_103
#define VECTOR_103    PORTA_IRQHandler  //PORTA
*/
#undef  VECTOR_106
#define VECTOR_106    PORTD_IRQHandler //PORTD
#undef  VECTOR_107
#define VECTOR_107    ReedPipeISR   //PORTE

extern void SamplingISR();            //PIT0  �жϷ�����
extern void SysTimerISR();            //PIT1  �жϷ�����
extern void PIT2ISR();
extern void ReedPipeISR();            //PORTA �жϷ����� 
extern void BluetoothISR();           //UART0 �жϷ�����
extern void PORTD_IRQHandler();       //PORTD �жϷ�����
//extern void PORTA_IRQHandler();       //PORTA �жϷ�����


#endif  //__ISR_H

/* End of "isr.h" */