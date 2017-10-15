/**
 * Вся эта муть - переосмысление библиотеки
 * https://github.com/KonstantinChizhov/Mcucpp
 *
 */

#pragma once

#include "loki/Typelist.h"
#include <stdint.h>

//using namespace Loki;
using NullType = Loki::NullType;

////////////////////////////////////////////////////////////////////////////////
// структура чтобы сохранить позицию в pinlist \/
////////////////////////////////////////////////////////////////////////////////
template<class TPIN, uint8_t p>
struct PinPositionHolder
{
	typedef TPIN Pin;
	enum { Position = p };
};

////////////////////////////////////////////////////////////////////////////////
// создаёт список типов с сохранённой позицией типа в списке \/
////////////////////////////////////////////////////////////////////////////////
template
<
    int Position,
    typename T1  = NullType, typename T2  = NullType, typename T3  = NullType,
    typename T4  = NullType, typename T5  = NullType, typename T6  = NullType,
    typename T7  = NullType, typename T8  = NullType, typename T9  = NullType,
    typename T10 = NullType, typename T11 = NullType, typename T12 = NullType,
    typename T13 = NullType, typename T14 = NullType, typename T15 = NullType,
    typename T16 = NullType, typename T17 = NullType, typename T18 = NullType,
    typename T19 = NullType, typename T20 = NullType, typename T21 = NullType,
    typename T22 = NullType, typename T23 = NullType, typename T24 = NullType,
    typename T25 = NullType, typename T26 = NullType, typename T27 = NullType,
    typename T28 = NullType, typename T29 = NullType, typename T30 = NullType,
    typename T31 = NullType, typename T32 = NullType, typename T33 = NullType
>
struct MakePinList
{
private:
    using TailResult = typename MakePinList < Position + 1,
        T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10, T11, T12, T13, T14, T15,
        T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
        T30, T31, T32, T33
    >::Result;
    enum { PositionInList = Position };
public:
    using Result = Loki::Typelist< PinPositionHolder<T1, PositionInList>, TailResult>;
};

template<int Position>
struct MakePinList<Position>
{
    using Result = NullType;
};

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
template<class PINS>
struct PinSet
{

};

////////////////////////////////////////////////////////////////////////////////
// преобразует список пинов в список портов этих пинов \/
////////////////////////////////////////////////////////////////////////////////
template <class TList> struct GetPorts;
        // пустая специализация
		template <> struct GetPorts<NullType>
		{
			using Result = NullType;
		};

		template <class Head, class Tail>
		struct GetPorts< Loki::Typelist<Head, Tail> >
		{
		private:
			using Port = typename Head::Pin::Port;
			using L1 = typename GetPorts<Tail>::Result;
		public:
			using Result = Loki::Typelist<Port, L1>;
        };


////////////////////////////////////////////////////////////////////////////////
// определяет принадлежит ли пин порту \/ только пока не ясно где это используеться
////////////////////////////////////////////////////////////////////////////////
template<class Port>
struct IsPinInPort
{
    template<class Item>
    struct Result
    {
        static const bool value = Loki::IsSameType<Port, typename Item::Pin::Port>::value;
    };
};
////////////////////////////////////////////////////////////////////////////////
// определяет битовую маску для порта - не ясно, видимо тут TList должен быть особый
////////////////////////////////////////////////////////////////////////////////
template <class TList> struct GetPortMask;
// Для пустого списка возвращаем 0.
template <> struct GetPortMask<NullType>
{
    enum { value = 0 };
};
 
template <class Head, class Tail>
struct GetPortMask< Loki::Typelist<Head, Tail> >
{	
    //value =	битовая маска для головы  | битовая маска оставшейся части списка
    enum {
        value = (1 << Head::Pin::Number) | GetPortMask<Tail>::value
    };
};

////////////////////////////////////////////////////////////////////////////////
// class template SelectPins
// Assume that TList is type list of PinPositionHolder types.
////////////////////////////////////////////////////////////////////////////////
template <class TList, template <class> class Predicate>
struct SelectPins;

template <template <class> class Predicate>
struct SelectPins<NullType, Predicate>
{
    typedef NullType Result;
};

template <class Head, class Tail, template <class> class Predicate>
class SelectPins<Loki::Typelist<Head, Tail>, Predicate>
{
     typedef typename SelectPins<Tail, Predicate>::Result NotMatch;
     typedef Loki::Typelist<Head,
            typename SelectPins<Tail, Predicate>::Result>
        Match;
     static const bool IsMatch = Predicate<Head>::value;
public:
     typedef typename Loki::Select<IsMatch,
        Match,
        NotMatch>::Result Result;
};

        
////////////////////////////////////////////////////////////////////////////////
// для определения свойств пинлиста \/
////////////////////////////////////////////////////////////////////////////////
template<class PINS>
class PinListProperties
{
private:
    typedef typename GetPorts<PINS>::Result PinsToPorts;
public:
    static const unsigned Length = Loki::TL::Length<PINS>::value;
    typedef typename Loki::TL::NoDuplicates<PinsToPorts>::Result Ports;
    typedef PINS PinTypeList;

//    enum{LastBitPositionEnum = IoPrivate::GetLastBitPosition<PINS>::value};
//    typedef typename IoPrivate::GetConfigPins<PINS>::Result ConfigPins;
//    typedef typename IoPrivate::GetPorts<ConfigPins>::Result PinsToConfigPorts;
//    typedef typename Loki::TL::NoDuplicates<PinsToConfigPorts>::Result ConfigPorts;
/*    static const unsigned LastBitPosition = LastBitPositionEnum;

    enum {PortsHasSameConfig =
        IoPrivate::CheckSameConfig<ConfigPorts>::value};

        typedef typename SelectSize<LastBitPosition+1>::Result DataType;
*/
};

////////////////////////////////////////////////////////////////////////////////
// class template PortWriteIterator
// Iterates througth port list and write value to them
// Assume that PinList is type list of PinPositionHolder types.
// And PortList is type list of port types.
////////////////////////////////////////////////////////////////////////////////

template <class PortList, class PinList, class ValueType> struct PortWriteIterator;

    // пустая специализация
    template <class PinList, class ValueType> struct PortWriteIterator<NullType, PinList, ValueType>
    {
        typedef ValueType DataType;
        static void Write(DataType) { }
        static void Set(DataType)   { }
        static void Clear(DataType) { }
        static DataType PinRead()   { return 0; }
        static DataType OutRead()   { return 0; }

        template<DataType value> static void Write()    { }
        template<DataType value> static void Set()      { }
        template<DataType value> static void Clear()    { }
    };

    template <class Head, class Tail, class PinList, class ValueType>
    struct PortWriteIterator< Loki::Typelist<Head, Tail>, PinList, ValueType>
    {
        //pins on current port
        typedef typename SelectPins<PinList, IsPinInPort<Head>::template Result>::Result Pins;

/*        enum{Mask = GetPortMask<Pins>::value};

        typedef Head Port; //Head points to current port in the list.
        typedef typename Port::DataT PortType;

        typedef typename StaticIf
                <
                    sizeof(PortType) >= sizeof(ValueType),
                    PortType,
                    ValueType
                    >::Result DataType;

        static void Enable()
        {
            Port::Enable();
            PortWriteIterator<Tail, PinList, ValueType>::Enable();
        }
        
        static void Write(DataType value)
        {
            DataType result = PinWriteIterator<Pins>::AppendValue(value, DataType(0));

            if((int)Length<Pins>::value == (int)Port::Width)// whole port
                Port::Write(result);
            else
            {
                Port::ClearAndSet(Mask, result);
            }

            PortWriteIterator<Tail, PinList, ValueType>::Write(value);
        }

        static void Set(DataType value)
        {
            DataType result = PinWriteIterator<Pins>::AppendValue(value, DataType(0));
            Port::Set(result);
            PortWriteIterator<Tail, PinList, ValueType>::Set(value);
        }

        static void Clear(DataType value)
        {
            DataType result = PinWriteIterator<Pins>::AppendValue(value, DataType(0));
            Port::Clear(result);
            PortWriteIterator<Tail, PinList, ValueType>::Clear(value);
        }

        template<class Configuration>
        static void SetConfiguration(Configuration config, DataType mask)
        {
            DataType portMask = PinWriteIterator<Pins>::AppendValue(mask, DataType(0));
            Port::SetConfiguration(portMask, config);
            PortWriteIterator<Tail, PinList, ValueType>::SetConfiguration(config, mask);
        }
        
        template<class Speed>
        static void SetSpeed(Speed speed, DataType mask)
        {
            DataType portMask = PinWriteIterator<Pins>::AppendValue(mask, DataType(0));
            Port::SetSpeed(portMask, speed);
            PortWriteIterator<Tail, PinList, ValueType>::SetSpeed(speed, mask);
        }
        
        template<class PullUp>
        static void SetPullUp(PullUp pull, DataType mask)
        {
            DataType portMask = PinWriteIterator<Pins>::AppendValue(mask, DataType(0));
            Port::SetPullUp(portMask, pull);
            PortWriteIterator<Tail, PinList, ValueType>::SetPullUp(pull, mask);
        }
        
        template<class DriverType>
        static void SetDriverType(DriverType driver, DataType mask)
        {
            DataType portMask = PinWriteIterator<Pins>::AppendValue(mask, DataType(0));
            Port::SetDriverType(portMask, driver);
            PortWriteIterator<Tail, PinList, ValueType>::SetDriverType(driver, mask);
        }

        static void AltFuncNumber(uint8_t number, DataType mask)
        {
            DataType portMask = PinWriteIterator<Pins>::AppendValue(mask, DataType(0));
            Port::AltFuncNumber(portMask, number);
            PortWriteIterator<Tail, PinList, ValueType>::AltFuncNumber(number, mask);
        }

        static DataType PinRead()
        {
            DataType portValue = Port::PinRead();
            return PinWriteIterator<Pins>::template AppendReadValue<DataType>(
                        portValue,
                        PortWriteIterator<Tail, PinList, ValueType>::PinRead());
        }

        static DataType OutRead()
        {
            DataType portValue = Port::Read();
            return PinWriteIterator<Pins>::template AppendReadValue<DataType>(
                        portValue,
                        PortWriteIterator<Tail, PinList, ValueType>::OutRead());
        }

        // constant writing interface

        template<DataType value>
        static void Write()
        {
            const DataType portValue =
                PinConstWriteIterator<Pins, DataType, value>::PortValue ^
                GetInversionMask<Pins>::value;

            Port::template ClearAndSet<Mask, portValue>();
            PortWriteIterator<Tail, PinList, ValueType>::template Write<value>();
        }

        template<DataType value>
        static void Set()
        {
            const DataType portValue =
                PinConstWriteIterator<Pins, DataType, value>::PortValue ^
                GetInversionMask<Pins>::value;

            Port::template Set<portValue>();
            PortWriteIterator<Tail, PinList, ValueType>::template Set<value>();
        }

        template<DataType value>
        static void Clear()
        {
            const DataType portValue =
                PinConstWriteIterator<Pins, DataType, value>::PortValue^
                GetInversionMask<Pins>::value;

            Port::template Clear<portValue>();
            PortWriteIterator<Tail, PinList, ValueType>::template Clear<value>();
        }*/
    };

/*
////////////////////////////////////////////////////////////////////////////////
// class template PinList
// Represents generic set of IO pins that could be used like a virtual port.
// It can be composed from any number of pins from 1 to 16 from any IO port present in selected device
// (the last T17 type in PinList is a end of list marker).
// It can be used like this:
//		typedef PinList<Pa0, Pa1, Pa2, Pa3, Pb5, Pb4, Pb2> pins;
//		pins::Write(someValue);

////////////////////////////////////////////////////////////////////////////////

template
<
    typename T1  = NullType, typename T2  = NullType, typename T3  = NullType,
    typename T4  = NullType, typename T5  = NullType, typename T6  = NullType,
    typename T7  = NullType, typename T8  = NullType, typename T9  = NullType,
    typename T10 = NullType, typename T11 = NullType, typename T12 = NullType,
    typename T13 = NullType, typename T14 = NullType, typename T15 = NullType,
    typename T16 = NullType, typename T17 = NullType, typename T18 = NullType,
    typename T19 = NullType, typename T20 = NullType, typename T21 = NullType,
    typename T22 = NullType, typename T23 = NullType, typename T24 = NullType,
    typename T25 = NullType, typename T26 = NullType, typename T27 = NullType,
    typename T28 = NullType, typename T29 = NullType, typename T30 = NullType,
    typename T31 = NullType, typename T32 = NullType, typename T33 = NullType
>
struct PinList : public PinSet
    <
        typename MakePinList
        <	0,	T1,
            T2 , T3 , T4 ,
            T5 , T6 , T7 ,
            T8 , T9 , T10,
            T11, T12, T13,
            T14, T15, T16,
            T17, T18, T19,
            T20, T21, T22,
            T23, T24, T25,
            T26, T27, T28,
            T29, T30, T31,
            T32, T33
        >::Result
    >
{	};
*/