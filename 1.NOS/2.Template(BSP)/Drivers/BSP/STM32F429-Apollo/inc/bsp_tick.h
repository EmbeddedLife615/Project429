/**
  ******************************************************************************
  * @file    bsp_led.h
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
/*-----------------------------------------------------------------------------
 * Name:    Board_LED.h
 * Purpose: LED interface header file
 * Rev.:    1.0.0
 *-----------------------------------------------------------------------------*/

#ifndef __BSP_TICK_H
#define __BSP_TICK_H

#include "stm32f4xx_hal.h"


/****
	* @fn     uint32_t BSP_TICK_Gret(void)
	* @brief  Provides a tick value in millisecond.
	*@retval  tick value 
	*/
extern uint32_t BSP_TICK_Get(void);

/****
	* @fn    uint8_t BSP_TICK_GetPeriod(void)
	* @brief Return tick Period.
	* @retval tick period in ms
	*/
extern uint32_t BSP_TICK_GetPeriod(void);

/****
	* @fn    uint8_t BSP_TICK_GetFreq(void)
	* @brief Return tick freqcuency.
	* @retval tick freqcuency in Hz
	*/
extern uint32_t BSP_TICK_GetFreq(void);

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
extern void BSP_TICK_Delay(uint32_t Delay);



#endif /* __BSP_TICK_H */

/************************ (C) COPYRIGHT XCMG GROUP *****END OF FILE****/


