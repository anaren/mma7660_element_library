#include "mma7660.h"
#include "../i2c/i2c.h"
#include "../generic/generic.h"
#include <stdlib.h>

static bool active;

void MMA7660_SetActive(bool state)
{
	active = state;
	unsigned char modereg = MMA7660_ReadReg(MMA7660_MODE_R);
	modereg &= ~(1<<0);

	//If it somehow was in testmode, disable that
	if (modereg && (1<<2)) {
		modereg &= ~(1<<2);
		MMA7660_WriteByte(MMA7660_MODE_R, modereg);
	}

	modereg += state;
	MMA7660_WriteByte(MMA7660_MODE_R, modereg);
}

uint8_t MMA7660_GetSingleAxisRaw( uint8_t number )
{
	bool active_old = active;
	if (!active) {
		MMA7660_SetActive(true);
		AIR_udelay(13000); //turn on time from standby -> active
	}

	signed char temp;
	bool alert;

	do {
		alert = false;
		temp = MMA7660_ReadReg(MMA7660_XOUT_R + number);
		if (temp > 63)
			alert = true;
		if (temp > 31)
			temp += 128+64;
	} while (alert);

	if (!active_old)
		MMA7660_SetActive(false);

	return temp ;
}

void MMA7660_GetRawData(int8_t *data)
{
	bool active_old = active;
	if (!active) {
		MMA7660_SetActive(true);
		AIR_udelay(13000); //turn on time from standby -> active
	}

	unsigned char temp[3];
	bool alert;

	do {
		uint8_t i;
		alert = false;
		MMA7660_ReadBytes(MMA7660_XOUT_R, temp, 3);
		for (i = 0; i<3; i++) {
			if (temp[i] > 63)
				alert = true;
			if (temp[i] > 31)
				temp[i] += 128+64;
			data[i] = (signed char)temp[i];
		}
	} while (alert);

	if (!active_old)
		MMA7660_SetActive(false);
}


void MMA7660_GetAccel(float *data)
{
	int i;
	int8_t intdata[3];
	MMA7660_GetRawData(intdata);
	for (i = 0; i<3; i++)
		data[i] = intdata[i]/MMA7660_SENSITIVITY;
}

float MMA7660_GetSingleAxisAccel( uint8_t number )
{
	bool active_old = active;
	if (!active) {
		MMA7660_SetActive(true);
		AIR_udelay(13000); //turn on time from standby -> active
	}

	signed char temp;
	bool alert;

	do {
		alert = false;
		temp = MMA7660_ReadReg(MMA7660_XOUT_R + number);
		if (temp > 63)
			alert = true;
		if (temp > 31)
			temp += 128+64;
	} while (alert);

	if (!active_old)
		MMA7660_SetActive(false);

	return temp / MMA7660_SENSITIVITY;

}

float MMA7660_GetXAxis( void )
{
	return MMA7660_GetSingleAxisAccel(0);
}

float MMA7660_GetYAxis( void )
{
	return MMA7660_GetSingleAxisAccel(1);
}

float MMA7660_GetZAxis( void )
{
	return MMA7660_GetSingleAxisAccel(2);
}

int8_t MMA7660_GetXAxisRaw( void )
{
	return MMA7660_GetSingleAxisRaw(0);
}

int8_t MMA7660_GetYAxisRaw( void )
{
	return MMA7660_GetSingleAxisRaw(1);
}

int8_t MMA7660_GetZAxisRaw( void )
{
	return MMA7660_GetSingleAxisRaw(2);
}

void MMA7660_SetSampleRate(uint8_t samplerate)
{
	bool active_old = active;
	MMA7660_SetActive(false);							   //Not allowed to be active to change anything
	uint8_t rates[] = {120, 64, 32, 16, 8, 4, 2, 1};	//Alowed samplerates (and their number in array is also number required for MMA)
	uint16_t sampleLoc = 0, sampleError = 10000, temp;
	uint8_t i;
	for (i = 0; i<8; i++) {
		temp = abs( rates[i] - samplerate );
		if (temp<sampleError) {
			sampleLoc = i;
			sampleError=temp;
		}
	}

	//Update the samplerate reg
	temp = MMA7660_ReadReg(MMA7660_SR_R);
	temp &= ~0x07;								  //Awake sample rate are lowest 3 bit
	temp |= sampleLoc;
	MMA7660_WriteByte(MMA7660_SR_R, temp);
	samplerate = rates[sampleLoc];
	MMA7660_SetActive(active_old);							  //Restore previous active state
}


MMA7660_Orientation_t MMA7660_GetSide( void )
{
	char tiltreg = MMA7660_ReadReg(MMA7660_TILT_R);
	//We care about 2 LSBs
	tiltreg &= 0x03;
	if (tiltreg == 0x01)
		return MMA7660_Front;
	if (tiltreg == 0x02)
		return MMA7660_Back;
	return MMA7660_Unknown;
}

MMA7660_Orientation_t MMA7660_GetOrientation( void )
{
	char tiltreg = MMA7660_ReadReg(MMA7660_TILT_R);

	//We care about bit 2, 3 and 4 (counting from zero)
	tiltreg &= 0x07<<2;
	tiltreg >>= 2;
	if (tiltreg == 0x01)
		return MMA7660_Left;
	if (tiltreg == 0x02)
		return MMA7660_Right;
	if (tiltreg == 0x05)
		return MMA7660_Down;
	if (tiltreg == 0x06)
		return MMA7660_Up;
	return MMA7660_Unknown;
}


void MMA7660_WriteByte(unsigned char address, unsigned char data)
{
	unsigned char temp[2];
	temp[0]=address;
	temp[1]=data;

	AIR_I2C_Write(MMA7660_ADDRESS,temp,2);
}

unsigned char MMA7660_ReadReg(unsigned char address)
{
	unsigned char retval;

	AIR_I2C_ComboRead(MMA7660_ADDRESS,&address,1,&retval,1);

	return retval;
}

void MMA7660_ReadBytes(unsigned char address, unsigned char *data, unsigned char length)
{
	AIR_I2C_ComboRead(MMA7660_ADDRESS,&address,1,data,length);
}
