/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  Wendell
  * @date    2019-3-21 
  * @brief   LED interface for STM32F429-Apollo Kit
  *          
  * Change Logs: 
  *				 Date		Author		 Notes
  *			  2019-2-28 	Wendell  	released
  *
  * Copyright (C) 2019 XCMG Group.
  ******************************************************************************
**/

#include "bsp_led.h"

/****
	* @fn     void BSP_LED_Init (void)
	* @brief  Configure all the LED GPIOs
	*/
void BSP_LED_Init (void) 
{
	uint32_t n;
	GPIO_InitTypeDef GPIO_InitStruct;
	
	/* Configure GPIO pins */
	for (n = 0; n < LED_COUNT; n++) 
	{
		/* GPIO Ports Clock Enable */
		LEDx_GPIO_CLK_ENABLE(n);
		// 先配置输出值
		if(LED_PIN[n].record)
		{
			HAL_GPIO_WritePin(LED_PIN[n].port, LED_PIN[n].pin, GPIO_PIN_SET);
		}
		else 
		{	
			HAL_GPIO_WritePin(LED_PIN[n].port, LED_PIN[n].pin, GPIO_PIN_RESET);
		}
		GPIO_InitStruct.Pin   = LED_PIN[n].pin;
		GPIO_InitStruct.Mode  = LED_PIN[n].mode;
		GPIO_InitStruct.Pull  = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(LED_PIN[n].port, &GPIO_InitStruct);
	}
}

/****
	* @fn     void BSP_LED_InitOne(LED_TypeDef Led)
	* @brief  Configures specified LED GPIO.
	* @param  LED: Specifies the LED to be configured. 
	*   This parameter can be one of following parameters:
	*     @arg LED0
	*     @arg LED1
	*@retval  none
	*/
void BSP_LED_InitOne(LED_TypeDef Led)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	assert_param(IS_BSP_GPIO_LED(Led));
	
	/* Enable the GPIO_LED Clock */
	LEDx_GPIO_CLK_ENABLE(Led);
	
	/* Configure the GPIO_LED pin */
	// 先配置输出值
	if(LED_PIN[Led].record)
	{
		HAL_GPIO_WritePin(LED_PIN[Led].port, LED_PIN[Led].pin, GPIO_PIN_SET);
	}
	else 
	{	
		HAL_GPIO_WritePin(LED_PIN[Led].port, LED_PIN[Led].pin, GPIO_PIN_RESET);
	} 
	
	GPIO_InitStruct.Pin = LED_PIN[Led].pin;
	GPIO_InitStruct.Mode = LED_PIN[Led].mode;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(LED_PIN[Led].port, &GPIO_InitStruct);
}

/****
	* @fn     void BSP_LED_DeInit (void) 
	* @brief  De-initialize all the LED GPIOS
	*/
void BSP_LED_DeInit (void) 
{
	uint32_t n;
	for (n = 0; n < LED_COUNT; n++) 
	{
		HAL_GPIO_DeInit(LED_PIN[n].port, LED_PIN[n].pin);
	}
}

/****
	* @fn     void BSP_LED_DeInitOne (LED_TypeDef Led) 
	* @brief  De-initialize specified LED GPIO
	* @param  LED: Specifies the LED to be De-initialized. 
	*   This parameter can be one of following parameters:
	*     @arg LED0
	*     @arg LED1
	*/
void BSP_LED_DeInitOne (LED_TypeDef Led) 
{
	assert_param(IS_BSP_GPIO_LED(Led));
	HAL_GPIO_DeInit(LED_PIN[Led].port, LED_PIN[Led].pin);
}

/****
	* @fn     void BSP_LED_On(LED_TypeDef Led)
	* @brief  Turns selected LED On.
	* @param  Led: Specifies the Led to be set on. 
	*   This parameter can be one of following parameters:
	*     @arg LED3
	*     @arg LED4 
	*/
void BSP_LED_On(LED_TypeDef Led)
{
	assert_param(IS_BSP_GPIO_LED(Led));
	HAL_GPIO_WritePin(LED_PIN[Led].port, LED_PIN[Led].pin, GPIO_PIN_RESET); 
}

/****
	* @fn     void BSP_LED_Off(LED_TypeDef Led)
	* @brief  Turns selected LED Off.
	* @param  Led: Specifies the Led to be set off. 
	*   This parameter can be one of following parameters:
	*     @arg LED3
	*     @arg LED4
	*/
void BSP_LED_Off(LED_TypeDef Led)
{
	assert_param(IS_BSP_GPIO_LED(Led));
	HAL_GPIO_WritePin(LED_PIN[Led].port, LED_PIN[Led].pin, GPIO_PIN_SET); 
}

/****
	* @fn     void BSP_LED_Toggle(LED_TypeDef Led)
	* @brief  Toggles the selected LED.
	* @param  Led: Specifies the Led to be toggled. 
	*   This parameter can be one of following parameters:
	*     @arg LED3
	*     @arg LED4  
	*/
void BSP_LED_Toggle(LED_TypeDef Led)
{
	assert_param(IS_BSP_GPIO_LED(Led));
	
	HAL_GPIO_TogglePin(LED_PIN[Led].port, LED_PIN[Led].pin);
}

/****
	* @fn     void BSP_LED_SetVal (uint32_t val) 
	* @brief  Write value to LEDs
	* @param  val: value to be displayed on LEDs , each bit corresponds to an LED  
	*/
void BSP_LED_SetVal (uint32_t val) 
{
	uint32_t n;
	LED_TypeDef LedVal;

	for (n = 0; n < LED_COUNT; n++) {
		LedVal = (LED_TypeDef)(val & (1 << n));
		if (LedVal)	BSP_LED_On (LedVal);
		else        BSP_LED_Off(LedVal);
	}
}

/****
	* @fn     uint32_t BSP_LED_GetCount (void) 
	* @brief  Number of available LEDs
	*@retval  LED_COUNT: LED number 
	*/
uint32_t BSP_LED_GetCount (void) 
{
  return LED_COUNT;
}


/****
	* @fn     uint8_t BSP_LED_IsOn(LED_TypeDef Led)
	* @brief  Determine whether the LED is on
	* @param  LED: Specifies the LED to be configured. 
	*   This parameter can be one of following parameters:
	*     @arg LED0
	*     @arg LED1
	*@retval  retCode: function state
	*		@b   0:  LED is on
	*		@b   1:  LED is off
	*/
uint8_t BSP_LED_IsOn(LED_TypeDef Led)
{
    uint8_t PinState;
	assert_param(IS_BSP_GPIO_LED(Led));
	
	PinState = (int8_t)HAL_GPIO_ReadPin(LED_PIN[Led].port, LED_PIN[Led].pin);
    return PinState;
}


/************************ (C) COPYRIGHT XCMG GROUP *****END OF FILE****/
