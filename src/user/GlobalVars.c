/*
 * GlobalVars.h
 *
 *  Created on: 2015-03-18
 *      Author: Jack
 */
#include "Device.h"

//ʾ������ʾ
uint8 Scope[16]={0};
//PosInformation  
int16 AD[12] = {0};
int16 Off1,Off2; 
int16 Offset,Slope;
int16 Y1,Y2,Left1,Left2,Right1,Right2,Middle;
//�ٶ�
bool MotorDir;
int16 CurSpdTemp,CurSpd;
int16 SpeedSet;
//�Ƕ�
int16 Angle;

//�Ƿ�ͣ��
bool  IsStop;
int16 StopDelay;
//ϵͳʱ��
int32 Tick;
//���Ա�
int16 Straight;
int16 KpTab[NUM][NUM];
int16 KiTab[NUM][NUM];
int16 KdTab[NUM][NUM];
int16 SpdTab[NUM][NUM];

//�м����ֵ
int16 Left,Right,OffsetKeep,OffsetLeftKeep,OffsetRightKeep,Offset_I,OffsetMiddle,DirKeep,P,D;
int16 P_old[60]={0};
 
//��ʼ��ʱ
int32 StartDelay;
//�µ�
int16 flag_ramp,t_ramp,dt_ramp,d_ramp,t_ramp_delay,ramp;
int16 Left1st,Right1st,Left2nd,Right2nd,posDv1,posDv2,posDvtest,pos_test,pos_DevidePoints[7],pos_TargetAngle[7];
int16 posLoc,posKeep,LeftKeep,RightKeep,pos_I,posBak_test,posBakKeep,posBak,posBak_DevidePoints[7],posBak_TargetAngle[7];
 
//���뿪��
bool PB[8];
//������
int32 ultraSoundTime,ABDistance;
//Test
int32 test[10];

void InitGlobalVars() {
  Off1      = 0;
  Off2      = 0;
  Offset    = 0;
  Slope     = 0;
  SpeedSet  = 0;
  Angle     = 0;
  CurSpdTemp = 0;
  CurSpd    = 0;
  MotorDir  = 0;
  StopDelay = 0; 
  Straight  = 0;
  IsStop    = FALSE;
  LoadTabs(Tab1,Tab1,Tab1,Tab1);

  //2015-03-18���
  Tick = 0;
  Y1=0;  Y2=0;  Left1=0;  Left2=0;  Right1=0;  Right2=0;  Middle=0;
  Left=0;  Right=0;
  OffsetKeep=0;  OffsetLeftKeep=0;  OffsetRightKeep=0;
  Offset_I=0;  OffsetMiddle=0;
  DirKeep=0;
  P=0;
  D=0;
  
  StartDelay = 3000;
  //�µ�
  flag_ramp = 0; dt_ramp = 0; t_ramp = 0; d_ramp = 0;
  t_ramp_delay = 3000;
  for(uint8 i = 0; i < 8; i++) {
    PB[i] = 0;
  }
  //������
  ultraSoundTime = 0; ABDistance = 0;
  
  test[0] = 0;
}