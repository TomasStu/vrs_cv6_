/*
 * hts221.c
 *
 *  Created on: Oct 28, 2023
 *      Author: Tomas
 */



#include "hts221.h"

int16_t T0_OUT, T1_OUT;
float T0_degC, T1_degC;


void htsInit(){
	if (whoAmI){
		i2c_send_byte(HTS221_WRITE_ADDRESS,CTRL_REG1_ADDRES, INIT_REG1);
		readTemp();
	}

}

uint8_t whoAmI(){
	if (i2c_master_read_byte(HTS221_READ_ADDRESS, HTS221_WHO_AM_I_ADDRES) == HTS221_WHO_AM_I_VALUE){
		return 1;
	}else return 0;

}
void readTemp(){
	 uint8_t T0_degC_x8, T1_degC_x8;
	    uint8_t T0_T1_msb;

	    // Read calibration coefficients
	    T0_degC_x8 = i2c_master_read_byte(HTS221_READ_ADDRESS, T0_degC_x8_ADDR);
	    T1_degC_x8 = i2c_master_read_byte(HTS221_READ_ADDRESS, T1_degC_x8_ADDR);
	    T0_T1_msb = i2c_master_read_byte(HTS221_READ_ADDRESS, T0_T1_MSB_ADDR);

	    T0_degC = (T0_degC_x8 + ((T0_T1_msb & 0x03) << 8)) / 8.0;
	    T1_degC = (T1_degC_x8 + ((T0_T1_msb & 0x0C) << 6)) / 8.0;

	    T0_OUT = (i2c_master_read_byte(HTS221_READ_ADDRESS, T0_OUT_L_ADDR) | (i2c_master_read_byte(HTS221_READ_ADDRESS, T0_OUT_H_ADDR) << 8));
	    T1_OUT = (i2c_master_read_byte(HTS221_READ_ADDRESS, T1_OUT_L_ADDR) | (i2c_master_read_byte(HTS221_READ_ADDRESS, T1_OUT_H_ADDR) << 8));

}
uint8_t readHum();

uint8_t convertTemp(uint8_t rawTemp){

}
uint8_t convertHum(uint8_t rawHum);
float returnTemp(){
		int16_t TEMP_OUT;

		uint8_t buffer[2];
		//i2c_master_read_bytes(HTS221_READ_ADDRESS, TEMP_OUT_L_ADDRES,buffer, 2);
		buffer[0] = i2c_master_read_byte(HTS221_READ_ADDRESS,TEMP_OUT_L_ADDRES);
		buffer[1] = i2c_master_read_byte(HTS221_READ_ADDRESS,TEMP_OUT_H_ADDRES);
	    TEMP_OUT = (buffer[1] << 8) | buffer[0];


	    return ((TEMP_OUT - T0_OUT) * (T1_degC - T0_degC)) / (float)(T1_OUT - T0_OUT) + T0_degC;
}


float returnHum() {
		uint8_t H0_rH_x2 = i2c_master_read_byte(HTS221_READ_ADDRESS, H0_rH_x2_ADDRESS);
	    uint8_t H1_rH_x2 = i2c_master_read_byte(HTS221_READ_ADDRESS, H1_rH_x2_ADDRESS);

	    int16_t H0_T0_out = ((int16_t)i2c_master_read_byte(HTS221_READ_ADDRESS, H0_T0_OUT_H_ADDRESS) << 8)
	                      | i2c_master_read_byte(HTS221_READ_ADDRESS, H0_T0_OUT_L_ADDRESS);
	    int16_t H1_T0_out = ((int16_t)i2c_master_read_byte(HTS221_READ_ADDRESS, H1_T0_OUT_H_ADDRESS) << 8)
	                      | i2c_master_read_byte(HTS221_READ_ADDRESS, H1_T0_OUT_L_ADDRESS);

	    int16_t H_T_out = ((int16_t)i2c_master_read_byte(HTS221_READ_ADDRESS, HUMIDITY_OUT_H_ADDRESS) << 8)
	                    | i2c_master_read_byte(HTS221_READ_ADDRESS, HUMIDITY_OUT_L_ADDRESS);

	    float H0_rH = H0_rH_x2 / 2.0f;
	    float H1_rH = H1_rH_x2 / 2.0f;

	    float humidity = ((H_T_out - H0_T0_out) * (H1_rH - H0_rH)) / (H1_T0_out - H0_T0_out) + H0_rH;

	    if (humidity > 100.0f) humidity = 100.0f; // Clip to 100% if needed
	    if (humidity < 0.0f) humidity = 0.0f;     // Clip to 0% if needed

	    return humidity;
}

