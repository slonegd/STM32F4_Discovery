#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx.h"

namespace DMA_ral {

    struct CR_t {
        enum DataDirection {
            PerToMem    = 0b00,
            MemToPer    = 0b01,
            MemToMem    = 0b10
        };
        enum DataSize {
            byte8   = 0b00,
            word16  = 0b01,
            dword32 = 0b10
        };
        enum Priority {
            low     = 0b00,
            medium  = 0b01,
            high    = 0b10,
            veryHi  = 0b11
        };
        enum Channels {
            _1 = 0b000,
            _2, _3, _4, _5, _6, _7
        };
        struct Bits {
            // Bit 0 EN: Stream enable / flag stream ready when read low
            volatile bool EN            :1;
            // Bit 1 DMEIE: Direct mode error interrupt enable
            volatile bool DMEIE         :1;
            // Bit 2 TEIE: Transfer error interrupt enable
            volatile bool TEIE          :1;
            // Bit 3 HTIE: Half transfer interrupt enable
            volatile bool HTIE          :1;
            // Bit 4 TCIE: Transfer complete interrupt enable
            volatile bool TCIE          :1;
            // Bit 5 PFCTRL: Peripheral flow controller
            volatile uint32_t PFCTRL    :1;
            // Bits 7:6 DIR[1:0]: Data transfer direction
            volatile DataDirection DIR  :2;
            // Bit 8 CIRC: Circular mode
            volatile bool CIRC          :1;
            // Bit 9 PINC: Peripheral increment mode
            volatile bool PINC          :1;
            // Bit 10 MINC: Memory increment mode
            volatile bool MINC          :1;
            // Bits 12:11 PSIZE[1:0]: Peripheral data size
            volatile DataSize PSIZE     :2;
            // Bits 14:13 MSIZE[1:0]: Memory data size
            volatile DataSize MSIZE     :2;
            // Bit 15 PINCOS: Peripheral increment offset size
            volatile uint32_t PINCOS    :1;
            // Bits 17:16 PL[1:0]: Priority level
            volatile Priority PL        :2;
            // Bit 18 DBM: Double buffer mode
            volatile uint32_t DBM       :1;
            // Bit 19 CT: Current target (only in double buffer mode)
            volatile uint32_t CT        :1;
            // Bits 22:21 PBURST[1:0]: Peripheral burst transfer configuration
            volatile uint32_t PBURST    :2;
            // Bits 24:23 MBURST: Memory burst transfer configuration
            volatile uint32_t MBURST    :2;
            // Bits 27:25 CHSEL[2:0]: Channel selection
            volatile Channels CHSEL     :3;
            // Bits 31:28 Reserved, must be kept at reset value.
            volatile uint32_t dcb1      :4;
        };
        union {
            volatile Bits bits;
            volatile uint32_t reg;
        };
    };

    struct NDTR_t {
        union {
            volatile uint32_t reg;
        };
    };

    struct PAR_t {
        union {
            volatile uint32_t reg;
        };
    };

    struct M0AR_t {
        union {
            volatile uint32_t reg;
        };
    };

    struct M1AR_t {
        union {
            volatile uint32_t reg;
        };
    };

    struct FCR_t {
        union {
            volatile uint32_t reg;
        };
    };
}

/*
typedef struct
{
  __IO uint32_t CR;     // DMA stream x configuration register
  __IO uint32_t NDTR;   // DMA stream x number of data register
  __IO uint32_t PAR;    // DMA stream x peripheral address register
  __IO uint32_t M0AR;   // DMA stream x memory 0 address register
  __IO uint32_t M1AR;   // DMA stream x memory 1 address register
  __IO uint32_t FCR;    // DMA stream x FIFO control register
} DMA_Stream_TypeDef;
*/

struct DMAstream_t : public DMA_ral::CR_t,
                     public DMA_ral::NDTR_t,
                     public DMA_ral::PAR_t,
                     public DMA_ral::M0AR_t,
                     public DMA_ral::M1AR_t,
                     public DMA_ral::FCR_t
{

};

template <uint32_t DMAstreamPtr>
class DMAstream : DMAstream_t
{
protected:
    static volatile DMA_ral::CR_t   &c()   { return (DMA_ral::CR_t &)   (*(DMA_Stream_TypeDef*)DMAstreamPtr).CR;   }
    static volatile DMA_ral::NDTR_t &ndt() { return (DMA_ral::NDTR_t &) (*(DMA_Stream_TypeDef*)DMAstreamPtr).NDTR; }
    static volatile DMA_ral::PAR_t  &pa()  { return (DMA_ral::PAR_t &)  (*(DMA_Stream_TypeDef*)DMAstreamPtr).PAR;  }
    static volatile DMA_ral::M0AR_t &m0a() { return (DMA_ral::M0AR_t &) (*(DMA_Stream_TypeDef*)DMAstreamPtr).M0AR; }
    static volatile DMA_ral::M1AR_t &m1a() { return (DMA_ral::M1AR_t &) (*(DMA_Stream_TypeDef*)DMAstreamPtr).M1AR; }
    static volatile DMA_ral::FCR_t  &fc()  { return (DMA_ral::FCR_t &)  (*(DMA_Stream_TypeDef*)DMAstreamPtr).FCR;  }

public:
    using DataDirection = DMA_ral::CR_t::DataDirection;
    using DataSize = DMA_ral::CR_t::DataSize;
    using Channels = DMA_ral::CR_t::Channels;
    static inline void Enable()  { c().bits.EN = true; }
    static inline void Disable() { c().bits.EN = false; }
    static inline void SetMemoryAdr (uint32_t val) { m0a().reg = val; }
    static inline void SetPeriphAdr (uint32_t val) { pa().reg = val; }
    static inline void SetDirection (DataDirection val) { c().bits.DIR = val; }
    static inline void SetMemoryTransactionSize (DataSize val) { c().bits.MSIZE = val; }
    static inline void SetPeriphTransactionSize (DataSize val) { c().bits.PSIZE = val; }
    static inline void SetMemoryInc (bool b)       { c().bits.MINC = b; }
    static inline void SetPeriphInc (bool b)       { c().bits.PINC = b; }
    static inline void SetCircularMode (bool b)    { c().bits.CIRC = b; }
    static inline void SetChannel (Channels val)   { c().bits.CHSEL = val; }
    static inline void SetQtyTransactions (uint16_t val) { ndt().reg = val; }
    static inline uint16_t QtyTransactionsLeft()   { return ndt().reg; }

};


using DMA1stream0 = DMAstream<DMA1_Stream0_BASE>;
using DMA1stream1 = DMAstream<DMA1_Stream1_BASE>;
using DMA1stream2 = DMAstream<DMA1_Stream2_BASE>;
using DMA1stream3 = DMAstream<DMA1_Stream3_BASE>;
using DMA1stream4 = DMAstream<DMA1_Stream4_BASE>;
using DMA1stream5 = DMAstream<DMA1_Stream5_BASE>;
using DMA1stream6 = DMAstream<DMA1_Stream6_BASE>;
using DMA1stream7 = DMAstream<DMA1_Stream7_BASE>;

using DMA2stream0 = DMAstream<DMA2_Stream0_BASE>;
using DMA2stream1 = DMAstream<DMA2_Stream1_BASE>;
using DMA2stream2 = DMAstream<DMA2_Stream2_BASE>;
using DMA2stream3 = DMAstream<DMA2_Stream3_BASE>;
using DMA2stream4 = DMAstream<DMA2_Stream4_BASE>;
using DMA2stream5 = DMAstream<DMA2_Stream5_BASE>;
using DMA2stream6 = DMAstream<DMA2_Stream6_BASE>;
using DMA2stream7 = DMAstream<DMA2_Stream7_BASE>;