/*
 * MPU6050.c
 *
 *  Created on: May 8, 2024
 *      Author: seyit
 */
#include "MPU6050.h"
#include "main.h"
#include "i2c.h"

MPU6050AccelValue_t  Accel;
MPU6050GyroValue_t	  Gyro;
extern Result_t result;
#define MPU6050_ADDR 0xD0
#define SMPLRT_DIV_REG 0x19
#define GYRO_CONFIG_REG 0x1B
#define ACCEL_CONFIG_REG 0x1C
#define ACCEL_XOUT_H_REG 0x3B
#define GYRO_XOUT_H_REG 0x43
#define PWR_MGMT_1_REG 0x6B
#define WHO_AM_I_REG 0x75

int16_t Accel_X_RAW = 0;
int16_t Accel_Y_RAW = 0;
int16_t Accel_Z_RAW = 0;

int16_t Gyro_X_RAW = 0;
int16_t Gyro_Y_RAW = 0;
int16_t Gyro_Z_RAW = 0;

Result_t MPU6050Init()
{
	uint8_t check;
	HAL_I2C_Mem_Read (&hi2c1, MPU6050_ADDR,WHO_AM_I_REG,1, &check, 1, 1000);
	if(check == 104)
	{
		return RESULT_OK;
	}
	return RESULT_ERROR;
}
Result_t MPU6050SetConf()
{
	uint8_t data = 0;
	PWRMNGNNT_t pwrConf;
	GyroConfig_t gyroConf;
	AccelConfig_t accelConf;
	// Set DATA RATE of 1KHz by writing SMPLRT_DIV register
	data = 0x07;
	if(HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, SMPLRT_DIV_REG, 1, &data, 1, 1000) != HAL_OK)
	{
		return RESULT_ERROR;
	}
	pwrConf.Value = 0;
	data = *(uint8_t*)&pwrConf;
	if(HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR,PWR_MGMT_1_REG , 1, &data, 1, 1000) != HAL_OK)
	{
		return RESULT_ERROR;
	}
	gyroConf.Value = 0;
	data = *(uint8_t*)&gyroConf;
	if(HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, ACCEL_CONFIG_REG, 1, &data, 1, 1000) != HAL_OK)
	{
		return RESULT_ERROR;
	}
	accelConf.Value = 0;
	data = *(uint8_t*)&accelConf;
	if(HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, GYRO_CONFIG_REG, 1, &data, 1, 1000) != HAL_OK)
	{
		return RESULT_ERROR;
	}
	return RESULT_OK;
}

void MPU6050_Read_Accel (void)
{
	uint8_t Rec_Data[6];

	// Read 6 BYTES of data starting from ACCEL_XOUT_H register

	if(HAL_I2C_Mem_Read (&hi2c1, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, Rec_Data, 6, 1000) == HAL_OK)
	{
		Accel_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data [1]);
		Accel_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data [3]);
		Accel_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data [5]);



		Accel.Ax = Accel_X_RAW/16384.0;
		Accel.Ay = Accel_Y_RAW/16384.0;
		Accel.Az = Accel_Z_RAW/16384.0;
		result = RESULT_OK;
		HAL_Delay(100);
	}
	result = RESULT_ERROR;
}
void MPU6050_Read_Gyro (void)
{
	uint8_t Rec_Data[6];

	// Read 6 BYTES of data starting from ACCEL_XOUT_H register

	if(HAL_I2C_Mem_Read (&hi2c1, MPU6050_ADDR, GYRO_XOUT_H_REG, 1, Rec_Data, 6, 1000) == HAL_OK)
	{
		Gyro_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data [1]);
		Gyro_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data [3]);
		Gyro_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data [5]);



		Gyro.Gx = Gyro_X_RAW/16384.0;
		Gyro.Gy = Gyro_Y_RAW/16384.0;
		Gyro.Gz = Gyro_Z_RAW/16384.0;
		result = RESULT_OK;
		HAL_Delay(100);
	}
	result = RESULT_ERROR;
}


