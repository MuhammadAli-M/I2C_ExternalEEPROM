/*
 * M24C16.c
 *
 *  Created on: Nov 27, 2018
 *      Author: Adam
 */

#include "M24C16.h"


/**
 * Write byte to external EEPROM
 *
 * @return status of operation
 */
uint8 EEPROM_writeByte(uint16 u16Addr, uint8 u8Data){
	uint8 address = 0xA0;

	I2C_start();
	if (I2C_getStatus() != TW_START){ // check that start has been sent
		return ERROR_START;
	}
	address = 0xA0 | ((uint8)((u16Addr>>8)<<1)); // Address Byte should be 1 0 1 0 A10 A9 A8 RW'
	I2C_write(address);
	if(I2C_getStatus() != TW_MT_SLA_W_ACK){ // check that ACK has been received
		return ERROR_MT_SLA_W_ACK;
	}

	I2C_write((uint8)(u16Addr & 0x00FF));
	if (I2C_getStatus() != TW_MT_DATA_ACK){ // check that ACK has been received
		return ERROR_MT_DATA_ACK;
	}

	I2C_write(u8Data);
	if (I2C_getStatus() != TW_MT_DATA_ACK){ // check that ACK has been received
		return ERROR_MT_DATA_ACK;
	}

	I2C_stop();

	return SUCCESS;
}


/**
 * Read byte from external EEPROM
 *
 * @return status of operation
 */
uint8 EEPROM_readByte(uint16 u16Addr, uint8* u8PtrTOData){

	// part 1: start writing the address
	uint8 address = 0xA0;

	I2C_start();
	if (I2C_getStatus() != TW_START){ // check that start has been sent
		return ERROR_R_START;
	}

	address = 0xA0 | ((uint8)((u16Addr>>8)<<1)); // Address Byte should be 1 0 1 0 A10 A9 A8 RW'
	I2C_write(address);
	if(I2C_getStatus() != TW_MT_SLA_W_ACK){ // check that ACK has been received
		return ERROR_R_MT_SLA_W_ACK;
	}

	I2C_write((uint8)(u16Addr & 0x00FF));
	if (I2C_getStatus() != TW_MT_DATA_ACK){ // check that ACK has been received
		return ERROR_R_MT_DATA_ACK;
	}

	// part 2: start reading the data
	address = 0xA1;
	I2C_start();
	if (I2C_getStatus() != TW_REP_START){ // check that repeated start has been sent
		return ERROR_R_REPEATED_START;
	}
	address = 0xA1 | ((uint8)((u16Addr>>8)<<1)); // Address Byte should be 1 0 1 0 A10 A9 A8 RW'
	I2C_write(address);
	if(I2C_getStatus() != TW_MT_SLA_R_ACK){ // check that ACK has been received
		return ERROR_R_MT_SLA_R_ACK;
	}

	*u8PtrTOData = I2C_read(NACK);
	if (I2C_getStatus() != TW_MR_DATA_NACK){ // check that ACK has been received
		return ERROR_R_MR_DATA_NACK;
	}

	I2C_stop();

	return SUCCESS;
}

