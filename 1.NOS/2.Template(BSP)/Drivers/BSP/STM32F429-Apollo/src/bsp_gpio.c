/**
  ******************************************************************************
  * @file    bsp_gpio.c
  * @author  Wendell
  * @date    2019-3-21 
  * @brief   GPIO driver for STM32F429-Apollo Kit
  *          
  * Change Logs: 
  *				 Date		Author		 Notes
  *			  2019-2-28 	Wendell  	released
  *
  * Copyright (C) 2019 XCMG Group.
  ******************************************************************************
**/
  
#include "stm32f4xx_hal.h"
#include <bsp_gpio.h>

BSP_GPIO_ConfigTypeDef input_config[] = {
    {GPIO_CHANNEL0, GPIOH, GPIO_PIN_3,  GPIO_MODE_INPUT, GPIO_PULLUP, 0x00},   /* 00 - PH3  - KEY0 */
    {GPIO_CHANNEL1, GPIOH, GPIO_PIN_2,  GPIO_MODE_INPUT, GPIO_PULLUP, 0x00},   /* 01 - PH2  - KEY1 */
    {GPIO_CHANNEL2, GPIOC, GPIO_PIN_13, GPIO_MODE_INPUT, GPIO_PULLUP, 0x00},   /* 02 - PC13 - KEY2 */
    {GPIO_CHANNEL3, GPIOA, GPIO_PIN_0,  GPIO_MODE_INPUT, GPIO_PULLUP, 0x00},   /* 03 - PA0  - WK-UP */
//    {GPIOE, GPIO_PIN_6,  GPIO_MODE_INPUT, 0x00},   /* 04 - PE6  - ON/STANDBY */
//    {GPIOC, GPIO_PIN_13, GPIO_MODE_INPUT, 0x00},   /* 05 - PC13 - A/M */

};

BSP_GPIO_ConfigTypeDef output_config[] = {
//    {GPIO_CHANNEL0, GPIOB, GPIO_PIN_6, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL,0x00},   /* 00 - PB6 -       */   
};

uint16_t input_count    = sizeof (input_config) / sizeof(BSP_GPIO_ConfigTypeDef);
uint16_t output_count   = sizeof (output_config) / sizeof(BSP_GPIO_ConfigTypeDef);

void BSP_GPIO_Init(void)
{
    int count;
    BSP_GPIO_ConfigTypeDef *iocfg;

    GPIO_InitTypeDef GPIO_InitStructure;
    __HAL_RCC_GPIOB_CLK_ENABLE();           //开启GPIOB时钟
  
    // input io init
    count = input_count;
    iocfg = &input_config[0];

    while(count--) {
        GPIO_InitStructure.Pin   = iocfg->pin;
        GPIO_InitStructure.Mode  = iocfg->mode;
        GPIO_InitStructure.Pull  = iocfg->pull;
        HAL_GPIO_Init(iocfg->port, &GPIO_InitStructure);
        iocfg++;
    }

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
        GPIO_InitStructure.Pull  = iocfg->pull;
        HAL_GPIO_Init(iocfg->port, &GPIO_InitStructure);
        iocfg++;
    }
}

int16_t BSP_GPIO_OutputSetDir(BSP_GPIO_ChannelTypeDef ChannelNum, BSP_GPIO_DirState DirState)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
	BSP_GPIO_ConfigTypeDef *output;

    if (ChannelNum >= output_count) {
        return -1;
    }

    output = &output_config[ChannelNum];
	
    if (DirState == BSP_DIR_OUTPUT) {
        GPIO_InitStructure.Pin   = output->pin;
        GPIO_InitStructure.Mode  = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStructure.Pull  = GPIO_NOPULL;
        HAL_GPIO_Init(output->port, &GPIO_InitStructure);
    }

    if (DirState == BSP_DIR_INPUT) {
        GPIO_InitStructure.Pin   = output->pin;
        GPIO_InitStructure.Mode  = GPIO_MODE_INPUT;
        GPIO_InitStructure.Pull  = GPIO_NOPULL;
        HAL_GPIO_Init(output->port, &GPIO_InitStructure);
    }
	return 0;
}


int16_t BSP_GPIO_OutputSetValue(BSP_GPIO_ChannelTypeDef ChannelNum, BSP_GPIO_ValueState ValueState)
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
            BSP_GPIO_SetDir(output->channel, BSP_DIR_INPUT);  // set IO as input
            break;

        default:
            return -1;
    }

    // 保存设置值
    output->record = ValueState;

    return 0;
}

//int16_t BSP_GPIO_OutputGetValue(BSP_GPIO_ChannelTypeDef ChannelNum, uint8_t* GetValue)
//{
//    BSP_GPIO_ConfigTypeDef *output;
//	
//    if (ChannelNum >= output_count) {
//        return -1;
//    }

//    output = &output_config[ChannelNum];

//    *GetValue = (uint8_t)HAL_GPIO_ReadPin(output->port, output->pin);
// 
//    return 0;
//}


uint16_t BSP_GPIO_OutputCount(void)
{
    return output_count;
}


int16_t BSP_GPIO_InputGetValue(BSP_GPIO_ChannelTypeDef ChannelNum, uint8_t* GetValue)
{
    BSP_GPIO_ConfigTypeDef *input;
	
    if (ChannelNum >= input_count) {
        return -1;
    }

    input = &input_config[ChannelNum];

    *GetValue = (uint8_t)HAL_GPIO_ReadPin(input->port, input->pin);
 
    return 0;
}

/************************ (C) COPYRIGHT XCMG GROUP *****END OF FILE****/
