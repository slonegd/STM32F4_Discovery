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

template<class USART_, uint32_t bufSize>
class USART
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

    void init (Settings& set);
    inline void enableRX () {}
    inline void disableRX () {}
    inline bool endMessage () { return false; }
    inline uint32_t byteQtyRX () { return 0; }
    inline void startTX (uint32_t qty) {}
    inline void stopTX () {}
    inline bool completeTX () { return false; }
};

template<class USART_, uint32_t bufSize>
void USART<USART_,bufSize>::init (USART<USART_,bufSize>::Settings& set)
{

}