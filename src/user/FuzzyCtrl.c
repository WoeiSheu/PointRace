/*
 * FuzzyCtrl.c
 *
 *  Created on: 2012-12-31
 *      Author: Jack
 */
#include "Device.h" 

#define FORWARD 0
#define BACKWARD 1

int32 OffsetMembership[NUM];
int32 OffsetDMembership[NUM];

int16 OffsetOld[30]    = {0}; 
int32 OffsetBound[NUM]  = {-360 , -240 , -120 , 0 , 120 , 240 , 360};
int32 OffsetDBound[NUM] = {-150 , -100 , -50  , 0 , 40  ,  100 , 150};

////////////////////////////////////////////////////////////
// 舵机控制
//

void FuzzyCtrl()
{

  int i,j;
  Kp = 0,Kd = 0,Spd = 0;
  
  CalcMembership(P,OffsetMembership  ,OffsetBound);
  CalcMembership(D,OffsetDMembership ,OffsetDBound);

  for (i = 0; i < NUM; i++) {   //Offset为列,OffsetD为行
    if (OffsetMembership[i] != 0) {
      for (j = 0; j < NUM; j++) {
        if (OffsetDMembership[j] != 0) {
          Kp  +=  KpTab[j][i] * OffsetMembership[i] * OffsetDMembership[j];
          Kd  +=  KdTab[j][i] * OffsetMembership[i] * OffsetDMembership[j];
          Spd +=  SpdTab[j][i]* OffsetMembership[i] * OffsetDMembership[j];
        }
      }
    }
  }

  Kp   /= 10000;
  Kd   /= 10000;

  SpeedSet = 300;//Spd/10000+40 + 30*PB[7] + 20*PB[6];

  //angle2 = Kp*P/50;
  //angle3 = Kd*D/45;

  Angle = Kp*P/50 + Kd*D/40;        //正负号根据舵机修改

  SetSteerAngle(Angle);
  
}


//////////////////////////////////////////////////////////////
// 速度控制
//
void  SpeedCtrl()      
{  
    //int16 P=24,I=10,D=5;  
    static int SpeedErr=0,LastSpdErr=0,PreSpdErr=0,Target = 0,SpdErrorSum = 0,DertaSpdError = 0; 
  
    if(IsStop)  SpeedSet = 0;
      
    CurSpdTemp = FTM1_CNT;
    FTM1_CNT &= 0x00;
    
    //FTM1_CNT 分正负
    //MotorDir = PIT_CVAL0;
    //MotorDir = ((FTM1_QDCTRL>>FTM_QDCTRL_QUADIR_SHIFT)&1);

    if( CurSpdTemp>FTM1_MOD/2 )//大于模的一半则说明平均速度是反向的
    {
        CurSpdTemp = FTM1_MOD-CurSpdTemp;       //用模减获得真实计数值
        MotorDir = BACKWARD;            //平均速度反向
    } else {
        CurSpdTemp = CurSpdTemp;
        MotorDir = FORWARD;            //平均速度正向
    }
    
    
    //滤波,可以让编码器返回值更平稳
    if( MotorDir == FORWARD )
    {
        CurSpd = (CurSpd*4 + CurSpdTemp)/5;
    }
    else  
    {
        CurSpd = (CurSpd*4 - CurSpdTemp)/5;
    }
    

//增量式
    PreSpdErr  = LastSpdErr;
    LastSpdErr = SpeedErr;
    SpeedErr   = (SpeedSet - CurSpd);
    Target += (KPv * (SpeedErr - LastSpdErr)
            +  KIv *  SpeedErr
            +  KDv * (SpeedErr-2*LastSpdErr+PreSpdErr))/100;   //增量式PID  
      //设置饱和区
    if(Target>SpeedRight) 
       Target = SpeedRight;
    if(Target<SpeedLeft)
       Target = SpeedLeft; 

/*
//位置式
    LastSpdErr = SpeedErr;
    SpeedErr = SpeedSet - CurSpd;
    DertaSpdError = SpeedErr - LastSpdErr;
    if(Tick > StartDelay) {
       SpdErrorSum += SpeedErr;
    } else {
    SpdErrorSum  = 0;
    }
    if(SpdErrorSum > 4000) { //积分饱和4000
          SpdErrorSum = 4000;
    }

    Target = (KPv*SpeedErr + KIv*SpdErrorSum + KDv*DertaSpdError)/1000;
          
    if(Target>SpeedRight)    Target = SpeedRight;
    if(Target<SpeedLeft)     Target = SpeedLeft;

  */  
    //Target = 300*GPIO_GET_4bit(PORTD,0)/9;
    SetMotorSpeed(Target);
    
}