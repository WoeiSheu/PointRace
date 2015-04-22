/*
 * Sensor.c
 *
 *  Created on: 2012-12-31
 *      Author: Jack
 */
#include "Device.h"
//int16  Norm = 0;

u16 max[LNUM] = {1000,1000,1000,1000,1000,1000,1000};
u16 Left1Max=1300,Y1Max=1350,Left2Max=1200,MiddleMax=1450,Right2Max=1200,Y2Max=1208,Right1Max=900;

void ReadAD(void)
{
    //已经含有均值滤波功能
    AD[0]=ad_ave(ADC0, AD8,WEI, AVE);
    AD[1]=ad_ave(ADC0, AD9,WEI, AVE);
    AD[2]=ad_ave(ADC0, AD12 ,WEI, AVE);
    AD[3]=ad_ave(ADC0, AD13 ,WEI, AVE);
    AD[4]=ad_ave(ADC1, AD14,WEI, AVE);
    AD[5]=ad_ave(ADC1, AD15,WEI, AVE);  
    AD[6]=ad_ave(ADC0, AD14,WEI, AVE);  
    AD[7]=ad_ave(ADC0, AD15,WEI, AVE);
    
/*
    if( Tick < StartDelay ) {
      Left1Max  = FindMax(AD[7],&max[0]);
      Y1Max     = FindMax(AD[6],&max[1]);
      Left2Max  = FindMax(AD[5],&max[2]);
      
      MiddleMax = FindMax(AD[4],&max[4]);
      
      Right2Max = FindMax(AD[2],&max[5]);
      Y2Max     = FindMax(AD[1],&max[6]);
      Right1Max = FindMax(AD[0],&max[7]);
    }
*/
    Left1  = AD[0]*2000/Left1Max;
    Y1     = AD[1]*2000/Y1Max;
    Left2  = AD[2]*2000/Left2Max;
    Middle = AD[4]*2200/MiddleMax;
    Right2 = AD[5]*2000/Right2Max;
    Y2     = AD[6]*2000/Y2Max;
    Right1 = AD[7]*2000/Right1Max;
    
    //AD[8]=ad_ave(ADC1, AD14,WEI, AVE);  
    //AD[9]=ad_ave(ADC1, AD5a,WEI, AVE);
    //AD[10]=ad_ave(ADC0, AD15,WEI, AVE); 
    //AD[11]=ad_ave(ADC0, AD14,WEI, AVE);      
}
 
void GetPosInfo(void) {
  int i,km;
  int32 ky1,ky2;
    
  ReadAD();
  
  ky1 = Y1*Y1/Y1Max; 
  ky2 = Y2*Y2/Y2Max; 
  Left  = Left1+ky1;
  Right = Right1+ky2;
  
  Offset = Right-Left;
 
  if(Left1>=700&&Right1>=700) {
    OffsetKeep=Offset;
    OffsetLeftKeep=Left;
    OffsetRightKeep=Right;
  }
  
  if(Left1<700&&OffsetKeep>0) {
      Offset_I  = OffsetKeep+(OffsetLeftKeep-Left)*3;
  } else {
      if(Right1<700&&OffsetKeep<0) {
        Offset_I = OffsetKeep+(-OffsetRightKeep+Right)*3;
      } else {
        Offset_I  = Offset;
      }
  }

  Offset_I = Offset_I/7;
  //OffsetMiddle = (MiddleMax - Middle)/6;

  OffsetMiddle = (2200 - Middle)/6;
  
  if(OffsetMiddle<=0) {
     OffsetMiddle=0;
  }
  if(Left>Right) {
     OffsetMiddle = -OffsetMiddle;
  }
  if(Left>=450&&Right>=450) {
     if(OffsetMiddle>0) {
        DirKeep = 1;
     } else {
        DirKeep = -1;
     }
  }
  
  OffsetMiddle = DirKeep*abs(OffsetMiddle);
  
  if(Middle>=900) {
    //km = 1000/(abs(Offset_I)-30);
    km = 1000 - (abs(Offset_I) - 35)*50;
    if(km <= 0) km = 0;
    
    if(abs(Offset_I)<=35)
      km=1000;
  } else {
    km=0;
  }
  P  = (Offset_I*km+OffsetMiddle*(1000-km))/1000;


///////////////////////////////////////////////////////////////////////////////
//坡道检测及处理 
if( PB[0] == 1 ) {
  Left1st  = (Left1 + ky1)/7;
  Right1st = (Right1+ ky2)/7;
  Left2nd  = (Left2 + ky1)/7;
  Right2nd = (Right2+ ky2)/7;


  posDv1 = Right2nd*Right1st*(Left2nd  - Left1st);
  posDv2 = Left1st *Left2nd *(Right2nd - Right1st);

  posDvtest=(posDv1+posDv2 )/150;

  if(posDvtest!=0) {
    pos_test=( posDv1-posDv2 )/( (posDv1+posDv2 )/150 );     //4电感公式
  }

  Calc_Deviation_7Gear(pos_test, &posLoc, pos_DevidePoints, pos_TargetAngle);
  
  if(posLoc>150)  posLoc=150;
  if(posLoc<-150) posLoc=-150; 
  
  if(posLoc==230) {            //这是防止在一侧最大时突然变到另一侧最大
    if(pos_test==-230) {
         posLoc=230;
    }
  }
  if(posLoc==-230) {
    if(pos_test==230) {
         posLoc=-230;
    }
  }

  if((Left1+Left2)>=800&&(Right1+Right2)>=1000) 
  {
    posKeep  = posLoc;
    LeftKeep = Left1st+Left2nd;
    RightKeep= Right1st+Right2nd;
  }

  if((Left1+Left2)<800&&posKeep>0) {
    pos_I = posKeep+(LeftKeep-(Left1st+Left2nd))*3;
  } else {    
    if((Right1+Right2)<1000&&posKeep<0) {
      pos_I  = posKeep+(-RightKeep+(Right1st+Right2nd))*3;
    } else {            
      pos_I  = posLoc;
    }
  }
  
  posBak_test  = (Right2-Left2)/3;



  if(Left2>=180&&Right2>=180) 
  {
    posBakKeep=posBak_test;
  }
  if(Left2<180&&posBakKeep>0) 
  {
      posBak_test  = (Left2Max-Left2)/5;
  } 
  else 
  {    
        if(Right2<180&&posBakKeep<0) 
        {
            posBak_test  = -(Right2Max-Right2)/5;
        }
        else 
        {            
          posBak_test  = posBak_test;
        }           
  }

  Calc_Deviation_7Gear(posBak_test, &posBak, posBak_DevidePoints, posBak_TargetAngle);

  if(posBak>120) posBak=120;
  if(posBak<-120) posBak=-120;
  
  
  
  if((Middle>=3000||(Left1+Right1>2800))&&flag_ramp==0) {   //上坡检测
    flag_ramp=1;
  }
  if( t_ramp>600 && ( Middle>=3000||(Left1+Right1>2800) ) && flag_ramp==1 ) {  //下坡检测
    //flag_ramp=0;
    dt_ramp=t_ramp;
    d_ramp=1;
  }
  
  if(d_ramp==1&&t_ramp>dt_ramp+600)   //下坡延时清标志位
  {
      flag_ramp=0;
      d_ramp=0;
  }
   
  if(t_ramp>t_ramp_delay)  //3s强制转换
  {
      flag_ramp=0;
      t_ramp=0;
  }
   
   
//坡道处理切四电感 
  if(flag_ramp==1) {    
    P=posLoc;
    //P=Offset_I;
    ramp=300;//蓝牙发送标志
  } else {
    ramp=0;
  }
  if(flag_ramp==1||t_ramp!=0) t_ramp++;    //检测到坡道开始延时
}
//////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////
//坡道处理二
if( PB[2] == 1 ) {
  if( (Middle>=3000 || Left1+Right1 > 3000)&&flag_ramp==0) {   //上坡检测
    flag_ramp = 1;
  }
  
  if( t_ramp>1000 && Middle>=2800 && flag_ramp==1 ) {  //下坡检测
    //flag_ramp=0;
    dt_ramp=t_ramp;
    d_ramp=1;
  }
  
  if(d_ramp==1&&t_ramp>dt_ramp+200) //下坡延时清标志位
  {
      flag_ramp=0;
      d_ramp=0;
  }
  
  if(t_ramp>t_ramp_delay)  //3s强制转换
  {
      flag_ramp=0;
      t_ramp=0;
  }
  
  if(flag_ramp==1) { 
    P = Offset_I/5;
    //P = (Left1-Right1) * 200 / (Left1+Right1);
    ramp=300;//蓝牙发送标志
  } else {
    ramp=0;
  }
  if(flag_ramp==1||t_ramp!=0) t_ramp++;    //检测到坡道开始延时
}
////////////////////////////////////////////////////////////////////////////

  
  //if(abs(Offset_I)<=50)
  //   P = P/5;

  for(i=0;i<30;i++ ) {
    P_old[i]=P_old[i+1];
  }

  P_old[30]=P;

  D=P-P_old[0]; 

  if(D>200) D=200;
  if(D<-200) D=-200;
}