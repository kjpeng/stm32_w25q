
#ifndef _W25QXX_H_
#define _W25QXX_H_

#include <stdint.h>
#include "stm32g4xx_hal.h"

#define W25Q_RSTEN    0x66
#define W25Q_RST      0x99
#define W25Q_JEDECID  0x9F
#define W25Q_READDAT  0x03
#define W25Q_ENWRITE  0x06
#define W25Q_DEWRITE  0x04
#define W25Q_ERASESEC 0x20

extern SPI_HandleTypeDef hspi2;

extern GPIO_TypeDef *cs_port;
extern uint16_t cs_pin;

void W25Q_SelectChip(void);
void W25Q_DeselectChip(void);

void W25Q_SPIWrite(uint8_t *data, uint8_t len);
void W25Q_SPIRead(uint8_t *data, uint8_t len);

void W25Q_Reset(void);
uint32_t W25Q_ReadID(void);

void W25Q_EnableWrite(void);
void W25Q_DisableWrite(void);

void W25Q_Read(uint32_t startPage, uint8_t offset, uint32_t size, uint8_t *rData);
void W25Q_EraseSector(uint16_t numSector);
void W25Q_WritePage(uint32_t page, uint16_t offset, uint32_t size, uint8_t *data);

uint32_t W25Q_BytesToWrite(uint32_t size, uint16_t offset);








#endif
