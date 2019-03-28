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
*	�� �� ��: APP_LED_Test
*	����˵��: LED��˸���Գ���,�ú����� main() ���á�
*	��    ��:  ��
*	�� �� ֵ: ��
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
