/*
 * I2c.c
 *
 *  Created on: Nov 12, 2018
 *      Author: Muhammad Adam
 */


#include "I2c.h"
#include <avr/io.h>


void I2C_initMaster(void){
//	 adjust the frequency
//	 BitRate = 400 kHz , FCPU = 8 MHz
	TWBR = 0x02;
	TWSR &= ~((1<<TWPS1) | (1<<TWPS0));
	// enable I2C,
	TWCR |= (1<<TWEN);
}

void I2C_initSlave(void){
	// assign the slave address and availability to general call
	TWAR = 0b10101010;
	// enable I2C
	TWCR |= (1<<TWEN);
	// enable I2C, acknowledgment and start
	TWCR |= (1<<TWEN) | (1<<TWEA) | (1<<TWINT);
}

// A master function to send start condition
void I2C_start(void){
	// enable I2C,generate start condition and start sending the start condition
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	// wait for the transmission to complete successfully (TWINT is set)
	while (!(TWCR & (1<<TWINT)))
		;
}

// A master function to send stop condition
void I2C_stop(void){
	// enable I2C, generate stop condition and start sending the stop condition
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

// A master/slave function to write to bus
void I2C_write(unsigned char data){

	TWDR = data;
	// enable I2C and start transmission
	TWCR = (1<<TWEN) | (1<<TWINT);
	// wait for the transmission to complete successfully (TWINT is set)
	while (!(TWCR & (1<<TWINT)))
		;
}

// A master/slave function to read from bus
unsigned char I2C_read(unsigned char withAck){
	if (withAck == 1){
		// enable I2C, start receiving, enable acknowledgment
		TWCR = (1<<TWEN) | (1<<TWINT) | (1<<TWEA);
	}else{
		// enable I2C, start receiving
		TWCR = (1<<TWEN) | (1<<TWINT);
	}
	// wait for the receiving to complete
	while (!(TWCR & (1<<TWINT)));
	return TWDR;
}

// A slave function to listen if it's addressed
void I2C_listen(void){
	while (!(TWCR & (1<<TWINT))); //wait to be addressed
}

unsigned char I2C_getStatus(void){
	return TWSR & (0xF8) ; //0xF8: to ignore the least 3 bits
}
