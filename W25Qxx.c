
#include "W25Qxx.h"
#include <cmath>

void W25Q_SelectChip(void) {
  HAL_GPIO_WritePin(cs_port, cs_pin, GPIO_PIN_RESET);
}

void W25Q_DeselectChip(void) {
  HAL_GPIO_WritePin(cs_port, cs_pin, GPIO_PIN_SET);
}

void W25Q_SPIWrite(uint8_t *data, uint8_t len) {
  HAL_SPI_Transmit(&hspi2, data, len, HAL_MAX_DELAY);
}

void W25Q_SPIRead(uint8_t *data, uint8_t len) {
  HAL_SPI_Receive(&hspi2, data, len, HAL_MAX_DELAY);
}

void W25Q_Reset(void) {
  uint8_t tData[2];
  tData[0] = W25Q_RSTEN;      // enable Reset
  tData[1] = W25Q_RST;

  W25Q_SelectChip();
  W25Q_SPIWrite(tData,2);
  W25Q_DeselectChip();
}

uint32_t W25Q_ReadID(void) {
  uint8_t tData = W25Q_JEDECID;
  uint8_t rData[3];

  W25Q_SelectChip();
  W25Q_SPIWrite(&tData, 1);
  W25Q_SPIRead(rData, 3);
  W25Q_DeselectChip();

  return rData[0] << 16 | rData[1] << 8 | rData[2];
}

void W25Q_Read(uint32_t startPage, uint8_t offset, uint32_t size, uint8_t *rData) {
  uint8_t tData[5];
  uint32_t memAddr = (startPage * 256) + offset;

  // 16MB chip, so only needs 3-byte addressing
  tData[0] = W25Q_READDAT;
  tData[1] = (memAddr >> 16) & 0xFF;
  tData[2] = (memAddr >> 8) & 0xFF;
  tData[3] = (memAddr) & 0xFF;

  W25Q_SelectChip();
  W25Q_SPIWrite(tData, 4);
  W25Q_SPIRead(rData, size);
  W25Q_DeselectChip();
}

void W25Q_EnableWrite(void) {
  uint8_t tData = W25Q_ENWRITE;

  W25Q_SelectChip();
  W25Q_SPIWrite(&tData, 1);
  W25Q_DeselectChip();
}

void W25Q_DisableWrite(void) {
  uint8_t tData = W25Q_DEWRITE;

  W25Q_SelectChip();
  W25Q_SPIWrite(&tData, 1);
  W25Q_DeselectChip();
}

void W25Q_EraseSector(uint16_t numSector) {
  uint8_t tData[6];
  uint32_t memAddr = numSector * 16 * 256;

  W25Q_EnableWrite();

  tData[0] = W25Q_ERASESEC;
  tData[1] = (memAddr >> 16) & 0xFF;
  tData[2] = (memAddr >> 8) & 0xFF;
  tData[3] = (memAddr) & 0xFF;

  W25Q_SelectChip();
  W25Q_SPIWrite(tData, 4);
  W25Q_DeselectChip();

  W25Q_DisableWrite();
}

void W25Q_WritePage(uint32_t page, uint16_t offset, uint32_t size, uint8_t *data) {
  uint8_t tData[266];
  uint32_t startPage = page;
  uint32_t endPage = startPage + ((size + offset - 1) / 256);
  uint32_t numPages = endPage - startPage + 1;

  uint16_t startSector = startPage / 16;
  uint16_t endSector = endPage / 16;
  uint16_t numSectors = endSector - startSector + 1;
  for (uint16_t i = 0; i < numSectors; i++) {
    W25Q_EraseSector(startSector++);
  }

  uint32_t dataPosition = 0;;
  for (uint32_t i = 0; i < numPages; i++) {
    uint32_t memAddr = (startPage * 256) + offset;
    uint16_t bytesRemaining = W25Q_BytesToWrite(size, offset);
  }
}

uint32_t W25Q_BytesToWrite(uint32_t size, uint16_t offset) {
  if ((size + offset) < 256)
    return size;
  return 256 - offset;
}

