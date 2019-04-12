/**
  ******************************************************************************
  * @file    bsp_uart.c
  * @author  Wendell
  * @date    2019-3-21 
  * @brief   uart driver interface for STM32F429-Apollo Kit
  *          
  * Change Logs: 
  *				 Date		Author		 Notes
  *			  2019-2-28 	Wendell  	released
  *
  * Copyright (C) 2019 XCMG Group.
  ******************************************************************************
**/

#include "bsp_uart.h"
	
UART_HandleTypeDef UART_Handler; //UART句柄

int fputc(int ch, FILE *f)
{
	/* 写一个字节到USARTx */  
	HAL_UART_Transmit(&UART_Handler,(uint8_t *)&ch,1,2);
	return ch;
}

/****
	* @fn     void BSP_LED_Init (void)
	* @brief  Configure all the LED GPIOs
	*/
void BSP_UART_Init (void) 
{
	/* uart1 TX = PA9   RX = PA10 */
	
	/* UART2 TX = PA2   RX = PA3 */

	UART_Handler.Instance=USART2;					    //USART2
	UART_Handler.Init.BaudRate=115200;				    //波特率
	UART_Handler.Init.WordLength=UART_WORDLENGTH_8B;   //字长为8位数据格式
	UART_Handler.Init.StopBits=UART_STOPBITS_1;	    //一个停止位
	UART_Handler.Init.Parity=UART_PARITY_NONE;		    //无奇偶校验位
	UART_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //无硬件流控
	UART_Handler.Init.Mode=UART_MODE_TX_RX;		    //收发模式
	HAL_UART_Init(&UART_Handler);					    //HAL_UART_Init()会使能UART2
	
//	HAL_UART_Receive_IT(&UART2_Handler, (u8 *)aRxBuffer, RXBUFFERSIZE);//该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量

	/* CPU的小缺陷：串口配置好，如果直接Send，则第1个字节发送不出去
		如下语句解决第1个字节无法正确发送出去的问题 */
//	USART_ClearFlag(USART2, USART_FLAG_TC);     /* 清发送完成标志，Transmission Complete flag */   
//#endif
}


void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    //GPIO端口设置
	GPIO_InitTypeDef GPIO_Initure;
	
	if(huart->Instance==USART1)//如果是串口1，进行串口1 MSP初始化
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();			//使能GPIOA时钟
		__HAL_RCC_USART1_CLK_ENABLE();			//使能USART1时钟
	
		GPIO_Initure.Pin=GPIO_PIN_9;			//PA9
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//复用推挽输出
		GPIO_Initure.Pull=GPIO_PULLUP;			//上拉
		GPIO_Initure.Speed=GPIO_SPEED_FAST;		//高速
		GPIO_Initure.Alternate=GPIO_AF7_USART1;	//复用为USART1
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA9

		GPIO_Initure.Pin=GPIO_PIN_10;			//PA10
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA10
		
#if EN_USART1_RX
		HAL_NVIC_EnableIRQ(USART1_IRQn);		//使能USART1中断通道
		HAL_NVIC_SetPriority(USART1_IRQn,3,3);	//抢占优先级3，子优先级3
#endif	
	}
	else if(huart->Instance==USART2)//如果是串口2，进行串口2 MSP初始化
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();			//使能GPIOA时钟
		__HAL_RCC_USART2_CLK_ENABLE();			//使能USART2时钟
	
		GPIO_Initure.Pin=GPIO_PIN_2;			//PA2
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//复用推挽输出
		GPIO_Initure.Pull=GPIO_PULLUP;			//上拉
		GPIO_Initure.Speed=GPIO_SPEED_FAST;		//高速
		GPIO_Initure.Alternate=GPIO_AF7_USART2;	//复用为USART2
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA2

		GPIO_Initure.Pin=GPIO_PIN_3;			//PA3
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA3
		
#if EN_USART2_RX
		HAL_NVIC_EnableIRQ(USART2_IRQn);		//使能USART2中断通道
		HAL_NVIC_SetPriority(USART2_IRQn,3,3);	//抢占优先级3，子优先级3
#endif	
	}

}

/************************ (C) COPYRIGHT XCMG GROUP *****END OF FILE****/
