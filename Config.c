#include "stm32f10x.h"
#include "Config.h"
#include "stm32f10x_i2c.h"
#include "MPU6050.h"
extern long int delay_counter;

void GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	
  GPIO_InitStructure.GPIO_Pin=GPIO_USART2_RX;
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA,&GPIO_InitStructure);
    
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin=GPIO_USART2_TX;
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;//led
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
  GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_I2C_SCL | GPIO_I2C_SDA;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void USART2_Config()
{
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
	
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE); 
    

    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	
    USART_InitStructure.USART_BaudRate=9600;
    USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;
    USART_InitStructure.USART_Parity=USART_Parity_No;
    USART_InitStructure.USART_StopBits=USART_StopBits_1;
    USART_InitStructure.USART_WordLength=USART_WordLength_8b;
    
    USART_Init(USART2,&USART_InitStructure);
	
		USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
	
    USART_Cmd(USART2,ENABLE);
    
}


void I2C_Config()
{
		I2C_InitTypeDef I2C_InitStructure;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
		
		/* I2C configuration */
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_OwnAddress1 = MPU6050_DEFAULT_ADDRESS; // MPU6050 7-bit adress = 0x68, 8-bit adress = 0xD0;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_ClockSpeed = MPU6050_I2C_Speed;

    /* Apply I2C configuration after enabling it */
    I2C_Init(I2C2, &I2C_InitStructure);
    /* I2C Peripheral Enable */
    I2C_Cmd(I2C2, ENABLE);

}	




void systick_init()
{

    SysTick_Config(SystemCoreClock/100);//Interrupt period of 10ms

    SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
}

void Delay(u32 ms_10)
{
	delay_counter=ms_10;
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;
	while(delay_counter);
	
}

