/**
  ******************************************************************************
  * @file    fml_tick.h
  * @author  Wendell
  * @date    2019-2-28 
  * @brief   LED function
  *          
  * Change Logs: 
  *				 Date		Author		 Notes
  *			  2019-2-28 	Wendell  	released
  *
  * Copyright (C) 2019 XCMG Group.
  ******************************************************************************
**/

#ifndef __FML_TICK_H
#define __FML_TICK_H

/****
	* @fn     uint32_t FML_TICK_Get(void)
	* @brief  Provides a tick value in millisecond.
	*@retval  tick value 
	*/
extern uint32_t FML_TICK_Get(void);
	
/****
	* @fn     uint8_t FML_TICK_TimeOut(uint32_t *start, uint32_t interval)
	* @brief  Determine whether the time is out 
	* @param  *start: Start time in millisecond. 
	*		  interval : Interval time in millisecond
	*@retval  
	*		@b   FALSE :  Time is not out
	*		@b   TRUE  :  Time is out
	*/
extern uint8_t FML_TICK_TimeOut(uint32_t *start, uint32_t interval);

/****
	* @fn     uint32_t FML_TICK_TimeElapsed(uint32_t *before)
	* @brief  Calculate elapsed time in millisecond 
	* @param  *before: Start time in millisecond. 
	*@retval  elapsed: The value of elapsed time in millisecond
	*/
extern uint32_t FML_TICK_TimeElapsed(uint32_t *before);

#endif

/************************ (C) COPYRIGHT XCMG GROUP *****END OF FILE****/
