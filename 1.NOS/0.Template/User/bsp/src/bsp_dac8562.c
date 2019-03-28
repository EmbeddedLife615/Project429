/*
*********************************************************************************************************
*
*	ģ������ : DAC8562/8563 ����ģ��(��ͨ����16λDAC)
*	�ļ����� : bsp_dac8562.c
*	��    �� : V1.1
*	˵    �� : DAC8562/8563ģ���CPU֮�����SPI�ӿڡ�����������֧��Ӳ��SPI�ӿں�����SPI�ӿڡ�
*			  ͨ�����л���
*
*	�޸ļ�¼ :
*		�汾��  ����         ����     ˵��
*		V1.0    2014-01-17  armfly  ��ʽ����
*		V1.1    2015-10-09  armfly  �������ߴ���LDAC������Ҫ�ӵأ�CLRҲ��Ҫ�ӵ�
*
*	Copyright (C), 2015-2020, ���������� www.armfly.com
*
*********************************************************************************************************
*/

#include "bsp.h"

/*
	DAC8562ģ�����ֱ�Ӳ嵽STM32-V6������CN19��ĸ(2*4P 2.54mm)�ӿ���

    DAC8562/8563ģ��    STM32-V6������
	  GND   ------  GND
	  VCC   ------  3.3V

	  LDAC  ------  ��չIO/NRF24L01_CE/DAC1_OUT    --- ����ӵػ�ָ��ǰ��0V
      SYNC  ------  PG10/NRF24L01_CSN

      SCLK  ------  PB3/SPI3_SCK
      DIN   ------  PB5/SPI3_MOSI

			------  PB4/SPI3_MISO         ---- DAC�޶�������
	  CLR   ------  PE4/NRF24L01_IRQ	  ---  �Ƽ���GND��
*/

/*
	DAC8562��������:
	1������2.7 - 5V;  ������ʹ��3.3V��
	4���ο���ѹ2.5V��ʹ���ڲ��ο�

	��SPI��ʱ���ٶ�Ҫ��: �ߴ�50MHz�� �ٶȺܿ�.
	SCLK�½��ض�ȡ����, ÿ�δ���24bit���ݣ� ��λ�ȴ�
*/

/* ����GPIO�˿� */
#define USE_HC574

/* Ƭѡ */
#define DAC8562_RCC_CS 		RCC_AHB1Periph_GPIOG
#define DAC8562_PORT_CS		GPIOG
#define DAC8562_PIN_CS		GPIO_Pin_10

/* CLR */
#define DAC8562_RCC_CLR 	RCC_AHB1Periph_GPIOH
#define DAC8562_PORT_CLR	GPIOH
#define DAC8562_PIN_CLR		GPIO_Pin_7

/* LDAC */
#ifdef USE_HC574	/* ʹ����չIO */
	#define DAC8562_LDAC_0()	HC574_SetPin(NRF24L01_CE, 0);
	#define DAC8562_LDAC_1()	HC574_SetPin(NRF24L01_CE, 1);
#else
	#define DAC8562_RCC_LDAC 	RCC_AHB1Periph_GPIOA
	#define DAC8562_PORT_LDAC	GPIOA
	#define DAC8562_PIN_LDAC	GPIO_Pin_4

	#define DAC8562_LDAC_0()	DAC8562_PORT_LDAC->BSRRH = DAC8562_PIN_LDAC
	#define DAC8562_LDAC_1()	DAC8562_PORT_LDAC->BSRRL = DAC8562_PIN_LDAC
#endif

/* ���������0����1�ĺ� */
#define DAC8562_CS_0()	DAC8562_PORT_CS->BSRRH = DAC8562_PIN_CS
#define DAC8562_CS_1()	DAC8562_PORT_CS->BSRRL = DAC8562_PIN_CS

#define DAC8562_CLR_0()	DAC8562_PORT_CLR->BSRRH = DAC8562_PIN_CLR
#define DAC8562_CLR_1()	DAC8562_PORT_CLR->BSRRL = DAC8562_PIN_CLR

static void DAC8562_ConfigGPIO(void);
static void DAC8562_WriteCmd(uint32_t _cmd);

/* �����ѹ��DACֵ��Ĺ�ϵ�� ����У׼ x��dac y �ǵ�ѹ 0.1mV */
#define X1	0
#define Y1  -100000

#define X2	65535
#define Y2  100000

/*
*********************************************************************************************************
*	�� �� ��: bsp_InitDAC8562
*	����˵��: ����STM32��GPIO��SPI�ӿڣ��������� DAC8562
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_InitDAC8562(void)
{
	DAC8562_ConfigGPIO();
	
	DAC8562_CLR_0();		/* CLR��GND�ɿ�һЩ��CLR���½��ش��� */
	DAC8562_LDAC_0();		/* �����첽����ģʽ�������Ž�GND */

	/* Power up DAC-A and DAC-B */
	DAC8562_WriteCmd((4 << 19) | (0 << 16) | (3 << 0));

	/* LDAC pin inactive for DAC-B and DAC-A  ��ʹ��LDAC���Ÿ������� */
	DAC8562_WriteCmd((6 << 19) | (0 << 16) | (3 << 0));

	/* ��λ2��DAC���м�ֵ, ���0V */
	DAC8562_SetDacData(0, 32767);
	DAC8562_SetDacData(1, 32767);

	/* ѡ���ڲ��ο�����λ2��DAC������=2 ����λʱ���ڲ��ο��ǽ�ֹ��) */
	DAC8562_WriteCmd((7 << 19) | (0 << 16) | (1 << 0));
}

/*
*********************************************************************************************************
*	�� �� ��: DAC8562_SetCS(0)
*	����˵��: ����CS�� ����������SPI������
*	��    ��: ��
	�� �� ֵ: ��
*********************************************************************************************************
*/
void DAC8562_SetCS(uint8_t _level)
{
	if (_level == 0)
	{
		bsp_SpiBusEnter();	/* ռ��SPI���ߣ� �������߹��� */

		#ifdef SOFT_SPI		/* ����SPI */
			bsp_SetSpiSck(0);
			DAC8562_CS_0();
		#endif

		#ifdef HARD_SPI		/* Ӳ��SPI */
			bsp_SPI_Init(SPI_Direction_2Lines_FullDuplex | SPI_Mode_Master | SPI_DataSize_8b
				| SPI_CPOL_Low | SPI_CPHA_1Edge | SPI_NSS_Soft | SPI_BaudRatePrescaler_8 | SPI_FirstBit_MSB);
			DAC8562_CS_0();
		#endif
	}
	else
	{
		DAC8562_CS_1();

		bsp_SpiBusExit();	/* �ͷ�SPI���ߣ� �������߹��� */
	}
}

/*
*********************************************************************************************************
*	�� �� ��: DAC8562_ConfigGPIO
*	����˵��: ����GPIO�� ������ SCK  MOSI  MISO ������SPI���ߡ�
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void DAC8562_ConfigGPIO(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* ��GPIOʱ�� */
	RCC_AHB1PeriphClockCmd(DAC8562_RCC_CS, ENABLE);

	DAC8562_CS_1();

	/* ���ü����������IO */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		/* ��Ϊ����� */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		/* ��Ϊ����ģʽ */
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	/* ���������費ʹ�� */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	/* IO������ٶ� */

	/* SYNC */
	GPIO_InitStructure.GPIO_Pin = DAC8562_PIN_CS;
	GPIO_Init(DAC8562_PORT_CS, &GPIO_InitStructure);
	
	/* CLR */
	GPIO_InitStructure.GPIO_Pin = DAC8562_PIN_CLR;
	GPIO_Init(DAC8562_PORT_CLR, &GPIO_InitStructure);	
	
#ifdef USE_HC574	/* ʹ����չIO */
	;
#else
	/* LDAC */
	GPIO_InitStructure.GPIO_Pin = DAC8562_PIN_LDAC;
	GPIO_Init(DAC8562_PORT_LDAC, &GPIO_InitStructure);
#endif
}

/*
*********************************************************************************************************
*	�� �� ��: DAC8562_WriteCmd
*	����˵��: ��SPI���߷���24��bit���ݡ�
*	��    ��: _cmd : ����
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void DAC8562_WriteCmd(uint32_t _cmd)
{
	DAC8562_SetCS(0);

	/*��DAC8562 SCLKʱ�Ӹߴ�50M����˿��Բ��ӳ� */

	/*��DAC8501 SCLKʱ�Ӹߴ�30M����˿��Բ��ӳ� */
	bsp_spiWrite0(_cmd >> 16);
	bsp_spiWrite0(_cmd >> 8);
	bsp_spiWrite0(_cmd);

	DAC8562_SetCS(1);
}

/*
*********************************************************************************************************
*	�� �� ��: DAC8562_SetDacData
*	����˵��: ����DAC��������������¡�
*	��    ��: _ch, ͨ��, 0 , 1
*		     _data : ����
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void DAC8562_SetDacData(uint8_t _ch, uint16_t _dac)
{
	if (_ch == 0)
	{
		/* Write to DAC-A input register and update DAC-A; */
		DAC8562_WriteCmd((3 << 19) | (0 << 16) | (_dac << 0));
	}
	else if (_ch == 1)
	{
		/* Write to DAC-B input register and update DAC-A; */
		DAC8562_WriteCmd((3 << 19) | (1 << 16) | (_dac << 0));
	}
}


/*
*********************************************************************************************************
*	�� �� ��: DAC8562_DacToVoltage
*	����˵��: ��DACֵ����Ϊ��ѹֵ����λ0.1mV
*	��    ��: _dac  16λDAC��
*	�� �� ֵ: ��ѹ����λ0.1mV
*********************************************************************************************************
*/
int32_t DAC8562_DacToVoltage(uint16_t _dac)
{
	int32_t y;

	/* CaculTwoPoint(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x);*/
	y =  CaculTwoPoint(X1, Y1, X2, Y2, _dac);
	return y;
}

/*
*********************************************************************************************************
*	�� �� ��: DAC8562_VoltageToDac
*	����˵��: ��DACֵ����Ϊ��ѹֵ����λ 0.1mV
*	��    ��: _volt ��ѹ����λ0.1mV
*	�� �� ֵ: 16λDAC��
*********************************************************************************************************
*/
uint32_t DAC8562_VoltageToDac(int32_t _volt)
{
	/* CaculTwoPoint(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x);*/
	return CaculTwoPoint(Y1, X1, Y2, X2, _volt);
}

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/