
#include "common.h"
#include "include.h"

void main()
{

    DisableInterrupts;                                //��ֹ���ж�
 
    pit_init_ms(PIT0, 1000);                          //��ʼ��PIT0����ʱʱ��Ϊ�� 1000ms

    EnableInterrupts;			              //�����ж�
    while(1)
    {
    }
}