/*
 * Misc.c
 *  各类小函数
 *  Created on: 2015-04-21
 *      Author:Hypocrisy
 */

#include "Device.h"

int16 Kp1[NUM][NUM] = {                                 //D为列P为行  //两个舵机表
    { 100, 90  , 85 ,  22  , 30 ,  60  , 80  },        //左上：左拐入弯   右上：右拐出弯
    { 85 , 85  , 80 ,  30  , 30 ,  75  , 65  },
    { 80 , 70  , 65 ,  50  , 45 ,  50  , 55  },
    { 45 , 40  , 23 ,   5  , 43 ,  45  , 50  },        //直道D为零
    { 33 , 50  , 45 ,  50  , 75 ,  70  , 80  },
    { 30 , 25  , 40 ,  30  , 80 ,  90  , 90  },
    { 20 , 20  , 50 ,  22  , 85 ,  100  , 110  }       //左下：左拐出弯   右下：右拐入弯
};
int16 Kd1[NUM][NUM] = {                                 //Offset为列，OffsetD为行 
    {150  ,  150  ,  85,  17 ,  80,  120  , 140  },
    {150  ,  130  ,  85,  28 ,  80,  120  , 140  },
    {145  ,  135  ,  80,  60 ,  80,  125  , 145  },
    {145  ,  130  ,  80,  65 ,  80,  130  , 140  },
    {145  ,  125  ,  80,  60 ,  80,  135  , 145  }, 
    {140  ,  120  ,  80,  28 ,  85,  130  , 150  },
    {140  ,  120  ,  80,  17 ,  85,  150  , 150  }
}; 
int16 Spd1[NUM][NUM] = {                                //Error为列Diff为行    //速度表
    { 130 , 120 ,  90 , 140 , 160 , 160 , 170 },
    { 135 , 130 , 100 , 150 , 170 , 160 , 160 },
    { 140 , 140 , 160 , 200 , 180 , 170 , 160 },
    { 160 , 170 , 200 , 226 , 200 , 170 , 160 },
    { 160 , 170 , 180 , 200 , 160 , 140 , 135 },
    { 170 , 170 , 170 , 150 , 100 , 120 , 125 },
    { 180 , 170 , 160 , 140 ,  90 , 110 , 120 }
};

int16 Kp2[NUM][NUM] = {                                 //D为列P为行  //两个舵机表
    { 80 , 70  , 60 ,  22  , 30 ,  60  , 80  },        //左上：左拐入弯   右上：右拐出弯
    { 65 , 65  , 45 ,  30  , 30 ,  75  , 65  },
    { 55 , 53  , 45 ,  50  , 45 ,  50  , 55  },
    { 45 , 40  , 23 ,  5   , 43 ,  45  , 50  },        //直道D为零
    { 33 , 50  , 45 ,  50  , 75 ,  55  , 60  },
    { 30 , 25  , 40 ,  30  , 60 ,  105  , 105  },
    { 20 , 20  , 50 ,  22  , 65 ,  110  , 120  }       //左下：左拐出弯   右下：右拐入弯
};
int16 Kd2[NUM][NUM] = {                                 //Offset为列，OffsetD为行 
    {150  ,  150  ,  85,  17 ,  80,  120  , 140  },
    {150  ,  130  ,  85,  28 ,  80,  120  , 140  },
    {145  ,  135  ,  80,  60 ,  80,  125  , 145  },
    {145  ,  130  ,  80,  65 ,  80,  130  , 140  },
    {145  ,  125  ,  80,  60 ,  80,  135  , 145  }, 
    {140  ,  120  ,  80,  28 ,  85,  130  , 150  },
    {140  ,  120  ,  80,  17 ,  85,  150  , 150  }
}; 
int16 Spd2[NUM][NUM] = {                                //Error为列Diff为行    //速度表
    { 130 , 120 ,  90 , 140 , 160 , 170 , 180 },
    { 135 , 130 , 100 , 150 , 170 , 170 , 170 },
    { 140 , 140 , 160 , 200 , 180 , 170 , 160 },
    { 160 , 170 , 200 , 226 , 200 , 170 , 160 },
    { 160 , 170 , 180 , 200 , 160 , 140 , 135 },
    { 170 , 170 , 170 , 150 , 100 , 120 , 125 },
    { 180 , 170 , 160 , 140 ,  90 , 110 , 120 }
};

int16 Kp3[NUM][NUM] = {                                 //D为列P为行  //两个舵机表
    { 100, 90  , 85 ,  22  , 30 ,  60  , 80  },        //左上：左拐入弯   右上：右拐出弯
    { 85 , 85  , 80 ,  30  , 30 ,  75  , 65  },
    { 80 , 70  , 20 ,  16  , 20 ,  50  , 55  },
    { 45 , 40  , 16 ,   5  , 16 ,  45  , 50  },        //直道D为零
    { 33 , 50  , 20 ,  16  , 20 ,  70  , 80  },
    { 30 , 25  , 40 ,  30  , 80 ,  90  , 90  },
    { 20 , 20  , 50 ,  22  , 85 ,  100  , 110  }       //左下：左拐出弯   右下：右拐入弯
};
int16 Kd3[NUM][NUM] = {                                 //Offset为列，OffsetD为行 
    {150  ,  150  ,  85,  17 ,  80,  120  , 140  },
    {150  ,  130  ,  85,  28 ,  80,  120  , 140  },
    {145  ,  135  ,  80,  60 ,  80,  125  , 145  },
    {145  ,  130  ,  80,  65 ,  80,  130  , 140  },
    {145  ,  125  ,  80,  60 ,  80,  135  , 145  }, 
    {140  ,  120  ,  80,  28 ,  85,  130  , 150  },
    {140  ,  120  ,  80,  17 ,  85,  150  , 150  }
}; 
int16 Spd3[NUM][NUM] = {                                //Error为列Diff为行    //速度表
    { 130 , 120 ,  90 , 140 , 160 , 170 , 180 },
    { 135 , 130 , 100 , 150 , 170 , 170 , 170 },
    { 140 , 140 , 160 , 200 , 180 , 170 , 160 },
    { 160 , 170 , 200 , 226 , 200 , 170 , 160 },
    { 160 , 170 , 180 , 200 , 160 , 140 , 135 },
    { 170 , 170 , 170 , 150 , 100 , 120 , 125 },
    { 180 , 170 , 160 , 140 ,  90 , 110 , 120 }
};

int16 Kp4[NUM][NUM] = {                                 //D为列P为行  //两个舵机表
    { 110, 100  , 85 ,  22  , 30 ,  60  , 80  },       //左上：左拐入弯   右上：右拐出弯
    { 90 , 90  , 80 ,  30  , 30 ,  75  , 65  },
    { 80 , 70  , 65 ,  50  , 45 ,  50  , 55  },
    { 45 , 40  , 23 ,   5  , 43 ,  45  , 50  },        //直道D为零
    { 33 , 50  , 45 ,  50  , 75 ,  70  , 80  },
    { 30 , 25  , 40 ,  30  , 80 ,  90  , 90  },
    { 20 , 20  , 50 ,  22  , 85 ,  100  , 110  }       //左下：左拐出弯   右下：右拐入弯
};
int16 Kd4[NUM][NUM] = {                                 //Offset为列，OffsetD为行 
    {150  ,  150  ,  85,  17 ,  80,  120  , 140  },
    {150  ,  130  ,  85,  28 ,  80,  120  , 140  },
    {145  ,  135  ,  80,  60 ,  80,  125  , 145  },
    {145  ,  130  ,  80,  65 ,  80,  130  , 140  },
    {145  ,  125  ,  80,  60 ,  80,  135  , 145  }, 
    {140  ,  120  ,  80,  28 ,  85,  130  , 150  },
    {140  ,  120  ,  80,  17 ,  85,  150  , 150  }
}; 
int16 Spd4[NUM][NUM] = {                                //Error为列Diff为行    //速度表
    { 130 , 120 ,  90 , 140 , 160 , 170 , 180 },
    { 135 , 130 , 100 , 150 , 170 , 170 , 170 },
    { 140 , 140 , 160 , 200 , 180 , 170 , 160 },
    { 160 , 170 , 200 , 226 , 200 , 170 , 160 },
    { 160 , 170 , 180 , 200 , 160 , 140 , 140 },
    { 170 , 170 , 170 , 150 , 100 , 130 , 135 },
    { 180 , 170 , 160 , 140 ,  90 , 130 , 130 }
};

int16 Ki1[NUM][NUM],Ki2[NUM][NUM],Ki3[NUM][NUM],Ki4[NUM][NUM];

/*
* 调用以控制舵机和电机
*/
//舵机
void SetSteerAngle(int16 nAngle) {
  //设置饱和区
  if(nAngle > AngleRight)
     nAngle = AngleRight; 
  if(nAngle < AngleLeft )
     nAngle = AngleLeft; 
  FTM2_C0V  = 8000 - 6*nAngle;  //62500对应200Hz,满占空比
}
//电机
void SetMotorSpeed(int16 nSpeed) {  
  //FTM0_C3V = 800;
  if(Tick < StartDelay) {
    FTM0_C3V = 0;
  } else {
    FTM0_C3V = nSpeed;    //周期61.25us时,1000对应40us,500对应20us
  }
}
//停车
void StopCar() {
    //disable_irq(PIT0 + 68);
    IsStop = TRUE;
    //SetSteerAngle(0);
}
/*************************************************************************
*                           Hypocrisy
*  函数名称：发送和接收数据的函数
*  功能说明：发送和接收数据
*  参数说明：发送和接收的四个int16型数据,加以CRC校验的两个字节
*  函数返回：无
*  修改时间：2015-4-11    已测试
*  备    注：
*************************************************************************/

uint16 OutData[4];              //串口数据
void GetData(int16 Ch1,int16 Ch2,int16 Ch3,int16 Ch4) {
  OutData[0]=(uint16)Ch1;
  OutData[1]=(uint16)Ch2;
  OutData[2]=(uint16)Ch3;
  OutData[3]=(uint16)Ch4;
}

//CRC16串口通讯协议
//---------------------------------------------------
//The following is the function of CRC16,please refer
//---------------------------------------------------
unsigned short CRC_CHECK(uint8 *Buf, uint8 CRC_CNT) {
    unsigned short CRC_Temp;
    uint8 i,j;
    CRC_Temp = 0xffff;

    for (i=0;i<CRC_CNT; i++){
        CRC_Temp ^= Buf[i];
        for (j=0;j<8;j++) {
            if (CRC_Temp & 0x01)
                CRC_Temp = (CRC_Temp >>1 ) ^ 0xa001;
            else
                CRC_Temp = CRC_Temp >> 1;
        }
    }
    return(CRC_Temp);
}

//Monitor routine Execute every T Period time
void OutputData() {
  unsigned short ChxData[4] = {0};
  uint8 databuf[10] = {0};
  uint8 i;
  unsigned short CRC16 = 0;
  for(i=0;i<4;i++) {
    ChxData[i] = (unsigned short)OutData[i];
	  //test161u = (unsigned short)OutData[i];
  }
  for(i=0;i<4;i++) {
    databuf[i*2+0] = (uint8)((ChxData[i])&0xff);
    databuf[i*2+1] = (uint8)((ChxData[i])>>8);
  }

  CRC16 = CRC_CHECK(databuf,8);
  databuf[8] = CRC16&0xff;
  databuf[9] = CRC16>>8;

  for(i=0;i<10;i++)
    uart_putchar(UART0,databuf[i]);
    //uart_send(databuf[i]);
}
//-----------------------------------------
//above is MCU code for CRC16 ,please refer.
//-----------------------------------------

/*
* 绝对值函数
*/
int16 abs(int16 value) {
  if(value < 0) {
    value = -value;
  }
  return value;
}
/*
* 比较求取最大值函数
*/
u16 FindMax(u16 ADValue,u16 *max) {
  if( *max < ADValue ) {
    *max = ADValue;
  }
  return *max;
}
/*
* 
*/
void Calc_Deviation_7Gear(int16 value, int16* returnValue, int16* dividePoints, int16* targetAngle) {
  int i;
  if (value < dividePoints[0]) {
   *returnValue = targetAngle[0];
  } else {
    if (value >= dividePoints[6]) {
      *returnValue = targetAngle[6];
    } else {
      for (i = 1; i < 7; i++) {
        if (value < dividePoints[i]) {
          *returnValue = (value - dividePoints[i-1]) * (targetAngle[i] - targetAngle[i-1]) / (dividePoints[i] - dividePoints[i-1]) + targetAngle[i-1];
          break;
        }
      }
    }
  }
}
/*************************************************************************
*                           Jack
*  函数名称：加载模糊表
*  功能说明：加载模糊表
*  参数说明：两个构成模糊表的二维数组
*  函数返回：无
*  修改时间：2013-4-11    已测试
*  备    注：
*************************************************************************/
void CopyArray(int16  a[NUM][NUM],int16  b[NUM][NUM]) {
    uint8 i,j;
    for(i = 0; i < NUM; i++)
       for(j = 0; j < NUM; j++)
          a[i][j] = b[i][j];
}
void LoadKpTab(TabN n) {
    switch(n) {
      case Tab1:CopyArray(KpTab,Kp1);break;
      case Tab2:CopyArray(KpTab,Kp2);break;
      case Tab3:CopyArray(KpTab,Kp3);break;
      case Tab4:CopyArray(KpTab,Kp4);break;
    }
}
void LoadKiTab(TabN n) {
    switch(n) {
      case Tab1:CopyArray(KiTab,Ki1);break;
      case Tab2:CopyArray(KiTab,Ki2);break;
      case Tab3:CopyArray(KiTab,Ki3);break;
      case Tab4:CopyArray(KiTab,Ki4);break;
    }
}
void LoadKdTab(TabN n) {
    switch(n) {
      case Tab1:CopyArray(KdTab,Kd1);break;
      case Tab2:CopyArray(KdTab,Kd2);break;
      case Tab3:CopyArray(KdTab,Kd3);break;
      case Tab4:CopyArray(KdTab,Kd4);break;
    }
}
void LoadSpdTab(TabN n) {
    switch(n) {
      case Tab1:CopyArray(SpdTab,Spd1);break;
      case Tab2:CopyArray(SpdTab,Spd2);break;
      case Tab3:CopyArray(SpdTab,Spd3);break;
      case Tab4:CopyArray(SpdTab,Spd4);break;
    }
}
void LoadTabs(TabN Kp,TabN Ki,TabN Kd,TabN Spd) {
    LoadKpTab(Kp);
    LoadKiTab(Ki);
    LoadKdTab(Kd);
    LoadSpdTab(Spd);
}
////////////////////////////////////////////////////////////////
//计算隶属度通用函数
///////////////////////////////////////////////////////////////
void CalcMembership(int32 value,int32 membership[],int32 bound[]) {
  uint8 i;
  for (i = 0; i <= NUM - 1; i++) {
    membership[i] = 0;
  }	
  if (value < bound[0])	{
    membership[0] = 100;
  } else if(value >= bound[NUM - 1]) {
    membership[NUM - 1] = 100;
  } else {
    for (i = 1; i <= NUM - 1; i++) {
      if (value < bound[i]) {
        membership[i-1] = (bound[i] - value) * 100 / (bound[i] - bound[i - 1]);
        membership[i]   = 100 - membership[i-1];
        break;
      }
    }
  }	
}