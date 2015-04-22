
#include "common.h"
#include "include.h"

void main()
{

    DisableInterrupts;                                //禁止总中断
 
    pit_init_ms(PIT0, 1000);                          //初始化PIT0，定时时间为： 1000ms

    EnableInterrupts;			              //开总中断
    while(1)
    {
    }
}