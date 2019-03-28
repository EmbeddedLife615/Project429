/*
*********************************************************************************************************
*
*	模块名称 : LED指示灯驱动模块
*	文件名称 : bsp_led.h
*	版    本 : V1.0
*	说    明 : 头文件
*
*	Copyright (C), 2013-2014, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/

#ifndef __FML_LED_H
#define __FML_LED_H

/* 供外部调用的函数声明 */
void FML_LED_Init(void);
void FML_LED_On(BSP_GPIO_ChannelTypeDef LED);
void FML_LED_Off(BSP_GPIO_ChannelTypeDef LED);
void FML_LED_Toggle(BSP_GPIO_ChannelTypeDef LED);
int8_t FML_LED_IsOn(BSP_GPIO_ChannelTypeDef LED);

#endif

/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
