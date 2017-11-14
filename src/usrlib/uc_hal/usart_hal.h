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
#include "constDef.h"

namespace USART_HAL {

}


template<class USART_, uint32_t bufSize, class RX, class TX, class RTS, class LED>
class USART : USART_
{
public:
    volatile uint8_t Buffer[bufSize];

    using Boudrate = typename USART_::Boudrate;
    enum ParityEn { disable, enable };
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

    void init (Settings set);
    inline void enableRX ()
    {
        DMArx::SetQtyTransactions (bufSize);
        DMArx::Enable(); 
    }
    inline void disableRx()     { DMArx::Disable(); }
    inline uint32_t byteQtyRX() { return bufSize - DMArx::QtyTransactionsLeft(); }
    inline void startTX (uint32_t qty)
    {
        DMAtx::SetQtyTransactions (qty);
        DMAtx::Enable();
        LED::Set();
    }
    inline void stopTX() { DMAtx::Disable(); }
    inline bool isCompleteTX()  { return false; }
    // обработчики прерываний
    // возвращает true если источник прерывания наш
    // тут возможно надо будет дораьотать, потому что
    // метод сбрасывает все флаги прерывания,
    // но в этом приложении пофиг
    inline bool idleHandler()
    {
        bool tmp = USART_::IDLEinterrupt();
        if (tmp) {
           disableRx();
           USART_::ClearIDLEinterruptFlag();
        }
        return tmp;
    }
    inline void txCompleteHandler()
    {
        if ( DMAtx::TransferCompleteInterrupt() ) {
            stopTX();
            LED::Clear();
            enableRX();
        }
    }
private:

};

template <class USART_, uint32_t bufSize, class RX, class TX, class RTS, class LED>
void USART<USART_, bufSize, RX, TX, RTS, LED>::init (Settings set)
{
    // пины
    RX::Port::ClockEnable();
    RX::Configure (
        RX::Mode::AlternateMode,
        RX::OutType::PushPull,
        RX::OutSpeed::High,
        RX::PullResistor::No
    );
    RX::template SetAltFunc <PA1::AF::AF7> ();

    TX::Port::ClockEnable();
    TX::Configure (
        TX::Mode::AlternateMode,
        TX::OutType::PushPull,
        TX::OutSpeed::High,
        TX::PullResistor::No
    );
    TX::template SetAltFunc <PA1::AF::AF7> ();

    RTS::Port::ClockEnable();
    RTS::Configure (
        RTS::Mode::AlternateMode,
        RTS::OutType::PushPull,
        RTS::OutSpeed::High,
        RTS::PullResistor::No
    );
    RTS::template SetAltFunc <PA1::AF::AF7> ();

    LED::Port::ClockEnable();
    LED::Configure (
        LED::Mode::OutputMode,
        LED::OutType::PushPull,
        LED::OutSpeed::Low,
        LED::PullResistor::No
    );
    LED::template SetAltFunc <PA1::AF::AF0> ();

    // уарт
    USART_::ClockEnable();
    USART_::SetBoudRate (set.boudrate);
    if (set.parityEn == ParityEn::enable) {
        USART_::ParityEnable (true);
        USART_::SetParity(set.parity);
    } else {
        USART_::ParityEnable (false);
    }
    USART_::SetStopBits (set.stopBits);
//    USART1->CR1 |= USART_CR1_RE_Msk;
//    USART1->CR1 |= USART_CR1_TE_Msk;
    USART_::RXenable (true);
    USART_::TXenable (true);
    USART_::DMArxEnable();
    USART_::DMAtxEnable();
//    USART1->CR1 |= USART_CR1_UE_Msk;
    USART_::Enable (true);

/*    // дма
    DMArx::ClockEnable();
    DMArx::SetMemoryAdr ( (uint32_t) this );
    DMArx::SetPeriphAdr ( (uint32_t) &(USART_::data()) );
    DMArx::SetDirection (DMArx::DataDirection::PerToMem);
    DMArx::SetMemoryTransactionSize (DMArx::DataSize::byte8);
    DMArx::SetPeriphTransactionSize (DMArx::DataSize::byte8);
    DMArx::SetMemoryInc (true);
    DMArx::SetPeriphInc (false);
    DMArx::SetCircularMode (true);
    DMArx::SetChannel (USART_::DMAChannel);
    enableRX();

    DMAtx::SetMemoryAdr ( (uint32_t) this );
    DMAtx::SetPeriphAdr ( (uint32_t) &(USART_::data()) );
    DMAtx::SetDirection (DMAtx::DataDirection::MemToPer);
    DMAtx::SetMemoryTransactionSize (DMAtx::DataSize::byte8);
    DMAtx::SetPeriphTransactionSize (DMAtx::DataSize::byte8);
    DMAtx::SetMemoryInc (true);
    DMAtx::SetPeriphInc (false);
    DMAtx::SetCircularMode (false);
    DMAtx::SetChannel (USART_::DMAChannel);

    // прерывания
    USART_::EnableIDLEinterrupt();
    NVIC_EnableIRQ(USART_::IRQn);
    DMAtx::EnableTransferCompleteInterrupt();
    NVIC_EnableIRQ(DMAtx::IRQn);*/
}


