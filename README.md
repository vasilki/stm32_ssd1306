# stm_ssd1306
Connecting OLED display ssd1306 to the Nucleo F401RE

Pinout:
OLED:STM32
GND:GND
VCC:5V
D0:SCK/D13(CN5)
D1:MOSI/D11(CN5)
RES:D9(CN5)
DC:D7(CN9)
CS:CS/D10(CN5)

Environment:
Library was taken from https://github.com/afiskon/stm32-ssd1306
STM32 NUCLEO-F401RE
OLED display ssd1306
Linux Mint 18.2 Sonya
STM32Cube_1.0 version 4.24.0.Repository is STM32Cube_FW_F4_V1.19.0.
System Workbench for STM32 (Version: 1.13.2.201703061529) based on Eclipse IDE version Mars.2.Release 4.5.2


Some moments:
Prescaler 64 ~ 34FPS
Prescale 128 ~ 18FPS
SPI should be 1EDGE:
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;