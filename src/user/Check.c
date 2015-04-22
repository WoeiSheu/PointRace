#include "Check.h"

vuint8 flag;
vuint8 index;
vuint8 buff[BUFFER_SIZE]; //接收数据缓冲区

void CRC_Send(u8 type,int16 var)
{
   u8 num=0;
   u8 checksum=0;
   int16 pvar=&var;
   out_data(startbit);
   out_data(startbit);
   out_data(type);
   checksum+=type;
   num = *((u8*)pvar);
   out_data(num);
   checksum+=num;
   num = *(((u8*)pvar)+1);
   out_data(num);
   checksum+=num;
   
}

void CRC_Recv(RecvType*type,int16*var)
{  
   u8 ch;
   ch = in_data();
   if(ch)
}