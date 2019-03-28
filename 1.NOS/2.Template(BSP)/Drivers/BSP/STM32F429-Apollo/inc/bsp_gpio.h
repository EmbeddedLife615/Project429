/*-----------------------------------------------------------------------
* io.h  -
*
*
*
* Copyright (C) 2016 XCMG Group.
*
*-----------------------------------------------------------------------*/
#ifndef _BSP_GPIO_H_
#define _BSP_GPIO_H_

typedef struct {
	uint8_t 		channel;
    GPIO_TypeDef*   port;
    uint16_t        pin;
    uint32_t   		mode;
    uint32_t        record;
} BSP_GPIO_ConfigTypeDef;


/** 
  * @brief  GPIO Configuration GPIO Channel enumeration 
  */ 
typedef enum
{ 
  GPIO_LED0 = 0,
  GPIO_LED1,
}BSP_GPIO_ChannelTypeDef;
#define IS_BSP_GPIO_LED(LED) (((LED) == GPIO_LED0) || ((LED) == GPIO_LED1) )
#define IS_BSP_GPIO_CHANNEL(CHANNEL) (((CHANNEL) == GPIO_LED0) || ((CHANNEL) == GPIO_LED1) )
//|| \
//                            ((FUNC) == GPIO_PuPd_DOWN))
/** 
  * @brief  GPIO Bit Direction Input and Bit Direction Output enumeration 
  */
typedef enum
{
  BSP_DIR_INPUT = 0,
  BSP_DIR_OUTPUT
}BSP_GPIO_DirState;

/** 
  * @brief  GPIO Bit Direction Input and Bit Direction Output enumeration 
  */
typedef enum
{
	BSP_GPIO_LOW = 0,
	BSP_GPIO_HIGH,
	BSP_GPIO_TOGGLE,
	BSP_GPIO_TRISTATE
}BSP_GPIO_ValueState;


extern BSP_GPIO_ConfigTypeDef input_config[];
extern BSP_GPIO_ConfigTypeDef output_config[];
extern uint16_t input_count;
extern uint16_t output_count;

void BSP_GPIO_Init(void);
void BSP_GPIO_SetDir(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BSP_GPIO_DirState DirState);
int16_t BSP_GPIO_SetValue(BSP_GPIO_ChannelTypeDef ChannelNum, BSP_GPIO_ValueState ValueState);
int16_t BSP_GPIO_GetValue(BSP_GPIO_ChannelTypeDef ChannelNum);
uint16_t BSP_GPIO_Count(void);
#endif /* _BSP_GPIO_H_ */
