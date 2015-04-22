/*
 * GlobalVars.h
 *
 *  Created on: 2015-03-18
 *      Author: Jack
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#define NUM 7

//ʾ������ʾ
extern uint8 Scope[16];
//�ٶ�ֵ 
extern int16 SpeedSet; 
extern int16 CurSpdTemp,CurSpd;
extern bool MotorDir;
//�Ƕ�ֵ 
extern int16 Angle; 
//����ֵ
extern int16 AD[12];
extern int16 Off1,Off2;
extern int16 Offset,Slope;
extern int16 Y1,Y2,Left1,Left2,Right1,Right2,Middle;   //AD������ı���
//�Ƿ�ͣ��
extern bool  IsStop;
extern int16 StopDelay;
//ϵͳʱ��
extern int32 Tick;
//���Ա�
extern int16 Straight;
extern int16 KpTab[NUM][NUM];
extern int16 KiTab[NUM][NUM];
extern int16 KdTab[NUM][NUM];
extern int16 SpdTab[NUM][NUM];

//�м����ֵ
extern int16 Left,Right,OffsetKeep,OffsetLeftKeep,OffsetRightKeep,Offset_I,OffsetMiddle,DirKeep,P_old[60],P,D;
//��ʼ��ʱ
extern int32 StartDelay;
//�µ�
extern int16 flag_ramp,t_ramp,dt_ramp,d_ramp,t_ramp_delay,ramp;
extern int16 Left1st,Right1st,Left2nd,Right2nd,posDv1,posDv2,posDvtest,pos_test,pos_DevidePoints[7],pos_TargetAngle[7];
extern int16 posLoc,posKeep,LeftKeep,RightKeep,pos_I,posBak_test,posBakKeep,posBak,posBak_DevidePoints[7],posBak_TargetAngle[7];

//���뿪��
extern bool PB[8];
//������
extern int32 ultraSoundTime,ABDistance;
//Test
extern int32 test[10];

#endif /* GLOBAL_H_ */