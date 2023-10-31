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

#define 	TEMP_OUT_H_ADDRES			0x2BU
#define 	TEMP_OUT_L_ADDRES			0x2AU

#define 	HUMIDITY_OUT_H_ADDRES		0x29U
#define 	HUMIDITY_OUT_L_ADDRES		0x28U

// I2C Address
#define HTS221_READ_ADDRESS     0xBFU
// Register Addresses
#define TEMP_OUT_L_ADDRES       0x2AU
#define TEMP_OUT_H_ADDRES       0x2BU
#define T0_degC_x8_ADDRES       0x32U
#define T1_degC_x8_ADDRES       0x33U
#define T1_T0_MSB_ADDRES        0x35U
#define T0_OUT_L_ADDRES         0x3CU
#define T0_OUT_H_ADDRES         0x3DU
#define T1_OUT_L_ADDRES         0x3EU
#define T1_OUT_H_ADDRES         0x3FU


uint8_t  whoAmI();
uint8_t  readTemp();
uint8_t  readHum();
uint8_t  convertTemp(uint8_t rawTemp);
uint8_t  convertHum(uint8_t rawHum);
uint8_t returnHum();
uint8_t  returnTemp();


#endif /* HTS221_H_ */

