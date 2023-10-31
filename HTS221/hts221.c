/*
 * hts221.c
 *
 *  Created on: Oct 28, 2023
 *      Author: Tomas
 */



#include "hts221.h"


uint8_t whoAmI(){
	if (i2c_master_read_byte(HTS221_READ_ADDRESS, HTS221_WHO_AM_I_ADDRES) == HTS221_WHO_AM_I_VALUE){
		return 1;
	}else return 0;

}
uint8_t readTemp(){
    uint8_t buffer[2];

    // Read calibration coefficients
    uint16_t T0_degC_x8 = i2c_master_read_bytes(HTS221_READ_ADDRESS, T0_degC_x8_ADDRES, buffer, 1);
    uint16_t T1_degC_x8 = i2c_master_read_bytes(HTS221_READ_ADDRESS, T1_degC_x8_ADDRES, buffer, 1);
    uint16_t T1_T0_MSB = i2c_master_read_bytes(HTS221_READ_ADDRESS, T1_T0_MSB_ADDRES, buffer, 1);

    T0_degC_x8 |= (T1_T0_MSB & 0x03) << 8; // Add the 2 least significant bits from T1_T0_MSB to T0_degC_x8
    T1_degC_x8 |= (T1_T0_MSB & 0x0C) << 6; // Add the 2 middle bits from T1_T0_MSB to T1_degC_x8

    float T0_degC = T0_degC_x8 / 8.0f;
    float T1_degC = T1_degC_x8 / 8.0f;

    int16_t T0_OUT = i2c_master_read_bytes(HTS221_READ_ADDRESS, T0_OUT_L_ADDRES, buffer, 1);
    T0_OUT |= (int16_t)i2c_master_read_bytes(HTS221_READ_ADDRESS, T0_OUT_H_ADDRES, buffer, 1) << 8;

    int16_t T1_OUT = i2c_master_read_bytes(HTS221_READ_ADDRESS, T1_OUT_L_ADDRES, buffer, 1);
    T1_OUT |= (int16_t)i2c_master_read_bytes(HTS221_READ_ADDRESS, T1_OUT_H_ADDRES, buffer, 1) << 8;

    // Read raw temperature value
    int16_t TEMP_OUT = i2c_master_read_bytes(HTS221_READ_ADDRESS, TEMP_OUT_L_ADDRES, buffer, 1);
    TEMP_OUT |= (int16_t)i2c_master_read_bytes(HTS221_READ_ADDRESS, TEMP_OUT_H_ADDRES, buffer, 1) << 8;

    // Calculate real temperature using linear interpolation
    float real_temperature = ((float)TEMP_OUT - T0_OUT) / (T1_OUT - T0_OUT) * (T1_degC - T0_degC) + T0_degC;

    return real_temperature;

}
uint8_t readHum();

uint8_t convertTemp(uint8_t rawTemp){
	uint8_t temp_data[2];
	i2c_master_read_bytes(HTS221_READ_ADDRESS, TEMP_OUT_L_ADDRES, temp_data, 2);
	int16_t temperature = (temp_data[0] << 8) | temp_data[1];
	return temperature;
}
uint8_t convertHum(uint8_t rawHum);
uint8_t returnTemp(){
	uint8_t rawTemp = 0;
	uint8_t temp = 0;

	if (whoAmI == 1){
		rawTemp = readTemp();
		temp = convertTemp(rawTemp);
		return temp;
	}else return 0;
}
uint8_t returnHum();
