/**
  ******************************************************************************
  * @file    bsp_gpio.c
  * @author  Wendell
  * @version V1.0
  * @date    2019-2-28 
  * @brief   GPIO driver.
  *          
  * @modefy 
  *			version		 date		author		 remark
  *			  V1.0    2019-2-28 	Wendell  	released
  *
  * Copyright (C) 2019 XCMG Group.
  ******************************************************************************
**/
  
#include "stm32f4xx_hal.h"
#include <bsp_gpio.h>

//BSP_GPIO_CFG input_config[] = {
//    {GPIOE, GPIO_PIN_2,  GPIO_MODE_INPUT, 0x00},   /* 00 - PE2  - 加 */
//    {GPIOE, GPIO_PIN_3,  GPIO_MODE_INPUT, 0x00},   /* 01 - PE3  - 减 */
//    {GPIOE, GPIO_PIN_4,  GPIO_MODE_INPUT, 0x00},   /* 02 - PE4  - 灵敏度功能按键 */
//    {GPIOE, GPIO_PIN_5,  GPIO_MODE_INPUT, 0x00},   /* 03 - PE5  - 基准快速设定 */
//    {GPIOE, GPIO_PIN_6,  GPIO_MODE_INPUT, 0x00},   /* 04 - PE6  - ON/STANDBY */
//    {GPIOC, GPIO_PIN_13, GPIO_MODE_INPUT, 0x00},   /* 05 - PC13 - A/M */

//};

BSP_GPIO_ConfigTypeDef output_config[] = {
    {GPIO_LED0, GPIOB, GPIO_PIN_1, GPIO_MODE_OUTPUT_PP, 0x00},   /* 00 - PB11 - 米字灯中心 */
    {GPIO_LED1, GPIOB, GPIO_PIN_0, GPIO_MODE_OUTPUT_PP, 0x00},   /* 01 - PB10 - 米字灯上线 */    
};

//uint16_t input_count    = sizeof (input_config) / sizeof(BSP_GPIO_CFG);
uint16_t output_count   = sizeof (output_config) / sizeof(BSP_GPIO_ConfigTypeDef);

void BSP_GPIO_Init(void)
{
    int count;
    BSP_GPIO_ConfigTypeDef *iocfg;

    GPIO_InitTypeDef GPIO_InitStructure;
    __HAL_RCC_GPIOB_CLK_ENABLE();           //开启GPIOB时钟
  
    // input io init
//    count = input_count;
//    iocfg = &input_config[0];

//    while(count--) {
//        GPIO_InitStructure.Pin   = iocfg->pin;
//        GPIO_InitStructure.Mode  = iocfg->mode;
//        GPIO_InitStructure.Pull  = GPIO_PULLUP;
//        HAL_GPIO_Init(iocfg->port, &GPIO_InitStructure);
//        iocfg++;
//    }

    // output io init
    count = output_count;
    iocfg = &output_config[0];

    while(count--) {
        // 先配置输出值
		if(iocfg->record)
		{
			HAL_GPIO_WritePin(iocfg->port, iocfg->pin, GPIO_PIN_SET);
		}
		else 
		{	
			HAL_GPIO_WritePin(iocfg->port, iocfg->pin, GPIO_PIN_RESET);
		}
        // 再将IO设置为输出
        GPIO_InitStructure.Pin   = iocfg->pin;
        GPIO_InitStructure.Mode  = iocfg->mode;
        GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
        GPIO_InitStructure.Pull  = GPIO_NOPULL;
        HAL_GPIO_Init(iocfg->port, &GPIO_InitStructure);
        iocfg++;
    }
}

void BSP_GPIO_SetDir(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BSP_GPIO_DirState DirState)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    if (DirState == BSP_DIR_OUTPUT) {
        GPIO_InitStructure.Pin   = GPIO_Pin;
        GPIO_InitStructure.Mode  = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStructure.Pull  = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOx, &GPIO_InitStructure);
    }

    if (DirState == BSP_DIR_INPUT) {
        GPIO_InitStructure.Pin   = GPIO_Pin;
        GPIO_InitStructure.Mode  = GPIO_MODE_INPUT;
        GPIO_InitStructure.Pull  = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOx, &GPIO_InitStructure);
    }
}


int16_t BSP_GPIO_SetValue(BSP_GPIO_ChannelTypeDef ChannelNum, BSP_GPIO_ValueState ValueState)
{
    BSP_GPIO_ConfigTypeDef *output;

    if (ChannelNum >= output_count) {
        return -1;
    }

    output = &output_config[ChannelNum];

    if (ValueState == BSP_GPIO_TOGGLE) {
        HAL_GPIO_TogglePin(output->port, output->pin);
    }

    // 要改的值与原来值相同
    if (ValueState == output->record) {
        return 0;
    }

    switch (ValueState) {
        case BSP_GPIO_HIGH:
            HAL_GPIO_WritePin(output->port, output->pin, GPIO_PIN_SET);
            break;

        case BSP_GPIO_LOW:
            HAL_GPIO_WritePin(output->port, output->pin, GPIO_PIN_RESET);
            break;

        case BSP_GPIO_TOGGLE:
            break;

        case BSP_GPIO_TRISTATE:
            BSP_GPIO_SetDir(output->port, output->pin, BSP_DIR_INPUT);  // set IO as input
            break;

        default:
            return -1;
    }

    // 保存设置值
    output->record = ValueState;

    return 0;
}

int16_t BSP_GPIO_GetValue(BSP_GPIO_ChannelTypeDef ChannelNum)
{
    BSP_GPIO_ConfigTypeDef *output;
	int16_t  GetValue;
    if (ChannelNum >= output_count) {
        return -1;
    }

    output = &output_config[ChannelNum];

    GetValue = (int16_t)HAL_GPIO_ReadPin(output->port, output->pin);
           

    return 0;
}


uint16_t BSP_GPIO_OutputCount(void)
{
    return output_count;
}

/************************ (C) COPYRIGHT XCMG GROUP *****END OF FILE****/
