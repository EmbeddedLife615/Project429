/**
  ******************************************************************************
  * @file    bsp.c
  * @author  Wendell
  * @date    2019-2-28 
  * @brief   Board Support Package
  *          
  * Change Logs: 
  *				 Date		Author		 Notes
  *			  2019-2-28 	Wendell  	released
  *
  * Copyright (C) 2019 XCMG Group.
  ******************************************************************************
**/

#include "bsp.h"

 /**
  * @brief STM32F429 APOLLO BSP Driver version number V1.0.0
  */
#define __STM32F429_BSP_VERSION_MAIN   (0x01) /*!< [31:24] main version */
#define __STM32F429_BSP_VERSION_SUB1   (0x00) /*!< [23:16] sub1 version */
#define __STM32F429_BSP_VERSION_SUB2   (0x00) /*!< [15:8]  sub2 version */
#define __STM32F429_BSP_VERSION_RC     (0x00) /*!< [7:0]  release candidate */ 
#define __STM32F429_BSP_VERSION        ((__STM32F429_BSP_VERSION_MAIN << 24)\
                                             |(__STM32F429_BSP_VERSION_SUB1 << 16)\
                                             |(__STM32F429_BSP_VERSION_SUB2 << 8 )\
                                             |(__STM32F429_BSP_VERSION_RC)) 
											 
/**
  * @brief  This method returns the STM32F429 APOLLO BSP Driver revision
  * @retval version: 0xXYZR (8bits for each decimal, R for RC)
  */
uint32_t BSP_GetVersion(void)
{
  return __STM32F429_BSP_VERSION;
}

void BSP_PrintfLogo(void)
{
	uint32_t HAL_Version;
	HAL_Version = HAL_GetHalVersion();
	printf("* HAL�汾 : V%d.%d.%d (STM32F4xx HAL driver version )\r\n", (HAL_Version>>24)&0xff,
			(HAL_Version>>16)&0xff,(HAL_Version>>8)&0xff);
	printf("* BSP�汾 : V%d.%d.%d (STM32F429-Apollo BSP version )\r\n", __STM32F429_BSP_VERSION_MAIN,
			__STM32F429_BSP_VERSION_SUB1,__STM32F429_BSP_VERSION_SUB2);	
	
}


/*
*********************************************************************************************************
*	�� �� ��: bsp_Init
*	����˵��: ��ʼ��Ӳ���豸��ֻ��Ҫ����һ�Ρ��ú�������CPU�Ĵ���������ļĴ�������ʼ��һЩȫ�ֱ�����
*			
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void BSP_Init(void)
{
	/*
		����ST�̼���������ļ��Ѿ�ִ����CPUϵͳʱ�ӵĳ�ʼ�������Բ����ٴ��ظ�����ϵͳʱ�ӡ�
		�����ļ�������CPU��ʱ��Ƶ�ʡ��ڲ�Flash�����ٶȺͿ�ѡ���ⲿSRAM FSMC��ʼ����

		ϵͳʱ��ȱʡ����Ϊ180MHz�������Ҫ���ģ������޸� system_stm32f4xx.c �ļ�
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
	
	HAL_Delay(10);				/*��ʼ����ʱ���ȴ�ʱ���ȶ�*/
//	SystemCoreClockUpdate();	/* ����PLL���ø���ϵͳʱ��Ƶ�ʱ��� SystemCoreClock */
	/* ���ȼ���������Ϊ4 */
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	BSP_LED_Init();		/* ����LED */
//	BSP_GPIO_Init();	/* ������������˿� */
	BSP_UART_Init();	/* ��ʼ������ */
//	bsp_InitKey();		/* ��ʼ������ */
//	bsp_InitTimer();	/* ��ʼ��ϵͳ�δ�ʱ�� (�˺����Ὺ systick �ж�, tim2-5�ж�) */
	printf("Hardware Abstraction Layer init completed!\r\n");
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_RunPer10ms
*	����˵��: �ú���ÿ��10ms��Systick�жϵ���1�Ρ���� bsp_timer.c�Ķ�ʱ�жϷ������һЩ����ʱ��Ҫ���ϸ��
*			������Է��ڴ˺��������磺����ɨ�衢���������п��Ƶȡ�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void BSP_RunPer10ms(void)
{
//	bsp_KeyScan();
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_RunPer1ms
*	����˵��: �ú���ÿ��1ms��Systick�жϵ���1�Ρ���� bsp_timer.c�Ķ�ʱ�жϷ������һЩ��Ҫ�����Դ��������
*			 ���Է��ڴ˺��������磺��������ɨ�衣
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void BSP_RunPer1ms(void)
{
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_Idle
*	����˵��: ����ʱִ�еĺ�����һ����������for��whileѭ������������Ҫ���� CPU_IDLE() �������ñ�������
*			 ������ȱʡΪ�ղ������û��������ι��������CPU��������ģʽ�Ĺ��ܡ�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/

void BSP_Idle(void)
{
	/* --- ι�� */

	/* --- ��CPU�������ߣ���Systick��ʱ�жϻ��ѻ��������жϻ��� */

	/* ���� emWin ͼ�ο⣬���Բ���ͼ�ο���Ҫ����ѯ���� */
	//GUI_Exec();

	/* ���� uIP Э�飬���Բ���uip��ѯ���� */
}

/************************ (C) COPYRIGHT XCMG GROUP *****END OF FILE****/


