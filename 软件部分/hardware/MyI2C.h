#ifndef __MYI2C_H
#define __MYI2C_H

void MyI2C_Init(void);
void MyI2C_start(void);
void MyI2C_stop(void);
void MyI2C_sentbyte(uint8_t byte);
uint8_t MyI2C_receivebyte(void);
void MyI2C_sendACK(uint8_t ackbit);
uint8_t MyI2C_receiveACK(void);

#endif
