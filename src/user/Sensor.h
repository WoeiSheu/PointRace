/*
 * Sensor.h
 *
 *  Created on: 2012-12-31
 *      Author: Jack
 */

#ifndef SENSOR_H_
#define SENSOR_H_

//宏定义
#define  LNUM  12               //使用电感个数
#define  AVE   10               //AD采样滤波次数
#define  WEI   ADC_12bit        //AD采样精度
#define  H     300

//函数声明
void  ReadAD(void);
void  GetPosInfo(void);
///////////////////////////////////////////////////

#endif /* SENSOR_H_ */




