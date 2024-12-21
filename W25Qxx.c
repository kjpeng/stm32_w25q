
#include "W25Qxx.h"

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
