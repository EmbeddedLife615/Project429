/*
*********************************************************************************************************
*
*	ģ������ : LEDָʾ������ģ��
*	�ļ����� : bsp_led.h
*	��    �� : V1.0
*	˵    �� : ͷ�ļ�
*
*	Copyright (C), 2013-2014, ���������� www.armfly.com
*
*********************************************************************************************************
*/

#ifndef __FML_LED_H
#define __FML_LED_H

/* ���ⲿ���õĺ������� */
void FML_LED_Init(void);
void FML_LED_On(BSP_GPIO_ChannelTypeDef LED);
void FML_LED_Off(BSP_GPIO_ChannelTypeDef LED);
void FML_LED_Toggle(BSP_GPIO_ChannelTypeDef LED);
int8_t FML_LED_IsOn(BSP_GPIO_ChannelTypeDef LED);

#endif

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/
