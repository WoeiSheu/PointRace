/*
 * Sensor.h
 *
 *  Created on: 2012-12-31
 *      Author: Jack
 */

#ifndef SENSOR_H_
#define SENSOR_H_

//�궨��
#define  LNUM  12               //ʹ�õ�и���
#define  AVE   10               //AD�����˲�����
#define  WEI   ADC_12bit        //AD��������
#define  H     300

//��������
void  ReadAD(void);
void  GetPosInfo(void);
///////////////////////////////////////////////////

#endif /* SENSOR_H_ */




