#include "../inc/stm32f4xx.h"
#include <stdint.h>

#ifndef STM32F4_REGCLASSES_HPP
#define STM32F4_REGCLASSES_HPP

class RCC_PLLCFGR {
public:
    enum PLLPdiv {
        div2 = 0b00,
        div4 = 0b01,
        div6 = 0b10,
        div8 = 0b11
    };
    enum PLLsource {
        HSI = 0b0,
        HSE = 0b1          
    };
    struct Bits {
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
        PLLPdiv PLLP   :2;
        // Bits 21:18 Reserved, must be kept at reset value.
        uint32_t dcb1   :4;
        // Bit 22 PLLSRC: Main PLL(PLL) and audio PLL (PLLI2S) entry clock source
        // 0: HSI clock selected as PLL and PLLI2S clock entry
        // 1: HSE oscillator clock selected as PLL and PLLI2S clock entry
        PLLsource PLLSRC :1;
        // Bit 23 Reserved, must be kept at reset value.
        uint32_t dcb2   :1;
        // Bits 27:24 PLLQ: Main PLL (PLL) division factor for USB OTG FS, SDIO and random number generator
        // 2 ≤ PLLQ ≤ 15
        uint32_t PLLQ   :4;
        // Bits 31:28 Reserved, must be kept at reset value.
        uint32_t dcb3   :4;           
    };
    Bits & bits = *(Bits*)ADR;
private:
    enum {
        ADR = RCC_BASE + 0x04
    };
    static inline volatile Bits &Reg() { return (Bits &)RCC->PLLCFGR; }
public:
    inline static void SetPLLP (PLLPdiv div)
    {
        Reg().PLLP = div;
    }
    inline void rSetPLLP (PLLPdiv div)
    {
        bits.PLLP = div;
    }
};
/*
struct RCC_ : public RCC_PLLCFGR {

    struct Regs {
        RCC_PLLCFGR PLLCFGR;
    };
*/
};

#endif // STM32F4_REGCLASSES_HPP