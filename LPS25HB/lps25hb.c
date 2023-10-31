/*
 * lps25hb.c
 *
 *  Created on: Oct 29, 2023
 *      Author: Tomas
 */
#include "lps25hb.h"
#include <math.h>

float firstHeight = 0;
float lastHeight= 0;

float returnHeight(){
	if (whoAmILPS()){
		lps25hb_read_pressure();
		return calculateHeight();
	}else return 0.0;
}


float calculateHeight(){
		const float T = 288.15;
	    const float R = 8.31432;
	    const float g = 9.80665;
	    const float M = 0.0289644;
	    const float L = -0.0065;

	    return (T / L) * (1 - powf(lastHeight  / firstHeight , (R * L) / (g * M)));
}

void lpsInit(){
	i2c_send_byte(LPS25HB_WRITE_ADDRESS, LPS25HB_CTRL_REG1 , LPS25HB_INIT_REG1);
	firstHeight = lps25hb_read_pressure();
}

uint8_t whoAmILPS(){
	if (i2c_master_read_byte(LPS25HB_READ_ADDRESS, LPS25HB_WHO_AM_I_ADDRES) == LPS25HB_WHO_AM_I_VALUE){
		return 1;
	}else return 0;

}

float lps25hb_read_pressure() {
    uint8_t buffer[3];
    //i2c_master_read_bytes(LPS25HB_READ_ADDRESS, PRESS_OUT_XL_ADDRES,buffer, 3);

    buffer[0] = i2c_master_read_byte(LPS25HB_READ_ADDRESS, PRESS_OUT_XL_ADDRES);
    buffer[1] = i2c_master_read_byte(LPS25HB_READ_ADDRESS, PRESS_OUT_L_ADDRES);
    buffer[2] = i2c_master_read_byte(LPS25HB_READ_ADDRESS, PRESS_OUT_H_ADDRES);

    int32_t raw_pressure = (int32_t)buffer[2] << 16 | (int32_t)buffer[1] << 8 | buffer[0];


    float pressure_hPa = raw_pressure / 4096.0f;

    lastHeight = pressure_hPa;

    return pressure_hPa;
}

