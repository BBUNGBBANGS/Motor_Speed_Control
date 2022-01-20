#include "as5048.h"

uint16 AS5048_SPI_Rx_buffer[2];
uint16 AS5048_SPI_Tx_buffer[2] = {0xFFFF,0x0000};
uint16 AS5048_SPI_Raw;
uint32 AS5048_Angle;
uint8 AS5048_parity;
uint8 AS5048_err;

void AS5048_Calc_Signal(void)
{
    sint32 angle_temp;
    HAL_SPI_TransmitReceive(AS5048_SPI_MODULE, AS5048_SPI_Tx_buffer, AS5048_SPI_Rx_buffer, 2, AS5048_SPI_TIMEOUT);
    AS5048_SPI_Raw = AS5048_SPI_Rx_buffer[1]&AS5048_SPI_DATAMASK;
    AS5048_err = (AS5048_SPI_Rx_buffer[1]>>AS5048_SPI_ERRSHIFT)&AS5048_SPI_BITMASK;
    AS5048_parity = (AS5048_SPI_Rx_buffer[1]>>AS5048_SPI_PARITYSHIFT)&AS5048_SPI_BITMASK;
    /*************************************************************************/
    /* 모터 각도 범위 : 0[degree] ~ 360[degree]                              */
    /* Angle 변수 값 범위 : 0  ~ 36000                                       */
    /*************************************************************************/
    if(AS5048_SPI_ERROR != AS5048_err)
    {
        /* Angle raw data를 Degree 값으로 변환(범위 : 0 ~ 180 degree) */
        angle_temp = (sint32)((float)(AS5048_SPI_Raw) * (AS5048_FAC_LSB_TO_ANGLE) - 18000.0f);
        /* Angle data 범위 변경(범위 : 0 ~ 360 degree) */
        angle_temp = angle_temp * 2;
        /* overflow 방지 */
        if(angle_temp>=36000)
        {
            angle_temp = 36000 - angle_temp;
        }
        if(angle_temp<0)
        {
            angle_temp = 36000 + angle_temp;
        }
        /* Angle값이 Clock wise 회전방향일 경우, 증가하도록 변환 */
        AS5048_Angle = (36000 - angle_temp);
    }
    else
    {
        /* SPI error 발생 시, 이전 각도 값 유지 */
    }
    return;
}