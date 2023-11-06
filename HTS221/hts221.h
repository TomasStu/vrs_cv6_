/*
 * hts221.h
 *
 *  Created on: Oct 28, 2023
 *      Author: Tomas
 */

#ifndef HTS221_H_
#define HTS221_H_

#include "stm32f3xx.h"
#include "i2c.h"


#define 	HTS221_READ_ADDRESS			0xBFU
#define 	HTS221_WRITE_ADDRESS		0xBEU

#define 	HTS221_WHO_AM_I_VALUE		0xBCU
#define 	HTS221_WHO_AM_I_ADDRES		0x0FU

#define 	CTRL_REG1_ADDRES			0x20U
#define 	INIT_REG1               	0x87U

#define 	TEMP_OUT_H_ADDRES			0x2BU
#define 	TEMP_OUT_L_ADDRES			0x2AU

#define 	HUMIDITY_OUT_H_ADDRESS		0x29U
#define 	HUMIDITY_OUT_L_ADDRESS		0x28U


//HUM PARAMETERS
#define 	H0_rH_x2_ADDRESS      		0x30
#define 	H1_rH_x2_ADDRESS      		0x31
#define 	H0_T0_OUT_L_ADDRESS   		0x36
#define 	H0_T0_OUT_H_ADDRESS   		0x37
#define 	H1_T0_OUT_L_ADDRESS   		0x3A
#define 	H1_T0_OUT_H_ADDRESS   		0x3B

// Calibration coefficients addresses
#define 	T0_degC_x8_ADDR     		0x32
#define 	T1_degC_x8_ADDR     		0x33
#define 	T0_T1_MSB_ADDR      		0x35
#define 	T0_OUT_L_ADDR       		0x3C
#define 	T0_OUT_H_ADDR       		0x3D
#define 	T1_OUT_L_ADDR       		0x3E
#define 	T1_OUT_H_ADDR       		0x3F



uint8_t whoAmI();

void htsInit();
void tempInit();

float rawTemp();
float rawHum();

float returnHum();
float returnTemp();





#endif /* HTS221_H_ */

