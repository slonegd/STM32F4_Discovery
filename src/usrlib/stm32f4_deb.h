#include <stdint.h>
#include "../inc/stm32f4xx.h"

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
	uint32_t PLLP   :2;
	// Bits 21:18 Reserved, must be kept at reset value.
	uint32_t dcb1   :4;
	// Bit 22 PLLSRC: Main PLL(PLL) and audio PLL (PLLI2S) entry clock source
	// 0: HSI clock selected as PLL and PLLI2S clock entry
	// 1: HSE oscillator clock selected as PLL and PLLI2S clock entry
	uint32_t PLLSRC :1;
	// Bit 23 Reserved, must be kept at reset value.
	uint32_t dcb2   :1;
	// Bits 27:24 PLLQ: Main PLL (PLL) division factor for USB OTG FS, SDIO and random number generator
	// 2 ≤ PLLQ ≤ 15
	uint32_t PLLQ   :4;
	// Bits 31:28 Reserved, must be kept at reset value.
	uint32_t dcb3   :4;
} RCC_PLLCFGR_t;

typedef struct {
	// Bits 1:0 SW: System clock switch
	// 00: HSI oscillator selected as system clock
	// 01: HSE oscillator selected as system clock
	// 10: PLL selected as system clock
	// 11: not allowed
	uint32_t SW		:2;
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
	uint32_t HPRE	:4;
	// Bits 9:8 Reserved, must be kept at reset value.
	uint32_t dcb1	:1;
	// Bits 12:10 PPRE1: APB Low speed prescaler (APB1)
	// 0xx: AHB clock not divided
	// 100: AHB clock divided by 2
	// 101: AHB clock divided by 4
	// 110: AHB clock divided by 8
	// 111: AHB clock divided by 16
	uint32_t PPRE1	:3;
	// Bits 15:13 PPRE2: APB high-speed prescaler (APB2)
	// like PPRE1
	uint32_t PPRE2	:3;
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



/*****************************************************************************
 *		FLASH
 ****************************************************************************/
typedef struct {
	// Bits 2:0 LATENCY[2:0]: Latency
	uint32_t LATENCY	:3;
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