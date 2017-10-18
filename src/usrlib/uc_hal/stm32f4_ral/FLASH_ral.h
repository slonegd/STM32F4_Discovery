/**
 * RAL над регистрами FLASH
 */

#pragma once

#include <stdint.h>
#include "stm32f4xx.h"

struct ACR_t {
    enum Latency {
        latency_0 = 0,
        latency_1,
        latency_2,
        latency_3,
        latency_4,
        latency_5,
        latency_6,
        latency_7
    };
    struct Bits_t {
        // Bits 2:0 LATENCY[2:0]: Latency
        volatile Latency LATENCY  :3;
        // Bits 7:3 Reserved, must be kept cleared.
        volatile uint32_t dcb1      :5;
        // Bit 8 PRFTEN: Prefetch enable
        volatile uint32_t PRFTEN    :1;
        // Bit 9 ICEN: Instruction cache enable
        volatile uint32_t ICEN      :1;
        // Bit 10 DCEN: Data cache enable
        volatile uint32_t DCEN      :1;
        // Bit 11 ICRST: Instruction cache reset
        volatile uint32_t ICRST     :1;
        // Bit 12 DCRST: Data cache reset
        volatile uint32_t DCRST     :1;
        // Bits 31:13 Reserved, must be kept cleared.
        volatile uint32_t dcb2      :19;
    };
    volatile Bits_t bits;
};
/*
typedef struct
{
  __IO uint32_t ACR;      // FLASH access control register,   Address offset: 0x00 
  __IO uint32_t KEYR;     // FLASH key register,              Address offset: 0x04 
  __IO uint32_t OPTKEYR;  // FLASH option key register,       Address offset: 0x08 
  __IO uint32_t SR;       // FLASH status register,           Address offset: 0x0C 
  __IO uint32_t CR;       // FLASH control register,          Address offset: 0x10 
  __IO uint32_t OPTCR;    // FLASH option control register ,  Address offset: 0x14 
  __IO uint32_t OPTCR1;   // FLASH option control register 1, Address offset: 0x18 
} FLASH_TypeDef;
*/

class FLASH_t : public ACR_t
// остальные регистры пока не нужны
{
public:
    using Latency = ACR_t::Latency;

    static volatile ACR_t &ac() { return (ACR_t &) FLASH->ACR; }

    static inline void SetLatency (Latency L) { ac().bits.LATENCY = L; }
};