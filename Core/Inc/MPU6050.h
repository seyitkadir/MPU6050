/*
 * MPU6050.h
 *
 *  Created on: May 8, 2024
 *      Author: seyit
 */

#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_
#include <stdint.h>
#include <stdbool.h>

typedef union
{
    struct
    {
        uint8_t clkSel      : 3; //clk source 0: 8Mhz
        uint8_t	temp_dıs    : 1; //read temperature disable
        uint8_t reserved    : 1;
        uint8_t cycle 		: 1;
        uint8_t sleep 		: 1; // for 1 sleep mode
        uint8_t device_rst	: 1; // for 1 sensor reset
    } Fields;
    uint8_t Value;
} PWRMNGNNT_t;

typedef union
{
    struct
    {
        uint8_t reserved    : 3;
        uint8_t	fs_sel      : 2; // gyro full scale range 0: +-250, 1: +- 500, 2: +-1000, 3: +-2000
        uint8_t zg_st       : 1; // self Test Z
        uint8_t yg_st 		: 1; // self Test Y
        uint8_t xg_st 		: 1; // self Test X
    } Fields;
    uint8_t Value;
} GyroConfig_t;

typedef union
{
    struct
    {
        uint8_t reserved    : 3;
        uint8_t	afs_sel     : 2; // gyro full scale range 0: +-2g, 1: +- 4g, 2: +-8g, 3: +-16
        uint8_t za_st       : 1; // self Test Z
        uint8_t ya_st 		: 1; // self Test Y
        uint8_t xa_st 		: 1; // self Test X
    } Fields;
    uint8_t Value;
} AccelConfig_t;
typedef struct
{
	float Ax;
	float Ay;
	float Az;
}MPU6050AccelValue_t;

typedef struct
{
	float Gx;
	float Gy;
	float Gz;
}MPU6050GyroValue_t;

typedef enum
{
	RESULT_OK,
	RESULT_ERROR,
}Result_t;

Result_t MPU6050Init(void);
Result_t MPU6050SetConf(void);
void MPU6050_Read_Accel(void);
void MPU6050_Read_Gyro(void);
MPU6050AccelValue_t* getAccel(void);
MPU6050GyroValue_t* getGyro(void);
#endif /* INC_MPU6050_H_ */
