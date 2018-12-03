/*
 * Main.c
 *
 *  Created on: Nov 12, 2018
 *      Author: Muhammad Adam
 */


#include <avr/io.h>
#include <util/delay.h>
#include "M24C16.h"
#include "I2c.h"

int main(void)
{
	DDRD = 0xFF;
	PORTD = 0x00;
	DDRA = 0xFF;
	PORTA = 0x00;

	I2C_initMaster();

	PORTA = EEPROM_writeByte(0x0002,0xAA);
	_delay_ms(100);
	uint8 data = 0;
	uint8 success = EEPROM_readByte(0x0002,&data);
	PORTD = data;
	PORTA = success;

	return 0;

}
