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


/* ���������ڵ��Խ׶��Ŵ� */
#define BSP_Printf		printf
//#define BSP_Printf(...)

 #include "bsp.h" 
/* ͨ��ȡ��ע�ͻ������ע�͵ķ�ʽ�����Ƿ����������ģ�� */
#include "fml_led.h"
#include "fml_tick.h"

/* �ṩ������C�ļ����õĺ��� */
extern uint32_t FML_GetVersion(void);
extern void FML_PrintfLogo(void);
extern void FML_Init(void);
extern void FML_Idle(void);

#endif

/************************ (C) COPYRIGHT XCMG GROUP *****END OF FILE****/
