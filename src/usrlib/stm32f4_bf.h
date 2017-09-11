/**
 * Файл с определениями битовых полей регистров
 * bf - bit fields
 */
#include <stdint.h>
#include "../inc/stm32f4xx.h"

#ifndef STM32F4_BF_H
#define STM32F4_BF_H

/*****************************************************************************
 *		RCC
 ****************************************************************************/
typedef struct {
	// Bit 0 HSION: Internal high-speed clock enable
	uint32_t HSION      :1;
	// Bit 1 HSIRDY: Internal high-speed clock ready flag
	uint32_t HSIRDY     :1; 
	// Bit 2 Reserved, must be kept at reset value.
	uint32_t dcb1       :1; 
	// Bits 7:3 HSITRIM[4:0]: Internal high-speed clock trimming
	uint32_t HSITRIM    :5; 
	// Bits 15:8 HSICAL[7:0]: Internal high-speed clock calibration
	uint32_t HSICAL     :8; 
	// Bit 16 HSEON: HSE clock enable
	uint32_t HSEON      :1; 
	// Bit 17 HSERDY: HSE clock ready flag
	uint32_t HSERDY     :1; 
	// Bit 18 HSEBYP: HSE clock bypass
	uint32_t HSEBYP     :1; 
	// Bit 19 CSSON: Clock security system enable
	uint32_t CSSON      :1; 
	// Bits 23:20 Reserved, must be kept at reset value.
	uint32_t dcb2       :4; 
	// Bit 24 PLLON: Main PLL (PLL) enable
	uint32_t PLLON      :1;	
	// Bit 25 PLLRDY: Main PLL (PLL) clock ready flag
	uint32_t PLLRDY		:1;	
	// Bit 26 PLLI2SON: PLLI2S enable
	uint32_t PLLI2SON	:1;	
	// Bit 27 PLLI2SRDY: PLLI2S clock ready flag
	uint32_t PLLI2SRDY	:1;	
	// Bits 31:28 Reserved, must be kept at reset value.
	uint32_t dcb3		:4;	
} RCC_CR_t;

typedef enum {
	PLLP_div2 = 0b00,
	PLLP_div4 = 0b01,
	PLLP_div6 = 0b10,
	PLLP_div8 = 0b11
} ePLLPdiv_t;

typedef enum {
	HSIsource = 0b0,
	HSEsource = 0b1
} ePLLsource_t;

typedef struct {
	// Bits 5:0 PLLM: Division factor for the main PLL (PLL) and audio PLL (PLLI2S) input clock
	// 2 ≤ PLLM ≤ 63
	uint32_t PLLM   :6;
	// Bits 14:6 PLLN: Main PLL (PLL) multiplication factor for VCO
	// 50 ≤ PLLN ≤ 432
	uint32_t PLLN   :9;
	// Bit 15 Reserved, must be kept at reset value.
	uint32_t dcb4   :1;
	// Bits 17:16 PLLP: Main PLL (PLL) division factor for main system clock
	// 00: PLLP = 2
	// 01: PLLP = 4
	// 10: PLLP = 6
	// 11: PLLP = 8
	ePLLPdiv_t PLLP   :2;
	// Bits 21:18 Reserved, must be kept at reset value.
	uint32_t dcb1   :4;
	// Bit 22 PLLSRC: Main PLL(PLL) and audio PLL (PLLI2S) entry clock source
	// 0: HSI clock selected as PLL and PLLI2S clock entry
	// 1: HSE oscillator clock selected as PLL and PLLI2S clock entry
	ePLLsource_t PLLSRC :1;
	// Bit 23 Reserved, must be kept at reset value.
	uint32_t dcb2   :1;
	// Bits 27:24 PLLQ: Main PLL (PLL) division factor for USB OTG FS, SDIO and random number generator
	// 2 ≤ PLLQ ≤ 15
	uint32_t PLLQ   :4;
	// Bits 31:28 Reserved, must be kept at reset value.
	uint32_t dcb3   :4;
} RCC_PLLCFGR_t;

typedef enum {
	AHBnotdiv	= 0,
	AHBdiv2		= 0b1000,
	AHBdiv4		= 0b1001,
	AHBdiv8		= 0b1010,
	AHBdiv16	= 0b1011,
	AHBdiv64	= 0b1100,
	AHBdiv128	= 0b1101,
	AHBdiv256	= 0b1110,
	AHBdiv512	= 0b1111
} eAHBprescaler_t;

typedef enum {
	APBnotdiv	= 0,
	APBdiv2		= 0b100,
	APBdiv4		= 0b101,
	APBdiv8		= 0b110,
	APBdiv16	= 0b111
} eAPBprescaler_t;

typedef enum {
	HSI		= 0,
	HSE		= 0b01,
	PLL		= 0b10
} eSystemClockSwitch_t;

typedef struct {
	// Bits 1:0 SW: System clock switch
	// 00: HSI oscillator selected as system clock
	// 01: HSE oscillator selected as system clock
	// 10: PLL selected as system clock
	// 11: not allowed
	eSystemClockSwitch_t SW		:2;
	// Bits 3:2 SWS: System clock switch status
	// like SW
	uint32_t SWS	:2;
	// Bits 7:4 HPRE: AHB prescaler
	// 0xxx: system clock not divided
	// 1000: system clock divided by 2
	// 1001: system clock divided by 4
	// 1010: system clock divided by 8
	// 1011: system clock divided by 16
	// 1100: system clock divided by 64
	// 1101: system clock divided by 128
	// 1110: system clock divided by 256
	// 1111: system clock divided by 512
	eAHBprescaler_t HPRE	:4;
	// Bits 9:8 Reserved, must be kept at reset value.
	uint32_t dcb1	:2;
	// Bits 12:10 PPRE1: APB Low speed prescaler (APB1)
	// 0xx: AHB clock not divided
	// 100: AHB clock divided by 2
	// 101: AHB clock divided by 4
	// 110: AHB clock divided by 8
	// 111: AHB clock divided by 16
	eAPBprescaler_t PPRE1	:3;
	// Bits 15:13 PPRE2: APB high-speed prescaler (APB2)
	// like PPRE1
	eAPBprescaler_t PPRE2	:3;
	// Bits 20:16 RTCPRE: HSE division factor for RTC clock
	// 2 ≤ PLLM ≤ 31
	uint32_t RTCPRE	:5;
	// Bits 22:21 MCO1: Microcontroller clock output 1
	// 00: HSI clock selected
	// 01: LSE oscillator selected
	// 10: HSE oscillator clock selected
	// 11: PLL clock selected
	uint32_t MCO1   :2;
	// Bit 23 I2SSRC: I2S clock selection
	// 0: PLLI2S clock used as I2S clock source
	// 1: External clock mapped on the I2S_CKIN pin used as I2S clock source
	uint32_t I2SSRC :1;
	// Bits 24:26 MCO1PRE: MCO1 prescaler
	// 0xx: no division
	// 100: division by 2
	// 101: division by 3
	// 110: division by 4
	// 111: division by 5
	uint32_t MCO1PRE    :3;
	// Bits 27:29 MCO2PRE: MCO2 prescaler
	// like MCO1PRE
	uint32_t MCO2PRE	:3;
	// Bits 31:30 MCO2[1:0]: Microcontroller clock output 2
	// 00: System clock (SYSCLK) selected
	// 01: PLLI2S clock selected
	// 10: HSE oscillator clock selected
	// 11: PLL clock selected
	uint32_t MCO2	:2;
} RCC_CFGR_t;

typedef struct {
	// Bit 0 GPIOAEN: IO port A clock enable
	uint32_t GPIOAEN	:1;
	// Bit 1 GPIOBEN: IO port B clock enable
	uint32_t GPIOBEN	:1;
	// Bit 2 GPIOCEN: IO port C clock enable
	uint32_t GPIOCEN	:1;
	// Bit 3 GPIODEN: IO port D clock enable
	uint32_t GPIODEN	:1;
	// Bit 4 GPIOEEN: IO port E clock enable
	uint32_t GPIOEEN	:1;
	// Bit 5 GPIOFEN: IO port F clock enable
	uint32_t GPIOFEN	:1;
	// Bit 6 GPIOGEN: IO port G clock enable
	uint32_t GPIOGEN	:1;
	// Bit 7 GPIOHEN: IO port H clock enable
	uint32_t GPIOHEN	:1;
	// Bit 8 GPIOIEN: IO port I clock enable
	uint32_t GPIOIEN	:1;
	// Bits 11:9 Reserved, must be kept at reset value.
	uint32_t dcb1		:3;
	// Bit 12 CRCEN: CRC clock enable
	uint32_t CRCEN		:1;
	// Bits 17:13 Reserved, must be kept at reset value.
	uint32_t dcb2		:5;
	// Bit 18 BKPSRAMEN: Backup SRAM interface clock enable
	uint32_t BKPSRAMEN	:1;
	// Bit 19 Reserved, must be kept at reset value.
	uint32_t dcb3		:1;
	// Bit 20 CCMDATARAMEN: CCM data RAM clock enable
	uint32_t CCMDATARAMEN	:1;
	// Bit 21 DMA1EN: DMA1 clock enable
	uint32_t DMA1EN		:1;
	// Bit 22 DMA2EN: DMA2 clock enable
	uint32_t DMA2EN		:1;
	// Bits 24:23 Reserved, must be kept at reset value.
	uint32_t dcb4		:2;
	// Bit 25 ETHMACEN: Ethernet MAC clock enable
	uint32_t ETHMACEN	:1;
	// Bit 26 ETHMACTXEN: Ethernet Transmission clock enable
	uint32_t ETHMACTXEN	:1;
	// Bit 27 ETHMACRXEN: Ethernet Reception clock enable
	uint32_t ETHMACRXEN	:1;
	// Bit 28 ETHMACPTPEN: Ethernet PTP clock enable
	uint32_t ETHMACPTPEN	:1;
	// Bit 29 OTGHSEN: USB OTG HS clock enable
	uint32_t OTGHSEN	:1;
	// Bit 30 OTGHSULPIEN: USB OTG HSULPI clock enable
	uint32_t OTGHSULPIEN	:1;
	// Bit 31 Reserved, must be kept at reset value.
	uint32_t dcb5		:1;
} RCC_AHB1ENR_t;


/*****************************************************************************
 *		GPIO
 ****************************************************************************/
 typedef enum {
	InputMode		= 0b00,
	OutputMode		= 0b01,
	AlternateMode	= 0b10,
	AnalogMode		= 0b11
} eMode_t;

 typedef struct {
	// Bits 2y:2y+1 MODERy[1:0]: Port x configuration bits (y = 0..15)
	// 00: Input (reset state)
	// 01: General purpose output mode
	// 10: Alternate function mode
	// 11: Analog mode
	eMode_t MODER0	:2;
	eMode_t MODER1	:2;
	eMode_t MODER2	:2;
	eMode_t MODER3	:2;
	eMode_t MODER4	:2;
	eMode_t MODER5	:2;
	eMode_t MODER6	:2;
	eMode_t MODER7	:2;
	eMode_t MODER8	:2;
	eMode_t MODER9	:2;
	eMode_t MODER10	:2;
	eMode_t MODER11	:2;
	eMode_t MODER12	:2;
	eMode_t MODER13	:2;
	eMode_t MODER14	:2;
	eMode_t MODER15	:2;
 } GPIO_MODER_t;

typedef enum {
	PushPull	= 0b0,
	OpenDrain	= 0b1
} eOutputType_t;

typedef struct {
	// Bits 15:0 OTy: Port x configuration bits (y = 0..15)
	// 0: Output push-pull (reset state)
	// 1: Output open-drain
	eOutputType_t OT0	:1;
	eOutputType_t OT1	:1;
	eOutputType_t OT2	:1;
	eOutputType_t OT3	:1;
	eOutputType_t OT4	:1;
	eOutputType_t OT5	:1;
	eOutputType_t OT6	:1;
	eOutputType_t OT7	:1;
	eOutputType_t OT8	:1;
	eOutputType_t OT9	:1;
	eOutputType_t OT10	:1;
	eOutputType_t OT11	:1;
	eOutputType_t OT12	:1;
	eOutputType_t OT13	:1;
	eOutputType_t OT14	:1;
	eOutputType_t OT15	:1;
	// Bits 31:16 Reserved, must be kept at reset value.
	uint32_t dcb1	:16;
 } GPIO_OTYPER_t;

typedef enum {
	LowSpeed	= 0b00,
	MediumSpeed	= 0b01,
	HighSpeed	= 0b10,
	VeryHighSpeed	= 0b00
} eOutputSpeed_t;

typedef struct {
	// Bits 2y:2y+1 OSPEEDRy[1:0]: Port x configuration bits (y = 0..15)
	// 00: Low speed
	// 01: Medium speed
	// 10: High speed
	// 11: Very high speed
	eOutputSpeed_t OSPEEDR0		:2;
	eOutputSpeed_t OSPEEDR1		:2;
	eOutputSpeed_t OSPEEDR2		:2;
	eOutputSpeed_t OSPEEDR3		:2;
	eOutputSpeed_t OSPEEDR4		:2;
	eOutputSpeed_t OSPEEDR5		:2;
	eOutputSpeed_t OSPEEDR6		:2;
	eOutputSpeed_t OSPEEDR7		:2;
	eOutputSpeed_t OSPEEDR8		:2;
	eOutputSpeed_t OSPEEDR9		:2;
	eOutputSpeed_t OSPEEDR10	:2;
	eOutputSpeed_t OSPEEDR11	:2;
	eOutputSpeed_t OSPEEDR12	:2;
	eOutputSpeed_t OSPEEDR13	:2;
	eOutputSpeed_t OSPEEDR14	:2;
	eOutputSpeed_t OSPEEDR15	:2;
 } GPIO_OSPEEDR_t;


 typedef enum {
	NoResistor	= 0b00,
	PullUp		= 0b01,
	PullDown	= 0b10
} ePullResistor_t;

typedef struct {
	// Bits 2y:2y+1 PUPDRy[1:0]: Port x configuration bits (y = 0..15)
	// 00: No pull-up, pull-down
	// 01: Pull-up
	// 10: Pull-down
	ePullResistor_t PUPDR0	:2;
	ePullResistor_t PUPDR1	:2;
	ePullResistor_t PUPDR2	:2;
	ePullResistor_t PUPDR3	:2;
	ePullResistor_t PUPDR4	:2;
	ePullResistor_t PUPDR5	:2;
	ePullResistor_t PUPDR6	:2;
	ePullResistor_t PUPDR7	:2;
	ePullResistor_t PUPDR8	:2;
	ePullResistor_t PUPDR9	:2;
	ePullResistor_t PUPDR10	:2;
	ePullResistor_t PUPDR11	:2;
	ePullResistor_t PUPDR12	:2;
	ePullResistor_t PUPDR13	:2;
	ePullResistor_t PUPDR14	:2;
	ePullResistor_t PUPDR15	:2;
 } GPIO_PUPDR_t;

 typedef struct {
	// Bits 15:0 ODRy: Port output data (y = 0..15)
	uint32_t ODR0		:1;
	uint32_t ODR1		:1;
	uint32_t ODR2		:1;
	uint32_t ODR3		:1;
	uint32_t ODR4		:1;
	uint32_t ODR5		:1;
	uint32_t ODR6		:1;
	uint32_t ODR7		:1;
	uint32_t ODR8		:1;
	uint32_t ODR9		:1;
	uint32_t ODR10		:1;
	uint32_t ODR11		:1;
	uint32_t ODR12		:1;
	uint32_t ODR13		:1;
	uint32_t ODR14		:1;
	uint32_t ODR15		:1;
	uint32_t dcb		:16;
} GPIO_ODR_t;

typedef struct {
	uint32_t BS0		:1;
	uint32_t BS1		:1;
	uint32_t BS2		:1;
	uint32_t BS3		:1;
	uint32_t BS4		:1;
	uint32_t BS5		:1;
	uint32_t BS6		:1;
	uint32_t BS7		:1;
	uint32_t BS8		:1;
	uint32_t BS9		:1;
	uint32_t BS10		:1;
	uint32_t BS11		:1;
	uint32_t BS12		:1;
	uint32_t BS13		:1;
	uint32_t BS14		:1;
	uint32_t BS15		:1;
	uint32_t BR0		:1;
	uint32_t BR1		:1;
	uint32_t BR2		:1;
	uint32_t BR3		:1;
	uint32_t BR4		:1;
	uint32_t BR5		:1;
	uint32_t BR6		:1;
	uint32_t BR7		:1;
	uint32_t BR8		:1;
	uint32_t BR9		:1;
	uint32_t BR10		:1;
	uint32_t BR11		:1;
	uint32_t BR12		:1;
	uint32_t BR13		:1;
	uint32_t BR14		:1;
	uint32_t BR15		:1;
} GPIO_BSRR_t;



/*****************************************************************************
 *		FLASH
 ****************************************************************************/
 typedef enum {
	latency_0 = 0,
	latency_1,
	latency_2,
	latency_3,
	latency_4,
	latency_5,
	latency_6,
	latency_7
} eLatency_t;

typedef struct {
	// Bits 2:0 LATENCY[2:0]: Latency
	eLatency_t LATENCY	:3;
	// Bits 7:3 Reserved, must be kept cleared.
	uint32_t dcb1		:5;
	// Bit 8 PRFTEN: Prefetch enable
	uint32_t PRFTEN		:1;
	// Bit 9 ICEN: Instruction cache enable
	uint32_t ICEN		:1;
	// Bit 10 DCEN: Data cache enable
	uint32_t DCEN		:1;
	// Bit 11 ICRST: Instruction cache reset
	uint32_t ICRST		:1;
	// Bit 12 DCRST: Data cache reset
	uint32_t DCRST		:1;
	// Bits 31:13 Reserved, must be kept cleared.
	uint32_t dcb2		:19;
} FLASH_ACR_t;

/*****************************************************************************
 *		TIM2-5
 ****************************************************************************/
typedef struct {
	// Bit 0 CEN: Counter enable
	uint16_t CEN		:1;
	// Bit 1 UDIS: Update disable
	uint16_t UDIS		:1;
	// Bit 2 URS: Update request source
	uint16_t URS		:1;
	// Bit 3 OPM: One-pulse mode
	uint16_t OPM		:1;
	// Bit 4 DIR: Direction
	// 0: Counter used as upcounter
	// 1: Counter used as downcounter
	uint16_t DIR		:1;
	// Bits 6:5 CMS: Center-aligned mode selection
	uint16_t CMS		:2;
	// Bit 7 ARPE: Auto-reload preload enable
	uint16_t ARPE		:1;
	// Bits 9:8 CKD: Clock division
	// 00: t DTS = t CK_INT
	// 01: t DTS = 2 × t CK_INT
	// 10: t DTS = 4 × t CK_INT
	uint16_t CKD		:2;
	// Bits 15:10 Reserved, must be kept at reset value.
	uint16_t dcb		:6;
} TIM2_5_CR1_t;

typedef struct {
	// Bits 2:0 Reserved, must be kept at reset value.
	uint16_t dcb1		:3;
	// Bit 3 CCDS: Capture/compare DMA selection
	uint16_t CCDS		:1;
	// Bits 6:4 MMS[2:0]: Master mode selection
	uint16_t MMS		:3;
	// Bit 7 TI1S: TI1 selection
	uint16_t TI1S		:1;
	// Bits 15:8 Reserved, must be kept at reset value.
	uint16_t dcb2		:8;
} TIM2_5_CR2_t;

typedef struct {
	// Bit 0 UIE: Update interrupt enable
	uint16_t UIE		:1;
	// Bit 1 CC1IE: Capture/Compare 1 interrupt enable
	uint16_t CC1IE		:1;
	// Bit 2 CC2IE: Capture/Compare 2 interrupt enable
	uint16_t CC2IE		:1;
	// Bit 3 CC2IE: Capture/Compare 3 interrupt enable
	uint16_t CC3IE		:1;
	// Bit 4 CC2IE: Capture/Compare 4 interrupt enable
	uint16_t CC4IE		:1;
	// Bit 5 Reserved, must be kept at reset value.
	uint16_t dcb1		:1;
	// Bit 6 TIE: Trigger interrupt enable
	uint16_t TIE		:1;
	// Bit 7 Reserved, must be kept at reset value.
	uint16_t dcb2		:1;
	// Bit 8 UDE: Update DMA request enable
	uint16_t UDE		:1;
	// Bit 9 CC1DE: Capture/Compare 1 DMA request enable
	uint16_t CC1DE		:1;
	// Bit 10 CC1DE: Capture/Compare 2 DMA request enable
	uint16_t CC2DE		:1;
	// Bit 11 CC1DE: Capture/Compare 3 DMA request enable
	uint16_t CC3DE		:1;
	// Bit 12 CC1DE: Capture/Compare 4 DMA request enable
	uint16_t CC4DE		:1;
	// Bit 13 Reserved, always read as 0.
	uint16_t dcb3		:1;
	// Bit 14 TDE: Trigger DMA request enable
	uint16_t TDE		:1;
	// Bit 15 Reserved, must be kept at reset value.
	uint16_t dcb4		:1;
} TIM2_5_DIER_t;

#endif // STM32F4_BF_H