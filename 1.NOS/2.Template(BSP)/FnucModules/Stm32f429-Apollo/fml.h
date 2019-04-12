/**
  ******************************************************************************
  * @file    fml.h
  * @author  Wendell
  * @version V1.0
  * @date    2019-2-28 
  * @brief   Function Module Layer
  *          
  * Change Logs: 
  *				 Date		Author		 Notes
  *			  2019-2-28 	Wendell  	released
  *
  * Copyright (C) 2019 XCMG Group.
  ******************************************************************************
**/

#ifndef _FML_H_
#define _FML_H_


/* 这个宏仅用于调试阶段排错 */
#define BSP_Printf		printf
//#define BSP_Printf(...)

 #include "bsp.h" 
/* 通过取消注释或者添加注释的方式控制是否包含各函数模块 */
#include "fml_led.h"
#include "fml_tick.h"

/* 提供给其他C文件调用的函数 */
extern uint32_t FML_GetVersion(void);
extern void FML_PrintfLogo(void);
extern void FML_Init(void);
extern void FML_Idle(void);

#endif

/************************ (C) COPYRIGHT XCMG GROUP *****END OF FILE****/
