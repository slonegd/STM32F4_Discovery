//////////////////////////////////////////////////////////////////////////////
/** первые 2 параметры шаблона -кслассы перечисления от 0, без пропусков
 *  последним членом перечилсения должны быть Qty
 * 
 *      ПОПРОБАВАТЬ ВМЕСТО ПЕРЕЧИСЛЕНИЙ ИСПОЛЬЗОВАТЬ СТРУКТУРЫ
 *      А ВМЕСТО СВИТЧ/КЕЙС СПЕЦИАЛИЗАЦИИ ШАБЛОННЫХ ФУНКЦИЙ,
 *      КОТОРОЙ ПЕРЕДАЁТЬСЯ АДРЕСС
 * с шаблонной функцией не получиться, но со структурами работать удобнее
 * просто в кейсе надо не енум ставить а адрес, который вычисляеться макросом
 * не придумал как макрос на шаблон изменить
 *//////////////////////////////////////////////////////////////////////////// 
#pragma once

#include "usart_hal.h"

template <class InRegs_, class OutRegs_, class UART_>
class MBslave
{
public:
    static const uint16_t InRegQty  = static_cast<uint16_t>(InRegs_::Qty);
    static const uint16_t OutRegQty = static_cast<uint16_t>(OutRegs_::Qty);

    uint16_t inReg[InRegQty];
    uint16_t outReg[OutRegQty];
    uint16_t inRegMin[InRegQty];
    uint16_t inRegMax[InRegQty];

    UART_& uart;


    MBslave(UART_& usart) : inReg{0}, outReg{0}, inRegMin{0}, inRegMax{0}, uart(usart), nInRegAction(InRegQty)
    { }


    // обрабатывает поступивший запрос, по необходимости формирует ответ
    // переводит уарт на отправку или приём, если ответа не надо
    inline void handler()
    {

    }


    // перебирает все входные регистров, на которые пришел запрос
    // внутри функции вызывать метод getInRegForAction для определения регистра
    template <class function>
    inline function foreachRegInActions (function f) 
    {
        for (; nInRegAction > nLastRegAction; nInRegAction++ ) {
            f();
        }
        return f;
    }


    inline InRegs_ getInRegForAction() { return inRegAction; }
     
private:
    union {
        InRegs_  inRegAction;
        uint16_t nInRegAction;
    };
    uint16_t nLastRegAction;
};


template <class InRegs_>
class stMBslave
{
public:
    using InRegStructure = InRegs_;
    static const uint16_t InRegQty = sizeof(InRegs_) / 2;
    constexpr uint16_t adr (uint16_t& reg) { return offsetof(InRegs_, reg)/2; }
    union {
        InRegs_ inRegs;
        uint16_t arInRegs[InRegQty];
    };

    // перебирает все входные регистров, на которые пришел запрос
    // внутри функции вызывать метод getInRegForAction для определения регистра
    template <class function>
    inline function foreachRegInActions (function f) 
    {
        // временно не верно
        for (i = 0; i < InRegQty; i++ ) {
            f();
        }
        return f;
    }

    uint16_t i;
    
};

template<uint16_t RegAdr>
inline void mbRegInActionst()
{ }

#define GET_ADR(struct ,reg)     (offsetof(struct, reg) / 2)