/**
  ******************************************************************************
  * @file    app_led.c
  * @author  Wendell
  * @version V1.0
  * @date    2019-2-28 
  * @brief   LED_app
  *          
  * @modefy 
  *			version		 date		author		 remark
  *			  V1.0    2019-2-28 	Wendell  	released
  *
  * Copyright (C) 2019 XCMG Group.
  ******************************************************************************
**/

#include <fml.h> 

/* Private functions ---------------------------------------------------------*/
void Delay(__IO uint32_t nCount)
{
  while(nCount--){}
}

/*
*********************************************************************************************************
*	函 数 名: APP_LED_Test
*	功能说明: LED闪烁测试程序,该函数被 main() 调用。
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
void APP_LED_Test(void)
{
	FML_LED_On(GPIO_LED0);
	FML_LED_Off(GPIO_LED1);
	Delay(0xFFFFFF);
	FML_LED_Off(GPIO_LED0);
	FML_LED_On(GPIO_LED1);
	Delay(0xFFFFFF);
}



/************************ (C) COPYRIGHT XCMG GROUP *****END OF FILE****/
