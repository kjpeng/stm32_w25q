
#ifndef _W25QXX_H_
#define _W25QXX_H_

#include <stdint.h>
#include "stm32g4xx_hal.h"

#define W25Q_RSTEN    0x66
#define W25Q_RST      0x99
#define W25Q_JEDECID  0x9F

extern SPI_HandleTypeDef hspi2;

extern GPIO_TypeDef *cs_port;
extern uint16_t cs_pin;

void W25Q_SelectChip(void);
void W25Q_DeselectChip(void);

void W25Q_SPIWrite(uint8_t *data, uint8_t len);
void W25Q_SPIRead(uint8_t *data, uint8_t len);

void W25Q_Reset(void);
uint32_t W25Q_ReadID(void);









#endif
