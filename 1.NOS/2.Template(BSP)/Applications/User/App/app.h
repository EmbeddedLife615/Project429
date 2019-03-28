/**
  ******************************************************************************
  * @file    app.h
  * @author  Wendell
  * @version V1.0
  * @date    2019-2-28 
  * @brief   Application
  *          
  * Change Logs: 
  *				 Date		Author		 Notes
  *			  2019-2-28 	Wendell  	released
  *
  * Copyright (C) 2019 XCMG Group.
  ******************************************************************************
**/

#ifndef _APP_H_
#define _APP_H_

/* 定义 Function Module Layer 版本号 */
#define __APP_VERSION		"1.0.0"


#include "fml.h" 
/* 通过取消注释或者添加注释的方式控制是否包含各函数模块 */
#include "app_led.h"

/* 提供给其他C文件调用的函数 */
void APP_Init(void);


#endif

/************************ (C) COPYRIGHT XCMG GROUP *****END OF FILE****/
