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
int32 OffsetBound[NUM]  = {-260 , -140 , -80 ,  0 , 80 ,   140 , 260};
int32 OffsetDBound[NUM] = {-150 , -100 , -50  , 0 , 40  ,  100 , 150};

////////////////////////////////////////////////////////////
// �������
//

void FuzzyCtrl()
{

  int i,j;
  int32 Kp = 0,Kd = 0,Spd = 0;
  
  CalcMembership(P,OffsetMembership  ,OffsetBound);
  CalcMembership(D,OffsetDMembership ,OffsetDBound);

  for (i = 0; i < NUM; i++) {   //OffsetΪ��,OffsetDΪ��
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

  SpeedSet = 200;  //Spd/10000;
  if(ABDistance < 1200) {
    SpeedSet -= 50;
  }
  
  //angle2 = Kp*P/50;
  //angle3 = Kd*D/45;

  Angle = Kp*P/40 + Kd*D/40;        //�����Ÿ��ݶ���޸�

  SetSteerAngle(Angle);
}


//////////////////////////////////////////////////////////////
// �ٶȿ���
//  
void SpeedCtrl()      
{  
    int16 KPv=12000, KIv=20, KDv=0; //���PID���Ʋ���
    //int16 P=24,I=10,D=5;  
    static int16 SpeedErr=0,LastSpdErr=0,PreSpdErr=0,Target = 0,SpdErrorSum = 0,DertaSpdError = 0; 
    if(IsStop)  SpeedSet = 0;
    CurSpdTemp = FTM1_CNT;
    FTM1_CNT &= 0x00;
    
    //FTM1_CNT ������
    //MotorDir = PIT_CVAL0;
    //MotorDir = ((FTM1_QDCTRL>>FTM_QDCTRL_QUADIR_SHIFT)&1);

    if( CurSpdTemp>FTM1_MOD/2 )//����ģ��һ����˵��ƽ���ٶ��Ƿ����
    {
        CurSpdTemp = FTM1_MOD-CurSpdTemp;       //��ģ�������ʵ����ֵ
        MotorDir = BACKWARD;            //ƽ���ٶȷ���
    } else {
        CurSpdTemp = CurSpdTemp;
        MotorDir = FORWARD;            //ƽ���ٶ�����
    }
    
    
    //�˲�,�����ñ���������ֵ��ƽ��
    if( MotorDir == FORWARD )
    {
        CurSpd = (CurSpd*4 + CurSpdTemp)/5;
    }
    else  
    {
        CurSpd = (CurSpd*4 - CurSpdTemp)/5;
    }
/*
//����ʽ
    PreSpdErr  = LastSpdErr;
    LastSpdErr = SpeedErr; 
    SpeedErr   = (SpeedSet - CurSpd);
    Target += (KPv * (SpeedErr - LastSpdErr)
            +  KIv *  SpeedErr
            +  KDv * (SpeedErr-2*LastSpdErr+PreSpdErr))/100;   //����ʽPID  
      //���ñ�����
    if(Target>SpeedRight) 
       Target = SpeedRight;
    if(Target<SpeedLeft)
       Target = SpeedLeft; 
*/

//λ��ʽ
    LastSpdErr = SpeedErr;
    SpeedErr = SpeedSet - CurSpd;
    DertaSpdError = SpeedErr - LastSpdErr;
    if(Tick > StartDelay) {
       SpdErrorSum += SpeedErr;
    } else {
       SpdErrorSum  = 0;
    }
    if(SpdErrorSum > 1200000/KIv) { //���ֱ���
          SpdErrorSum = 1200000/KIv;
    }

    Target = (KPv*SpeedErr + KIv*SpdErrorSum + KDv*DertaSpdError)/1000;
          
    if(Target>SpeedRight)    Target = SpeedRight;
    if(Target<SpeedLeft)     Target = SpeedLeft;

    
    //Target = 300*GPIO_GET_4bit(PORTD,0)/9;
    SetMotorSpeed(Target);
    //SetScopeCh(2);
    //SetScope(CurSpd,0);
    //SetScope(SpeedSet,1);
    
}