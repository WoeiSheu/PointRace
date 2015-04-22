/*
 * Misc.h
 * 
 *  Created on: 2015-04-21
 *      Author:Hypocrisy
 */

#ifndef MISC_H_
#define MISC_H_

#define AngleRight  1000
#define AngleLeft  -1000

#define SpeedRight  800
#define SpeedLeft  -800

typedef enum TabN
{ 
   Tab1, Tab2,  
   Tab3, Tab4,
   Tab5, Tab6 
} TabN;

void SetSteerAngle(int16 nAngle);
void SetMotorSpeed(int16 nSpeed);
void StopCar();
void GetData(int16 Ch1,int16 Ch2,int16 Ch3,int16 Ch4);
unsigned short CRC_CHECK(uint8 *Buf, uint8 CRC_CNT);
void OutputData();
int16 abs(int16);
u16 FindMax(u16 ADValue,u16 *max);
void Calc_Deviation_7Gear(int16, int16*, int16*, int16*);

void LoadKpTab(TabN);
void LoadKiTab(TabN);
void LoadKdTab(TabN);
void LoadSpdTab(TabN);
void LoadTabs(TabN Kp,TabN Ki,TabN Kd,TabN Spd);

//Á¥Êô¶È¼ÆËãº¯Êý
void CalcMembership(int32 value,int32 membership[],int32 bound[]);
 
#endif  /*  MISC_H_  */