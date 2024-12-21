# STM32_W25Q
Creates an STM32 library for use with the W25Q16JVSNIQ SPI flash memory
chip. This is based off of Controller Tech's [W25Q Flash Series](https://controllerstech.com/w25q-flash-series-part-1-read-id/) and [Adafruit_SPIFlash](https://github.com/adafruit/Adafruit_SPIFlash/tree/master/src). 
Specifically, this is for use with my [BasicBoard-STM32G473CET6 board](https://github.com/kjpeng/BasicBoard-STM32G473CET6), which uses SPI2 pins PB15 (SPI2_MOSI), PB14 (SPI2_MISO), PB13 (SPI2_SCK), PB11 (SPI2_CS), and PB10 (DC).
