/**
  ******************************************************************************
  * @file    bsp.c
  * @author  Wendell
  * @version V1.0
  * @date    2019-2-28 
  * @brief   Board Support Package
  *          
  * @modefy 
  *			version		 date		author		 remark
  *			  V1.0    2019-2-28 	Wendell  	released
  *
  * Copyright (C) 2019 XCMG Group.
  ******************************************************************************
**/

#include "bsp.h"

/*
*********************************************************************************************************
*	函 数 名: bsp_Init
*	功能说明: 初始化硬件设备。只需要调用一次。该函数配置CPU寄存器和外设的寄存器并初始化一些全局变量。
*			
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void BSP_Init(void)
{
	/*
		由于ST固件库的启动文件已经执行了CPU系统时钟的初始化，所以不必再次重复配置系统时钟。
		启动文件配置了CPU主时钟频率、内部Flash访问速度和可选的外部SRAM FSMC初始化。

		系统时钟缺省配置为168MHz，如果需要更改，可以修改 system_stm32f4xx.c 文件
	*/
	/* STM32F4xx HAL library initialization:
	   - Configure the Flash prefetch, Flash preread and Buffer caches
	   - Systick timer is configured by default as source of time base, but user 
			 can eventually implement his proper time base source (a general purpose 
			 timer for example or other time source), keeping in mind that Time base 
			 duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
			 handled in milliseconds basis.
	   - Low Level Initialization
	 */
	HAL_Init();
	/* Configure the System clock to 180 MHz */
	SystemClock_Config();

	
//	SystemCoreClockUpdate();	/* 根据PLL配置更新系统时钟频率变量 SystemCoreClock */
	/* 优先级分组设置为4 */
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	BSP_GPIO_Init();	/* 配置IO */
//	bsp_InitUart(); 	/* 初始化串口 */
//	bsp_InitKey();		/* 初始化按键 */
//	bsp_InitTimer();	/* 初始化系统滴答定时器 (此函数会开 systick 中断, tim2-5中断) */
}

/*
*********************************************************************************************************
*	函 数 名: bsp_RunPer10ms
*	功能说明: 该函数每隔10ms被Systick中断调用1次。详见 bsp_timer.c的定时中断服务程序。一些处理时间要求不严格的
*			任务可以放在此函数。比如：按键扫描、蜂鸣器鸣叫控制等。
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void BSP_RunPer10ms(void)
{
//	bsp_KeyScan();
}

/*
*********************************************************************************************************
*	函 数 名: bsp_RunPer1ms
*	功能说明: 该函数每隔1ms被Systick中断调用1次。详见 bsp_timer.c的定时中断服务程序。一些需要周期性处理的事务
*			 可以放在此函数。比如：触摸坐标扫描。
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void BSP_RunPer1ms(void)
{
}

/*
*********************************************************************************************************
*	函 数 名: bsp_Idle
*	功能说明: 空闲时执行的函数。一般主程序在for和while循环程序体中需要插入 CPU_IDLE() 宏来调用本函数。
*			 本函数缺省为空操作。用户可以添加喂狗、设置CPU进入休眠模式的功能。
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
//extern void SaveScreenToBmp(uint16_t _index);
void BSP_Idle(void)
{
	/* --- 喂狗 */

	/* --- 让CPU进入休眠，由Systick定时中断唤醒或者其他中断唤醒 */

	/* 例如 emWin 图形库，可以插入图形库需要的轮询函数 */
	//GUI_Exec();

	/* 例如 uIP 协议，可以插入uip轮询函数 */
}

/************************ (C) COPYRIGHT XCMG GROUP *****END OF FILE****/


