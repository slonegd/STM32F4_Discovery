//////////////////////////////////////////////////////////////////////////////
/** реализую методы
 *      инициализации, поскольку в конструкторе как правило еще
 *  не известно какие настройки подключения
 *      слышать
 *      определять конец пакета
 *      определять сколько пришло
 *      отправлять сколько надо
 *      говорить, что отправка произошла
 *////////////////////////////////////////////////////////////////////////////
#pragma once

#include "USART_ral.h"

template <class USART_> static const DMA_ral::CR_t::Channels DMArxChannel();
template <class USART_> static const DMA_ral::CR_t::Channels DMAtxChannel();

template<class USART_, uint32_t bufSize, class RX, class TX, class RTS>
class USART : USART_
{
public:
    volatile uint8_t Buffer[bufSize];
    using Boudrate = typename USART_::Boudrate;
    enum ParityEn {
        disable,
        enable
    };
    using Parity = typename USART_::Parity;
    using StopBits = typename USART_::StopBits;
    struct Settings {
        Boudrate boudrate;
        ParityEn parityEn;
        Parity parity;
        StopBits stopBits;
    };
    using DMArx = typename USART_::DMArx;
    using DMAtx = typename USART_::DMAtx;

    inline void init (Settings set)
    {
        USART_::ClockEnable();
        USART_::SetBoudRate (set.boudrate);
        if (set.parityEn == ParityEn::enable) {
            USART_::ParityEnable();
            USART_::SetParity(set.parity);
        } else {
            USART_::ParityDisable();
        }
        USART_::SetStopBits (set.stopBits);
        USART_::RXenable();
        USART_::TXenable();
        USART_::DMArxEnable();
        USART_::DMAtxEnable();
        USART_::Enable();

        DMArx::SetMemoryAdr ( (uint32_t) this );
        DMArx::SetPeriphAdr ( (uint32_t) &( USART_::d() ) );
        DMArx::SetDirection (DMArx::DataDirection::PerToMem);
        DMArx::SetMemoryTransactionSize (DMArx::DataSize::byte8);
        DMArx::SetPeriphTransactionSize (DMArx::DataSize::byte8);
        DMArx::SetMemoryInc (true);
        DMArx::SetPeriphInc (false);
        DMArx::SetCircularMode (true);
        DMArx::SetChannel ( DMArxChannel<USART_>() );
        enableRX();

        DMAtx::SetMemoryAdr ( (uint32_t) this );
        DMAtx::SetPeriphAdr ( (uint32_t) &( USART_::d() ) );
        DMAtx::SetDirection (DMAtx::DataDirection::MemToPer);
        DMAtx::SetMemoryTransactionSize (DMAtx::DataSize::byte8);
        DMAtx::SetPeriphTransactionSize (DMAtx::DataSize::byte8);
        DMAtx::SetMemoryInc (true);
        DMAtx::SetPeriphInc (false);
        DMAtx::SetCircularMode (true);
        DMArx::SetChannel ( DMAtxChannel<USART_>() );

    }
    inline void enableRX ()
    {
        DMArx::SetQtyTransactions (bufSize);
        DMArx::Enable(); 
    }
    inline void disableRX()      { DMArx::Disable(); }
    inline bool rxComplete ()  { return frxComplete; }
    inline uint32_t byteQtyRX () { return bufSize - DMArx::QtyTransactionsLeft(); }
    inline void startTX (uint32_t qty)
    {
        DMAtx::SetQtyTransactions (qty);
        DMAtx::Enable();
    }
    inline void stopTX () { DMAtx::Disnable(); }
    inline bool isCompleteTX ()  { return false; }
private:
    bool frxComplete;
};



//////////////////////////////////////////////////////////////////////////////
// конкретизация 
//////////////////////////////////////////////////////////////////////////////
template <> const DMA_ral::CR_t::Channels DMArxChannel<USART1_t>() { return DMA_ral::CR_t::Channels::_4; };
template <> const DMA_ral::CR_t::Channels DMAtxChannel<USART1_t>() { return DMA_ral::CR_t::Channels::_4; };