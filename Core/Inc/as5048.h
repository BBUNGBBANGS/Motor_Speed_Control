#include "main.h"

#define AS5048_SPI_MODULE           (&hspi1)
#define AS5048_SPI_TIMEOUT          (10)
#define AS5048_SPI_DATAMASK         (0x3FFF)
#define AS5048_SPI_BITMASK          (0x01)
#define AS5048_SPI_ERRSHIFT         (14)
#define AS5048_SPI_PARITYSHIFT      (15)
#define AS5048_SPI_ERROR            (1)

#define AS5048_FAC_LSB_TO_ANGLE     (2.19f)

extern void AS5048_Calc_Signal(void);