/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  Wendell
  * @date    2019-3-21 
  * @brief   LED interface for STM32F429-Apollo Kit
  *          
  * Change Logs: 
  *				 Date		Author		 Notes
  *			  2019-2-28 	Wendell  	released
  *
  * Copyright (C) 2019 XCMG Group.
  ******************************************************************************
**/

#include "bsp_tick.h"


/****
	* @fn     uint32_t BSP_TICK_Gret(void)
	* @brief  Provides a tick value in millisecond.
	*@retval  tick value 
	*/
uint32_t BSP_TICK_Get(void)
{
	return HAL_GetTick();
}


/****
	* @fn    uint8_t BSP_TICK_GetPeriod(void)
	* @brief Return tick Period.
	* @retval tick period in ms
	*/
uint32_t BSP_TICK_GetPeriod(void)
{
	uint32_t TickPeriod;
	TickPeriod = (uint32_t)HAL_GetTickFreq();
	assert_param(IS_TICKFREQ(TickPeriod));
	
	return TickPeriod;
}


/****
	* @fn    uint8_t BSP_TICK_GetFreq(void)
	* @brief Return tick freqcuency.
	* @retval tick freqcuency in Hz
	*/
uint32_t BSP_TICK_GetFreq(void)
{		
	return 1000U/BSP_TICK_GetPeriod();;
}

/****
	* @fn    void BSP_TICK_Delay(uint32_t Delay)
	* @brief This function provides minimum delay (in milliseconds) based 
	*        on variable incremented.
	* @note In the default implementation , SysTick timer is the source of time base.
	*       It is used to generate interrupts at regular time intervals where uwTick
	*       is incremented.
	* @param Delay specifies the delay time length, in milliseconds.
	* @retval None
	*/
void BSP_TICK_Delay(uint32_t Delay)
{
	HAL_Delay(Delay);
}

/************************ (C) COPYRIGHT XCMG GROUP *****END OF FILE****/


