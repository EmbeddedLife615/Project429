/**
  ******************************************************************************
  * @file    app_led.c
  * @author  Wendell
  * @version V1.0
  * @date    2019-2-28 
  * @brief   LED_app
  *          
  * Change Logs: 
  *				 Date		Author		 Notes
  *			  2019-2-28 	Wendell  	released
  *
  * Copyright (C) 2019 XCMG Group.
  ******************************************************************************
**/

#include "fml.h" 
#include "app_led.h"

typedef enum
{	
	LED_INIT =1,
	LED_BLINK,
}LED_StateDef;

uint32_t LED_TickStart;
uint8_t LED_State = LED_INIT;
/* Private functions ---------------------------------------------------------*/
void APP_LED_Init(void)
{
	LED_TickStart = FML_TICK_Get();
}
/*
*********************************************************************************************************
*	函 数 名: APP_LED_Blink
*	功能说明: LED闪烁测试程序,该函数被 main() 调用。
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
void APP_LED_Blink(uint32_t period)
{	
	if(FML_TICK_TimeOut(&LED_TickStart,period))
	{
		BSP_LED_Toggle(LED0);
		BSP_LED_Toggle(LED1);
	}
}

void APP_LED_Poll(void)
{
	switch(LED_State)
	{
		case LED_INIT:
			APP_LED_Init();
			LED_State = LED_BLINK;
			break;
		case LED_BLINK:
			APP_LED_Blink(500);
			break;
	}
}

/************************ (C) COPYRIGHT XCMG GROUP *****END OF FILE****/
