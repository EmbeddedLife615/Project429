/**
  ******************************************************************************
  * @file    fml_led.c
  * @author  Wendell
  * @version V1.0
  * @date    2019-2-28 
  * @brief   LED Function
  *          
  * @modefy 
  *			version		 date		author		 remark
  *			  V1.0    2019-2-28 	Wendell  	released
  *
  * Copyright (C) 2019 XCMG Group.
  ******************************************************************************
**/

#include <bsp.h> 
#include "fml_led.h"
/*
*********************************************************************************************************
*	�� �� ��: FML_LED_Init
*	����˵��: ����LEDָʾ�Ƴ�ʼ״̬Ϩ��,  �ú�����FML_Init()���á�
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void FML_LED_Init(void)
{
	FML_LED_Off(GPIO_LED0);
	FML_LED_Off(GPIO_LED1);
}

/*
*********************************************************************************************************
*	�� �� ��: FML_LED_On
*	����˵��: ����ָ����LEDָʾ�ơ�
*	��    ��: LEDChannel: ָʾ����ţ���ΧΪ0-1����output_config[]��Ԫ�صĵ�һ��������Ӧ
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void FML_LED_On(BSP_GPIO_ChannelTypeDef LEDChannel)
{
	assert_param(IS_BSP_GPIO_LED(LEDChannel));
	BSP_GPIO_SetValue(LEDChannel,BSP_GPIO_LOW);
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_LedOff
*	����˵��: Ϩ��ָ����LEDָʾ�ơ�
*	��    ��: LEDChannel: ָʾ����ţ���ΧΪ0-1����output_config[]��Ԫ�صĵ�һ��������Ӧ
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void FML_LED_Off(BSP_GPIO_ChannelTypeDef LEDChannel)
{
	assert_param(IS_BSP_GPIO_LED(LEDChannel));
	BSP_GPIO_SetValue(LEDChannel,BSP_GPIO_HIGH);
}

/*
*********************************************************************************************************
*	�� �� ��: FML_LED_Toggle
*	����˵��: ��תָ����LEDָʾ�ơ�
*	��    ��: LEDChannel: ָʾ����ţ���ΧΪ0-1����output_config[]��Ԫ�صĵ�һ��������Ӧ
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void FML_LED_Toggle(BSP_GPIO_ChannelTypeDef LEDChannel)
{
	assert_param(IS_BSP_GPIO_LED(LEDChannel));
	BSP_GPIO_SetValue(LEDChannel,BSP_GPIO_TOGGLE);
}

/*
*********************************************************************************************************
*	�� �� ��: FML_LED_IsOn
*	����˵��: �ж�LEDָʾ���Ƿ��Ѿ�������
*	��    ��: LEDChannel: ָʾ����ţ���ΧΪ0-1
*	�� �� ֵ: 0��ʾ�Ѿ�������1��ʾδ������-1��ʾ����
*********************************************************************************************************
*/
int8_t FML_LED_IsOn(BSP_GPIO_ChannelTypeDef LEDChannel)
{
	assert_param(IS_BSP_GPIO_LED(LEDChannel));
	return BSP_GPIO_GetValue(LEDChannel);
}

/************************ (C) COPYRIGHT XCMG GROUP *****END OF FILE****/
