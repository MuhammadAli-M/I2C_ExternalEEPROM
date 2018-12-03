/*
 * I2c.h
 *
 *  Created on: Nov 12, 2018
 *      Author: Muhammad Adam
 */
#ifndef I2C_H_
#define I2C_H_


/* I2C Status Bits in the TWSR Register with prescalar bit = 0*/
#define TW_START         0x08 // start has been sent
#define TW_REP_START     0x10 // repeated start
#define TW_MT_SLA_W_ACK  0x18 // Master transmit ( slave address + Write request ) to slave + Ack received from slave
#define TW_MT_SLA_R_ACK  0x40 // Master transmit ( slave address + Read request ) to slave + Ack received from slave
#define TW_MT_DATA_ACK   0x28 // Master transmit data and ACK has been received from Slave.
#define TW_MR_DATA_ACK   0x50 // Master received data and send ACK to slave
#define TW_MR_DATA_NACK  0x58 // Master received data but doesn't send ACK to slave

#define DDR_I2C DDRC
#define PORT_I2C PORTC
#define DD_SCL 	PC0
#define DD_SDA PC1

void I2C_initMaster(void);
void I2C_initSlave(void);

// A master function to send start condition
void I2C_start(void);
// A master function to send stop condition
void I2C_stop(void);

// A master/slave function to write to bus
void I2C_write(unsigned char data);
// A master/slave function to read from bus
unsigned char I2C_read(unsigned char withAck);

// A slave function to listen if it's addressed
void I2C_listen(void);

unsigned char I2C_getStatus(void);

#endif /* I2C_H_ */
