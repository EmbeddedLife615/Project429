/**
  ******************************************************************************
  * @file    app.c
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

#include "app.h"

/* 定义例程名和例程发布日期 */
#define PROJECT_NAME	"Template for stm32f429-apollos"
#define PROJECT_DATE	"2019-03-23"
#define PROJECT_VER		"1.0.0"

void APP_PrintfLogo(void)
{
	/* 检测CPU ID */
	{
		/* 参考手册：
			32.6.1 MCU device ID code
			33.1 Unique device ID register (96 bits)
		*/
		uint32_t CPU_Sn0, CPU_Sn1, CPU_Sn2;

		CPU_Sn0 = *(__IO uint32_t*)(0x1FFF7A10);
		CPU_Sn1 = *(__IO uint32_t*)(0x1FFF7A10 + 4);
		CPU_Sn2 = *(__IO uint32_t*)(0x1FFF7A10 + 8);

		printf("\r\nCPU : STM32F429IGT6, LQFP176, UID = %08X %08X %08X\n\r"
			, CPU_Sn2, CPU_Sn1, CPU_Sn0);
	}

	printf("\n\r");
	printf("**************************************************************\r\n");
	printf("* 程序名称   : %s\r\n", PROJECT_NAME);	/* 打印程序名称 */
	printf("* 程序版本   : %s\r\n", PROJECT_VER);	/* 打印程序版本 */
	printf("* 发布日期   : %s\r\n", PROJECT_DATE);	/* 打印程序日期 */

	/* 打印各层版本 */
	FML_PrintfLogo();
	
	printf("* \r\n");	/* 打印一行空格 */
	printf("* Copyright (c) 2018-2019 XCMG Group\r\n");
	printf("**************************************************************\r\n");
}

/*
*********************************************************************************************************
*	函 数 名: APP_Init
*	功能说明: 应用层级的初始化，逐层调用下级初始化函数，只需要调用一次。应用层APP-->功能模块层FML-->板级支持包BSP-->硬件抽象层HAL
*			  该函数被 main() 调用。
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void APP_Init(void)
{
	FML_Init();
	printf("Application Layer init completed!\r\n");
}


/*
*********************************************************************************************************
*	函 数 名: APP_Idle
*	功能说明: 空闲时执行的函数。一般主程序在for和while循环程序体中需要插入 CPU_IDLE() 宏来调用本函数。
*			 本函数缺省为空操作。用户可以添加喂狗、设置CPU进入休眠模式的功能。
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void APP_Idle(void)
{
	FML_Idle();
	/* --- 喂狗 */

	/* --- 让CPU进入休眠，由Systick定时中断唤醒或者其他中断唤醒 */

	/* 例如 emWin 图形库，可以插入图形库需要的轮询函数 */
	//GUI_Exec();

	/* 例如 uIP 协议，可以插入uip轮询函数 */
}

/************************ (C) COPYRIGHT XCMG GROUP *****END OF FILE****/



