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
	uint32_t		pull;
    uint32_t        record;
} BSP_GPIO_ConfigTypeDef;


/** 
  * @brief  GPIO Configuration GPIO Channel enumeration 
  */ 
typedef enum
{ 
	GPIO_CHANNEL0 = 0,
	GPIO_CHANNEL1,
	GPIO_CHANNEL2,
	GPIO_CHANNEL3,
	GPIO_CHANNEL4,
	GPIO_CHANNEL5,
	GPIO_CHANNEL6,
	GPIO_CHANNEL7,
	GPIO_CHANNEL8,
	GPIO_CHANNEL9,
}BSP_GPIO_ChannelTypeDef;
#define IS_BSP_GPIO_CHANNEL(CHANNEL) (((CHANNEL) == GPIO_CHANNEL0) || ((CHANNEL) == GPIO_CHANNEL1)\
										(CHANNEL) == GPIO_CHANNEL2) || ((CHANNEL) == GPIO_CHANNEL3)\
										(CHANNEL) == GPIO_CHANNEL4) || ((CHANNEL) == GPIO_CHANNEL5)\
										(CHANNEL) == GPIO_CHANNEL6) || ((CHANNEL) == GPIO_CHANNEL7)\
										(CHANNEL) == GPIO_CHANNEL8) || ((CHANNEL) == GPIO_CHANNEL9))
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
int16_t BSP_GPIO_SetDir(BSP_GPIO_ChannelTypeDef ChannelNum, BSP_GPIO_DirState DirState);
int16_t BSP_GPIO_SetValue(BSP_GPIO_ChannelTypeDef ChannelNum, BSP_GPIO_ValueState ValueState);
int16_t BSP_GPIO_GetValue(BSP_GPIO_ChannelTypeDef ChannelNum);
uint16_t BSP_GPIO_Count(void);
#endif /* _BSP_GPIO_H_ */
