#ifndef MMA7660_H
#define MMA7660_H

#include <stdint.h>
#include <stdbool.h>
#include "mma7660_config.h"

/**
 * MMA7660 I2C Address
 */
#define MMA7660_ADDRESS     (0x98>>1)

/**
 * MMA7660 Sensitivity per data sheet
 */
#define MMA7660_SENSITIVITY 21.33

/**
 * Define MMA7660 Registers
 */
#define MMA7660_XOUT_R      0x00
#define MMA7660_YOUT_R      0x01
#define MMA7660_ZOUT_R      0x02
#define MMA7660_TILT_R      0x03
#define MMA7660_INT_R       0x06
#define MMA7660_MODE_R      0x07
#define MMA7660_SR_R        0x08

/**
 * Orientation - used to represent which way
 * the device is facing
 */
typedef enum MMA7660_Orientation {
	MMA7660_Up		= 0x00,
	MMA7660_Down 	= 0x01,
	MMA7660_Right	= 0x02,
	MMA7660_Left 	= 0x03,
	MMA7660_Back 	= 0x04,
	MMA7660_Front 	= 0x05,
	MMA7660_Unknown = 0x06
} MMA7660_Orientation_t;

/**
 * SamplingRate Possible sampling rates (per sec)
 */
enum MMA7660_SamplingRate {
	MMA7660_SMPL_120 = 120,
	MMA7660_SMPL_64 = 64,
	MMA7660_SMPL_32 = 32,
	MMA7660_SMPL_16 = 16,
	MMA7660_SMPL_8 = 8,
	MMA7660_SMPL_4 = 4,
	MMA7660_SMPL_2 = 2,
	MMA7660_SMPL_1 = 1,
};

/**
 * MMA7660_Status device operating status
 * */

enum MMA7660_Status {
	MMA7660_ACTIVE = true,
	MMA7660_INACTIVE = false
};

/**
 * Set device operating mode
 * @param state if true active mode, false standbye mode
 */
void MMA7660_SetActive(bool state);

/**
 * Read raw acceleration data from sensor
 * @param data array to store read from device
 */
void MMA7660_GetRawData(int8_t *data);
/**
 * Read acceleration values from sensor
 * @param data array to store read from device
 */
void MMA7660_GetAccel(float *data);



/**
 * Read raw X data
 * @return X data
 */
int8_t MMA7660_GetXAxisRaw(void);
/**
 * Read Y data
 * @return Y data
 */
int8_t MMA7660_GetYAxisRaw(void);
/**
 * Read raw Z data
 * @return Z data
 */
int8_t MMA7660_GetZAxisRaw(void);
/**
 * Read X data
 * @return X accel in G's
 */




float MMA7660_GetXAxis(void);
/**
 * Read Y data
 * @return Y accel in G's
 */
float MMA7660_GetYAxis(void);
/**
 * Read Z data
 * @return Z accel in G's
 */
float MMA7660_GetZAxis(void);



/**
 * Set sensor sampling rate
 * @param samplerate samples per second
 */
void MMA7660_SetSampleRate(uint8_t samplerate);
/**
 * Gets which side device is on
 * @return Returns front, back, or unknown
 */
MMA7660_Orientation_t MMA7660_GetSide(void);
/**
 * Gets orientation of device
 * @return Returns left, right, down, up, unknown
 */
MMA7660_Orientation_t MMA7660_GetOrientation (void);
/**
 * Writes data byte to given address over I2C
 * @param address i2c address to write to
 * @param data data to write
 */




void MMA7660_WriteByte(unsigned char address, unsigned char data);
/**
 * Read data byte from given address over I2C
 * @param address i2c address to read from
 * @return data byte read
 */
unsigned char MMA7660_ReadReg(unsigned char address);
/**
 * Read data byte(s) from given address over I2C
 * @param address i2c address to read from
 * @param data array to store data read in
 * @param length of data to read in
 */
void MMA7660_ReadBytes(unsigned char address, unsigned char *data, unsigned char length);

#endif
