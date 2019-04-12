/**
  ******************************************************************************
  * @file    fml.c
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

#include "fml.h"

 /**
  * @brief Function Module Layer version number V1.0.0
  */
#define __FML_VERSION_MAIN   (0x01) /*!< [31:24] main version */
#define __FML_VERSION_SUB1   (0x00) /*!< [23:16] sub1 version */
#define __FML_VERSION_SUB2   (0x00) /*!< [15:8]  sub2 version */
#define __FML_VERSION_RC     (0x00) /*!< [7:0]  release candidate */ 
#define __FML_VERSION        ((__FML_VERSION_MAIN << 24)\
                              |(__FML_VERSION_SUB1 << 16)\
							  |(__FML_VERSION_SUB2 << 8 )\
							  |(__FML_VERSION_RC)) 
							  
/**
  * @brief  This method returns the Function Module Layer vierssion
  * @retval version: 0xXYZR (8bits for each decimal, R for RC)
  */
uint32_t FML_GetVersion(void)
{
  return __FML_VERSION;
}							  
							  
void FML_PrintfLogo(void)
{
	BSP_PrintfLogo();
	printf("* FML版本 : V%d.%d.%d (Function Module Layer version)\r\n", __FML_VERSION_MAIN,
			__FML_VERSION_SUB1,__FML_VERSION_SUB2);
}											 
/*
*********************************************************************************************************
*	函 数 名: FML_Init
*	功能说明: 功能模块层的初始化，逐层调用下级初始化函数，只需要调用一次。功能模块层FML-->板级支持包BSP-->硬件抽象层HAL
*			  该函数被 APP_Init() 调用。
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void FML_Init(void)
{
	BSP_Init();
	FML_LED_Init(); 	/* 初始LED指示灯端口 */
	printf("Function Module Layer init completed!\r\n");
}



///*
//*********************************************************************************************************
//*	函 数 名: bsp_RunPer10ms
//*	功能说明: 该函数每隔10ms被Systick中断调用1次。详见 bsp_timer.c的定时中断服务程序。一些处理时间要求不严格的
//*			任务可以放在此函数。比如：按键扫描、蜂鸣器鸣叫控制等。
//*	形    参：无
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//void bsp_RunPer10ms(void)
//{
////	bsp_KeyScan();
//}

///*
//*********************************************************************************************************
//*	函 数 名: bsp_RunPer1ms
//*	功能说明: 该函数每隔1ms被Systick中断调用1次。详见 bsp_timer.c的定时中断服务程序。一些需要周期性处理的事务
//*			 可以放在此函数。比如：触摸坐标扫描。
//*	形    参: 无
//*	返 回 值: 无
//*********************************************************************************************************
//*/
//void bsp_RunPer1ms(void)
//{
//}

/*
*********************************************************************************************************
*	函 数 名: bsp_Idle
*	功能说明: 空闲时执行的函数。一般主程序在for和while循环程序体中需要插入 CPU_IDLE() 宏来调用本函数。
*			 本函数缺省为空操作。用户可以添加喂狗、设置CPU进入休眠模式的功能。
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/

void FML_Idle(void)
{
	BSP_Idle();
	/* --- 喂狗 */

	/* --- 让CPU进入休眠，由Systick定时中断唤醒或者其他中断唤醒 */

	/* 例如 emWin 图形库，可以插入图形库需要的轮询函数 */
	//GUI_Exec();

	/* 例如 uIP 协议，可以插入uip轮询函数 */
}

///************************ (C) COPYRIGHT XCMG GROUP *****END OF FILE****/



