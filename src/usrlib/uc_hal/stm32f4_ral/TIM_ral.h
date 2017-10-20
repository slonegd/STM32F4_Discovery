#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx.h"
#include "GPIO_ral.h"

struct CR1_t {
    struct Bits_t {
        // Bit 0 CEN: Counter enable
        volatile bool CEN        :1;
        // Bit 1 UDIS: Update disable
        volatile uint32_t UDIS   :1;
        // Bit 2 URS: Update request source
        volatile uint32_t URS    :1;
        // Bit 3 OPM: One-pulse mode
        volatile uint32_t OPM    :1;
        // Bit 4 DIR: Direction
        // 0: Counter used as upcounter
        // 1: Counter used as downcounter
        volatile uint32_t DIR    :1;
        // Bits 6:5 CMS: Center-aligned mode selection
        volatile uint32_t CMS    :2;
        // Bit 7 ARPE: Auto-reload preload enable
        volatile bool ARPE       :1;
        // Bits 9:8 CKD: Clock division
        // 00: t DTS = t CK_INT
        // 01: t DTS = 2 × t CK_INT
        // 10: t DTS = 4 × t CK_INT
        volatile uint32_t CKD    :2;
        // Bits 15:10 Reserved, must be kept at reset value.
        volatile uint32_t dcb    :22;
    };
    volatile Bits_t bits;
};

struct CR2_t {
    struct Bits_t {
        // Bits 2:0 Reserved, must be kept at reset value.
        volatile uint32_t dcb1  :3;
        // Bit 3 CCDS: Capture/compare DMA selection
        volatile uint32_t CCDS  :1;
        // Bits 6:4 MMS[2:0]: Master mode selection
        volatile uint32_t MMS   :3;
        // Bit 7 TI1S: TI1 selection
        volatile uint32_t TI1S  :1;
        // Bits 15:8 Reserved, must be kept at reset value.
        volatile uint32_t dcb2  :24;
    };
    volatile Bits_t bits;
};

struct SMCR_t {
    uint32_t reg;
};

struct DIER_t {
    struct Bits_t {
        // Bit 0 UIE: Update interrupt enable
        volatile uint32_t UIE   :1;
        // Bit 1 CC1IE: Capture/Compare 1 interrupt enable
        volatile uint32_t CC1IE :1;
        // Bit 2 CC2IE: Capture/Compare 2 interrupt enable
        volatile uint32_t CC2IE :1;
        // Bit 3 CC2IE: Capture/Compare 3 interrupt enable
        volatile uint32_t CC3IE :1;
        // Bit 4 CC2IE: Capture/Compare 4 interrupt enable
        volatile uint32_t CC4IE :1;
        // Bit 5 Reserved, must be kept at reset value.
        volatile uint32_t dcb1  :1;
        // Bit 6 TIE: Trigger interrupt enable
        volatile uint32_t TIE   :1;
        // Bit 7 Reserved, must be kept at reset value.
        volatile uint32_t dcb2  :1;
        // Bit 8 UDE: Update DMA request enable
        volatile uint32_t UDE   :1;
        // Bit 9 CC1DE: Capture/Compare 1 DMA request enable
        volatile uint32_t CC1DE :1;
        // Bit 10 CC1DE: Capture/Compare 2 DMA request enable
        volatile uint32_t CC2DE :1;
        // Bit 11 CC1DE: Capture/Compare 3 DMA request enable
        volatile uint32_t CC3DE :1;
        // Bit 12 CC1DE: Capture/Compare 4 DMA request enable
        volatile uint32_t CC4DE :1;
        // Bit 13 Reserved, always read as 0.
        volatile uint32_t dcb3  :1;
        // Bit 14 TDE: Trigger DMA request enable
        volatile uint32_t TDE   :1;
        // Bit 15 Reserved, must be kept at reset value.
        volatile uint32_t dcb4  :17;
    };
    volatile Bits_t bits;
};



struct SR_t {
    uint32_t reg;
};

struct EGR_t {
    uint32_t reg;
};

struct CCMR_t {

    enum CompareMode {
        Off             = 0b000,
        ActiveOnMatch   = 0b001,
        InactiveOnMatch = 0b010,
        ToggleOnMatch   = 0b011,
        ForceInactive   = 0b100,
        ForceActive     = 0b101,
        PWMmode         = 0b110,
        InvertedPWMmode = 0b111
    };

    struct Bits_t {
        // Bits 1:0 CC1S: Capture/Compare 1 selection
        volatile uint32_t CC1S      :2;
        // Bit 2 OC1FE: Output compare 1 fast enable
        volatile bool OC1FE         :1;
        // Bit 3 OC1PE: Output compare 1 preload enable
        volatile bool OC1PE         :1;
        // Bits 6:4 OC1M: Output compare 1 mode
        volatile CompareMode OC1M   :3;
        // Bit 7 OC1CE: Output compare 1 clear enable
        volatile bool OC1CE         :1;

        volatile uint32_t CC2S      :2;
        volatile bool OC2FE         :1;
        volatile bool OC2PE         :1;
        volatile CompareMode OC2M   :3;
        volatile bool OC2CE         :1;

        uint32_t dcb1               :16;

        volatile uint32_t CC3S      :2;
        volatile bool OC3FE         :1;
        volatile bool OC3PE         :1;
        volatile CompareMode OC3M   :3;
        volatile bool OC3CE         :1;
        volatile uint32_t CC4S      :2;
        volatile bool OC4FE         :1;
        volatile bool OC4PE         :1;
        volatile CompareMode OC4M   :3;
        volatile bool OC4CE         :1;

        uint32_t dcb2               :16;
    };
    union {
        volatile Bits_t bits;
        volatile uint32_t regs[2];   
    };
};
struct CCER_t {
    struct Bits {
        // Bit 0 CC1E: Capture/Compare 1 output enable.
        volatile bool CC1E      :1;
        // Bit 1 CC1P: Capture/Compare 1 output Polarity.
        volatile uint32_t CC1P  :1;
        // Bit 2 Reserved, must be kept at reset value.
        volatile uint32_t dcb1  :1;
        // Bit 3 CC1NP: Capture/Compare 1 output Polarity.
        volatile uint32_t CC1NP :1;

        volatile bool CC2E      :1;
        volatile uint32_t CC2P  :1;
        volatile uint32_t dcb2  :1;
        volatile uint32_t CC2NP :1;
        volatile bool CC3E      :1;
        volatile uint32_t CC3P  :1;
        volatile uint32_t dcb3  :1;
        volatile uint32_t CC3NP :1;
        volatile bool CC4E      :1;
        volatile uint32_t CC4P  :1;
        volatile uint32_t dcb4  :1;
        volatile uint32_t CC4NP :1;
        volatile uint32_t dcb5  :16;
    };
    union {
        Bits bits;
        uint16_t reg;
    };
};

struct CNT_t {
    uint32_t reg;
};

struct PSC_t {
    uint32_t reg;
};

struct ARR_t {
    uint32_t reg;
};

struct RCR_t {
    uint32_t reg;
};

struct CCR_t {
    uint32_t regs[4];
};


/*
typedef struct
{
  __IO uint32_t CR1;         // TIM control register 1,              Address offset: 0x00
  __IO uint32_t CR2;         // TIM control register 2,              Address offset: 0x04
  __IO uint32_t SMCR;        // TIM slave mode control register,     Address offset: 0x08
  __IO uint32_t DIER;        // TIM DMA/interrupt enable register,   Address offset: 0x0C
  __IO uint32_t SR;          // TIM status register,                 Address offset: 0x10
  __IO uint32_t EGR;         // TIM event generation register,       Address offset: 0x14
  __IO uint32_t CCMR1;       // TIM capture/compare mode register 1, Address offset: 0x18
  __IO uint32_t CCMR2;       // TIM capture/compare mode register 2, Address offset: 0x1C
  __IO uint32_t CCER;        // TIM capture/compare enable register, Address offset: 0x20
  __IO uint32_t CNT;         // TIM counter register,                Address offset: 0x24
  __IO uint32_t PSC;         // TIM prescaler,                       Address offset: 0x28
  __IO uint32_t ARR;         // TIM auto-reload register,            Address offset: 0x2C
  __IO uint32_t RCR;         // TIM repetition counter register,     Address offset: 0x30
  __IO uint32_t CCR1;        // TIM capture/compare register 1,      Address offset: 0x34
  __IO uint32_t CCR2;        // TIM capture/compare register 2,      Address offset: 0x38
  __IO uint32_t CCR3;        // TIM capture/compare register 3,      Address offset: 0x3C
  __IO uint32_t CCR4;        // TIM capture/compare register 4,      Address offset: 0x40
  __IO uint32_t BDTR;        // TIM break and dead-time register,    Address offset: 0x44
  __IO uint32_t DCR;         // TIM DMA control register,            Address offset: 0x48
  __IO uint32_t DMAR;        // TIM DMA address for full transfer,   Address offset: 0x4C
  __IO uint32_t OR;          // TIM option register,                 Address offset: 0x50
} TIM_TypeDef;
*/

struct TIM_t : public CR1_t,
               public CR2_t,
               public SMCR_t,
               public DIER_t,
               public SR_t,
               public EGR_t,
               public CCMR_t,
               public CCER_t,
               public CNT_t,
               public PSC_t,
               public ARR_t,
               public RCR_t,
               public CCR_t
{

};
// ClkEnOffset оффсет для регистра из структуры RCC, разрешающий тактирование 
template <uint32_t TIMptr, uint32_t ClkEnOffset, uint32_t ClkEnMask, AFR_t::AF af>
class TIM : TIM_t
{
public:
    using CompareMode = TIM_t::CCMR_t::CompareMode;
    static const AFR_t::AF AltFunc = af;
protected:
    static volatile CR1_t &c1()     { return (CR1_t &)    (*(TIM_TypeDef*)TIMptr).CR1; }
    static volatile CR2_t &c2()     { return (CR2_t &)    (*(TIM_TypeDef*)TIMptr).CR2; }
    static volatile CCMR_t &ccm()   { return (CCMR_t &)   (*(TIM_TypeDef*)TIMptr).CCMR1; }
    static volatile CCER_t &cce()   { return (CCER_t &)   (*(TIM_TypeDef*)TIMptr).CCER; }
    static volatile uint32_t &ar()  { return (uint32_t &) (*(TIM_TypeDef*)TIMptr).ARR; }
    static volatile CCR_t &cc()     { return (CCR_t &)    (*(TIM_TypeDef*)TIMptr).CCR1; }

public:
    // включает тактирование таймера
    static inline void ClockEnable() { *((uint32_t*)(RCC_BASE + ClkEnOffset)) |= ClkEnMask; }
    static inline void CounterEnable()    { c1().bits.CEN = true; }
    static inline bool IsCount()          { return c1().bits.CEN; }
    static inline void CounterDisable()   { c1().bits.CEN = false; }
    static inline void AutoReloadEnable() { c1().bits.ARPE = true; }
    template <CompareMode cm, uint8_t channel>
    static inline void  SetCompareMode ()
    {
        // 0 для каналов 1,2; 1 для каналов 3,4
        constexpr uint8_t regN = channel / 3;
        // 4 для каналов 1,3; 12 для каналов 2,4   
        constexpr uint8_t offset = 4 + 8 * (channel / (regN*2 + 2));
        constexpr uint32_t ClearMask = (uint32_t) 0b111 << offset;
        constexpr uint32_t SetMask = (uint32_t) cm << offset;
        MODIFY_REG (ccm().regs[regN], ClearMask, SetMask);
    }
    template <uint8_t channel>
    static inline void CompareEnable ()
    {
        cce().reg |= (uint16_t)1 << (channel-1)*4;
    }
    template <uint8_t channel>
    static inline void CompareDisable ()
    {
        cce().reg &= ~( (uint16_t)1 << (channel-1)*4 );
    }
    template <uint8_t channel>
    static inline bool IsCompareEnable ()
    {
        return ( (cce().reg & ((uint16_t)1 << (channel-1)*4)) != 0);
    }

    static inline void SetAutoReloadValue (uint32_t val) { ar() = val; }
    template <uint8_t channel>
    static inline void SetCompareValue (uint32_t val) { cc().regs[channel-1] = val; }
};

using TIM1_t = TIM<TIM1_BASE, 0x44, RCC_APB2ENR_TIM1EN_Msk, AFR_t::AF::AF1>;
using TIM2_t = TIM<TIM2_BASE, 0x40, RCC_APB1ENR_TIM2EN_Msk, AFR_t::AF::AF1>;
using TIM3_t = TIM<TIM3_BASE, 0x40, RCC_APB1ENR_TIM3EN_Msk, AFR_t::AF::AF2>;
using TIM4_t = TIM<TIM4_BASE, 0x40, RCC_APB1ENR_TIM4EN_Msk, AFR_t::AF::AF2>;


