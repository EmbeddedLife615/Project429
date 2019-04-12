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
	printf("* FML�汾 : V%d.%d.%d (Function Module Layer version)\r\n", __FML_VERSION_MAIN,
			__FML_VERSION_SUB1,__FML_VERSION_SUB2);
}											 
/*
*********************************************************************************************************
*	�� �� ��: FML_Init
*	����˵��: ����ģ���ĳ�ʼ�����������¼���ʼ��������ֻ��Ҫ����һ�Ρ�����ģ���FML-->�弶֧�ְ�BSP-->Ӳ�������HAL
*			  �ú����� APP_Init() ���á�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void FML_Init(void)
{
	BSP_Init();
	FML_LED_Init(); 	/* ��ʼLEDָʾ�ƶ˿� */
	printf("Function Module Layer init completed!\r\n");
}



///*
//*********************************************************************************************************
//*	�� �� ��: bsp_RunPer10ms
//*	����˵��: �ú���ÿ��10ms��Systick�жϵ���1�Ρ���� bsp_timer.c�Ķ�ʱ�жϷ������һЩ����ʱ��Ҫ���ϸ��
//*			������Է��ڴ˺��������磺����ɨ�衢���������п��Ƶȡ�
//*	��    �Σ���
//*	�� �� ֵ: ��
//*********************************************************************************************************
//*/
//void bsp_RunPer10ms(void)
//{
////	bsp_KeyScan();
//}

///*
//*********************************************************************************************************
//*	�� �� ��: bsp_RunPer1ms
//*	����˵��: �ú���ÿ��1ms��Systick�жϵ���1�Ρ���� bsp_timer.c�Ķ�ʱ�жϷ������һЩ��Ҫ�����Դ��������
//*			 ���Է��ڴ˺��������磺��������ɨ�衣
//*	��    ��: ��
//*	�� �� ֵ: ��
//*********************************************************************************************************
//*/
//void bsp_RunPer1ms(void)
//{
//}

/*
*********************************************************************************************************
*	�� �� ��: bsp_Idle
*	����˵��: ����ʱִ�еĺ�����һ����������for��whileѭ������������Ҫ���� CPU_IDLE() �������ñ�������
*			 ������ȱʡΪ�ղ������û��������ι��������CPU��������ģʽ�Ĺ��ܡ�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/

void FML_Idle(void)
{
	BSP_Idle();
	/* --- ι�� */

	/* --- ��CPU�������ߣ���Systick��ʱ�жϻ��ѻ��������жϻ��� */

	/* ���� emWin ͼ�ο⣬���Բ���ͼ�ο���Ҫ����ѯ���� */
	//GUI_Exec();

	/* ���� uIP Э�飬���Բ���uip��ѯ���� */
}

///************************ (C) COPYRIGHT XCMG GROUP *****END OF FILE****/



