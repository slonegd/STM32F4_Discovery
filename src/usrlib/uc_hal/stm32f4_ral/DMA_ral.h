#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx.h"

namespace DMA_ral {

    struct CR_t {
        union {
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
    static volatile DMA_ral::PAR_t  &pat() { return (DMA_ral::PAR_t &)  (*(DMA_Stream_TypeDef*)DMAstreamPtr).PAR;  }
    static volatile DMA_ral::M0AR_t &m0a() { return (DMA_ral::M0AR_t &) (*(DMA_Stream_TypeDef*)DMAstreamPtr).M0AR; }
    static volatile DMA_ral::M1AR_t &m1a() { return (DMA_ral::M1AR_t &) (*(DMA_Stream_TypeDef*)DMAstreamPtr).M1AR; }
    static volatile DMA_ral::FCR_t  &fc()  { return (DMA_ral::FCR_t &)  (*(DMA_Stream_TypeDef*)DMAstreamPtr).FCR;  }

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