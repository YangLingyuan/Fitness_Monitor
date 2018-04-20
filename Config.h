#ifndef _CONFIG_H_
#define _CONFIG_H_

#define GPIO_USART2_TX GPIO_Pin_2  //GPIO_A
#define GPIO_USART2_RX GPIO_Pin_3  //GPIO_A
#define GPIO_I2C_SCL GPIO_Pin_10  //GPIO_B
#define GPIO_I2C_SDA GPIO_Pin_11  //GPIO_B


void GPIO_Config(void);
void USART2_Config(void);
void systick_init(void);
void Delay(u32 ms_10);
void I2C_Config(void);

#endif
