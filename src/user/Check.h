/*
 * Check.h
 *
 *  Created on: 2013-05-05
 *      Author: Jack
 */

#ifndef CHECK_H_
#define CHECK_H_ 

#include "Device.h"

typedef enum SendType
{
    ad0=0,  ad1=1,
    ad2=2,  ad3=3,
    ad4=4,  ad5=5,
    ad6=6,  ad7=7,
    ad8=8,  ad9=9,
    ad10=10, ad11=11,
    CRC_ang=12,
    CRC_spd=13
}SendType;

typedef enum RecvType
{
  
   CRC_angle,CRC_speed
     
}RecvType;

#define startbit 0xff
#define BUFFER_SIZE 100 //接收缓冲区最大字节数


#define in_data(x) uart_getchar(UART0)
#define out_data(x) uart_putchar(UART0,x)

void CRC_Send(SendType type,int16 var);
bool CRC_Recv(RecvType*type,int16*var);

#endif /* CHECK_H_ */
