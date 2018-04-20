#include "stm32f10x.h"
#include "Config.h"
#include "MPU6050.h"
//#include "stm32f10x_conf.h"
long int delay_counter=0;

unsigned char USART2_TX_Buffer[]="#10000";
unsigned char USART2_RX_Buffer[]="#10000";
unsigned char RX_Count=0;
unsigned char TX_Count=0;
unsigned char Size_of_Rx_Buffer=6;
unsigned char Size_of_Tx_Buffer=6;
short int ACC[6];
int main()
{
	GPIO_Config();
	USART2_Config();
	systick_init();
	MPU6050_Initialize();
	MPU6050_I2C_Init();
	while(1)
	{
		
		Delay(100);
		MPU6050_GetRawAccelGyro( ACC);
		USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
		USART_SendData(USART2,USART2_TX_Buffer[0]);
	}
	return 1;
}


