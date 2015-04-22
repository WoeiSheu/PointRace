/*
 * Device.h
 *
 *  Created on: 2012-12-31
 *      Author: Jack
 */

#ifndef DEVICE_H_
#define DEVICE_H_

//---------------------------------------------------------------------------
// Bit Definitions:
//
#define Bit(n)               1<<n
#define SetBit(T,n)         ((T) |= (1<<n))
#define ClrBit(T,n)         ((T) &= ~(1<<n))

#define pi                  3.1415

//---------------------------------------------------------------------------
// Include All Header Files:
//  
/* Including needed modules to compile this module/procedure */ 



#include "include.h"
#include "common.h" 

//user header
#include "Check.h"
#include "Sensor.h"
#include "FuzzyCtrl.h" 
#include "GlobalVars.h"
#include "InitAll.h"
#include "Misc.h"

#endif /* DEVICE_H_ */
