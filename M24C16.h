/*
 * M24C16.h
 *
 *  Created on: Nov 27, 2018
 *      Author: Muhammad Adam
 */

#ifndef M24C16_H_
#define M24C16_H_

#include "StandardTypes.h"
#include "I2c.h"

#define SUCCESS 0x01

// write function errors
#define ERROR_START				0x02
#define ERROR_REPEATED_START	0x03
#define ERROR_MT_SLA_W_ACK		0x04	// error while master transmits slave address with write permission with Ack
#define ERROR_MT_SLA_R_ACK		0x05	// error while master transmits slave address with read permission with Ack
#define ERROR_MT_DATA_ACK		0x06	// error while master transmits data with Ack
#define ERROR_MR_DATA_NACK		0x07

// read function errors
#define ERROR_R_START				0x12
#define ERROR_R_REPEATED_START		0x13
#define ERROR_R_MT_SLA_W_ACK		0x14	// error while master transmits slave address with write permission with Ack
#define ERROR_R_MT_SLA_R_ACK		0x15	// error while master transmits slave address with read permission with Ack
#define ERROR_R_MT_DATA_ACK			0x16	// error while master transmits data with Ack
#define ERROR_R_MR_DATA_NACK		0x17

#define ACK 1
#define NACK 0

#endif /* M24C16_H_ */


/**
 * Write byte to external EEPROM
 *
 * @return status of operation
 */
uint8 EEPROM_writeByte(uint16 u16Addr, uint8 u8Data);

/**
 * Read byte from external EEPROM
 *
 * @return status of operation
 */
uint8 EEPROM_readByte(uint16 u16Addr, uint8* u8PtrTOData);
