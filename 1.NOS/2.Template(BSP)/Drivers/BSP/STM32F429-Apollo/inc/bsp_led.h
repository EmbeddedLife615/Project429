/**
  ******************************************************************************
  * @file    bsp_led.h
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

#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "stm32f4xx_hal.h"


/** @addtogroup STM32F429_APOLLO_LOW_LEVEL_Exported_Types STM32F429 APOLLO LOW LEVEL Exported Types
  * @{
  */
typedef enum 
{
  LED0 = 0,
  LED1
}LED_TypeDef;
#define IS_BSP_GPIO_LED(LED) (((LED) == LED0) || ((LED) == LED1) )

/* GPIO Pin identifier */
typedef struct _GPIO_PIN 
{
  GPIO_TypeDef *port;
  uint16_t      pin;
  uint32_t   	mode;
  uint32_t      record;
} GPIO_PIN;

/* LED GPIO Pins */
static const GPIO_PIN LED_PIN[] = 
{
  { GPIOB, GPIO_PIN_1, GPIO_MODE_OUTPUT_PP, 0U },
  { GPIOB, GPIO_PIN_0, GPIO_MODE_OUTPUT_PP, 0U }
};

#define LED_COUNT (sizeof(LED_PIN)/sizeof(GPIO_PIN))

/** @defgroup STM32F429_APOLLO_LOW_LEVEL_LED STM32F429 APOLLO LOW LEVEL LED
  * @{
  */
#define LEDn                                    2
  
#define LED0_PIN                                GPIO_PIN_1
#define LED0_GPIO_PORT                          GPIOB
#define LED0_GPIO_CLK_ENABLE()                  __HAL_RCC_GPIOB_CLK_ENABLE()  
#define LED0_GPIO_CLK_DISABLE()                 __HAL_RCC_GPIOB_CLK_DISABLE()  

#define LED1_PIN                                GPIO_PIN_0
#define LED1_GPIO_PORT                          GPIOB
#define LED1_GPIO_CLK_ENABLE()                  __HAL_RCC_GPIOB_CLK_ENABLE()  
#define LED1_GPIO_CLK_DISABLE()                 __HAL_RCC_GPIOB_CLK_DISABLE()  

#define LEDx_GPIO_CLK_ENABLE(__INDEX__)  do{if((__INDEX__) == 0) LED0_GPIO_CLK_ENABLE(); else \
                                            if((__INDEX__) == 1) LED1_GPIO_CLK_ENABLE(); \
                                            }while(0)
#define LEDx_GPIO_CLK_DISABLE(__INDEX__) do{if((__INDEX__) == 0) LED0_GPIO_CLK_DISABLE(); else \
                                            if((__INDEX__) == 1) LED1_GPIO_CLK_DISABLE(); \
                                            }while(0)



/****
	* @fn     void BSP_LED_Init (void)
	* @brief  Configure all the LED GPIOs
	*/
extern void BSP_LED_Init (void)
	;
/****
	* @fn     void BSP_LED_InitOne(LED_TypeDef Led)
	* @brief  Configures specified LED GPIO.
	* @param  LED: Specifies the LED to be configured. 
	*   This parameter can be one of following parameters:
	*     @arg LED0
	*     @arg LED1
	*@retval  none
	*/
extern void BSP_LED_InitOne(LED_TypeDef Led);

/****
	* @fn     void BSP_LED_DeInit (void) 
	* @brief  De-initialize all the LED GPIOS
	*/
extern void BSP_LED_DeInit (void) ;

/****
	* @fn     void BSP_LED_DeInitOne (LED_TypeDef Led) 
	* @brief  De-initialize specified LED GPIO
	* @param  LED: Specifies the LED to be De-initialized. 
	*   This parameter can be one of following parameters:
	*     @arg LED0
	*     @arg LED1
	*/
extern void BSP_LED_DeInitOne (LED_TypeDef Led);

/****
	* @fn     void BSP_LED_On(LED_TypeDef Led)
	* @brief  Turns selected LED On.
	* @param  Led: Specifies the Led to be set on. 
	*   This parameter can be one of following parameters:
	*     @arg LED3
	*     @arg LED4 
	*/
extern void BSP_LED_On(LED_TypeDef Led);

/****
	* @fn     void BSP_LED_Off(LED_TypeDef Led)
	* @brief  Turns selected LED Off.
	* @param  Led: Specifies the Led to be set off. 
	*   This parameter can be one of following parameters:
	*     @arg LED3
	*     @arg LED4
	*/
extern void BSP_LED_Off(LED_TypeDef Led);

/****
	* @fn     void BSP_LED_Toggle(LED_TypeDef Led)
	* @brief  Toggles the selected LED.
	* @param  Led: Specifies the Led to be toggled. 
	*   This parameter can be one of following parameters:
	*     @arg LED3
	*     @arg LED4  
	*/
extern void BSP_LED_Toggle(LED_TypeDef Led);


/****
	* @fn     void BSP_LED_SetVal (uint32_t val) 
	* @brief  Write value to LEDs
	* @param  val: value to be displayed on LEDs , each bit corresponds to an LED  
	*/
extern void BSP_LED_SetVal (uint32_t val) ;

/****
	* @fn     uint32_t BSP_LED_GetCount (void) 
	* @brief  Number of available LEDs
	*@retval  LED_COUNT: LED number 
	*/
extern uint32_t BSP_LED_GetCount (void) ;

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
extern uint8_t BSP_LED_IsOn(LED_TypeDef Led);

#endif /* __BSP_LED_H */

/************************ (C) COPYRIGHT XCMG GROUP *****END OF FILE****/

