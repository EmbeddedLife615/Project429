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
*	函 数 名: FML_LED_Init
*	功能说明: 配置LED指示灯初始状态熄灭,  该函数被FML_Init()调用。
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
void FML_LED_Init(void)
{
	FML_LED_Off(GPIO_LED0);
	FML_LED_Off(GPIO_LED1);
}

/*
*********************************************************************************************************
*	函 数 名: FML_LED_On
*	功能说明: 点亮指定的LED指示灯。
*	形    参: LEDChannel: 指示灯序号，范围为0-1，与output_config[]中元素的第一个参数对应
*	返 回 值: 无
*********************************************************************************************************
*/
void FML_LED_On(BSP_GPIO_ChannelTypeDef LEDChannel)
{
	assert_param(IS_BSP_GPIO_LED(LEDChannel));
	BSP_GPIO_SetValue(LEDChannel,BSP_GPIO_LOW);
}

/*
*********************************************************************************************************
*	函 数 名: bsp_LedOff
*	功能说明: 熄灭指定的LED指示灯。
*	形    参: LEDChannel: 指示灯序号，范围为0-1，与output_config[]中元素的第一个参数对应
*	返 回 值: 无
*********************************************************************************************************
*/
void FML_LED_Off(BSP_GPIO_ChannelTypeDef LEDChannel)
{
	assert_param(IS_BSP_GPIO_LED(LEDChannel));
	BSP_GPIO_SetValue(LEDChannel,BSP_GPIO_HIGH);
}

/*
*********************************************************************************************************
*	函 数 名: FML_LED_Toggle
*	功能说明: 翻转指定的LED指示灯。
*	形    参: LEDChannel: 指示灯序号，范围为0-1，与output_config[]中元素的第一个参数对应
*	返 回 值: 无
*********************************************************************************************************
*/
void FML_LED_Toggle(BSP_GPIO_ChannelTypeDef LEDChannel)
{
	assert_param(IS_BSP_GPIO_LED(LEDChannel));
	BSP_GPIO_SetValue(LEDChannel,BSP_GPIO_TOGGLE);
}

/*
*********************************************************************************************************
*	函 数 名: FML_LED_IsOn
*	功能说明: 判断LED指示灯是否已经点亮。
*	形    参: LEDChannel: 指示灯序号，范围为0-1
*	返 回 值: 0表示已经点亮，1表示未点亮，-1表示出错
*********************************************************************************************************
*/
int8_t FML_LED_IsOn(BSP_GPIO_ChannelTypeDef LEDChannel)
{
	assert_param(IS_BSP_GPIO_LED(LEDChannel));
	return BSP_GPIO_GetValue(LEDChannel);
}

/************************ (C) COPYRIGHT XCMG GROUP *****END OF FILE****/
