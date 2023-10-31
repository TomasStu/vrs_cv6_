/*
 * lps25hb.h
 *
 *  Created on: Oct 29, 2023
 *      Author: Tomas
 */


#ifndef LPS25HB_H_
#define LPS25HB_H_
/* INCLUDES */
#include "stm32f3xx.h"
#include "i2c.h"

#endif /* LPS25HB_H_ */
/* GLOBAL */


/* MACROS */

#define 	LPS25HB_READ_ADDRESS		0xBBU
#define 	LPS25HB_WRITE_ADDRESS		0xBAU

#define 	LPS25HB_WHO_AM_I_VALUE		0xBDU
#define 	LPS25HB_WHO_AM_I_ADDRES		0x0FU

#define 	PRESS_OUT_XL_ADDRES      	0x28U
#define 	PRESS_OUT_L_ADDRES       	0x29U
#define 	PRESS_OUT_H_ADDRES       	0x2AU

#define 	LPS25HB_CTRL_REG1                	0x20U
#define 	LPS25HB_INIT_REG1               	0x90U //PD = 1 ODR 1Hz

/* FUNCTIONS */

float returnHeight();
uint8_t whoAmILPS();
void lpsInit();
float calculateHeight();
float lps25hb_read_pressure();

