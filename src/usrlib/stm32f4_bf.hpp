/**
 * Файл с определениями битовых полей регистров
 * bf - bit fields
 */
#include <stdint.h>
#include "stm32f4xx.h"

#ifndef STM32F4_BF_H
#define STM32F4_BF_H



/*****************************************************************************
 *		FLASH
 ****************************************************************************/
 enum Latency_t {
	latency_0 = 0,
	latency_1,
	latency_2,
	latency_3,
	latency_4,
	latency_5,
	latency_6,
	latency_7
};

typedef struct {
	// Bits 2:0 LATENCY[2:0]: Latency
	Latency_t LATENCY	:3;
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