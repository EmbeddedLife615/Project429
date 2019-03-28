/**
  ******************************************************************************
  * @file    fml_tick.c
  * @author  Wendell
  * @date    2019-2-28 
  * @brief   Tick function
  *          
  * Change Logs: 
  *				 Date		Author		 Notes
  *			  2019-2-28 	Wendell  	released
  *
  * Copyright (C) 2019 XCMG Group.
  ******************************************************************************
**/

#include <bsp.h> 
#include "fml_tick.h"


/****
	* @fn     uint32_t FML_TICK_Get(void)
	* @brief  Provides a tick value in millisecond.
	*@retval  tick value 
	*/
uint32_t FML_TICK_Get(void)
{
	return BSP_TICK_Get();
}

/****
	* @fn     uint8_t FML_TICK_TimeOut(uint32_t *start, uint32_t interval)
	* @brief  Determine whether the time is out 
	* @param  *start: Start time in millisecond. 
	*		  interval : Interval time in millisecond
	*@retval  
	*		@b   FALSE :  Time is not out
	*		@b   TRUE  :  Time is out
	*/
uint8_t FML_TICK_TimeOut(uint32_t *start, uint32_t interval)
{
    uint32_t current;

    current = BSP_TICK_Get();

    if (current - *start < interval) {
        return FALSE;
    }
    *start = current;
    return TRUE;
}


/****
	* @fn     uint32_t FML_TICK_TimeElapsed(uint32_t *before)
	* @brief  Calculate elapsed time in millisecond 
	* @param  *before: Start time in millisecond. 
	*@retval  elapsed: The value of elapsed time in millisecond
	*/
uint32_t FML_TICK_TimeElapsed(uint32_t *before)
{
    uint32_t current, elapsed;

    current = BSP_TICK_Get();

    elapsed = current - *before;
    *before = current;

    return elapsed;
}



///************************ (C) COPYRIGHT XCMG GROUP *****END OF FILE****/
