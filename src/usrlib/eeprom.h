/**
 * ОСНОВНЫЕ МОМЕНТЫ:
 * Работа с еепром с помощью структуры struct EEPROMst,
 * которая должна быть создана в файле macros.h.
 * Состав структуры произвольный,
 * минимальный размер данных 16 бит (8 недопустимо)
 * При инициализации прочитать из памяти в экземпляр EEPROMst с помощью функции EEPROMRead().
 * Внутри программы работаем с экземпляром EEPROMst без каких либо ограничений.
 * Периодически вызываем функцию EEPROMUpd() для обновления изменившихся значений в памяти
 * 
 * Реализация для STM32 имитирует еепром, занимая страницу флэш памяти
 * указатель на структуру страницы должен быть определен в macros.h
 *
 */
  
#pragma once

#include <stdbool.h>
#include <string.h>
#include "defines.h"

template <uint8_t sector> static constexpr uint32_t Addres();
template <uint8_t sector> static constexpr uint32_t Size();


template <class DATA, uint8_t sector>
class EEPROM 
{
public:
   DATA data;
   bool readFromFlash ();
   void update();

private:
   static constexpr uint32_t QtyBytes = sizeof(DATA);
   uint8_t buf[QtyBytes];
   uint16_t flashOffset;
   struct ByteInd_t {
       uint8_t byte;
       uint8_t ind;   
   };
   struct Flash_t {
       ByteInd_t data[Size<sector>()/2];
   };
   volatile Flash_t& flash = *( (Flash_t *) Addres<sector>() );
};


template <class Data, uint8_t sector>
bool EEPROM<Data,sector>::readFromFlash ()
{
   // обнуляем буфер перед заполнением
   memset (buf, 0, QtyBytes);

   // подумать на случай если данных стало меньше (при перепрошики)
   // надо читать все данные, но в maxInd только те которые меньше количества байт
   // чтоб не вылезть за границы массива
   uint16_t maxInd = 0;
   for (uint16_t i = 0; i < Size<sector>(); i++) {
       uint16_t index;
       index = flash.data[i].ind;
       if ( index < QtyBytes) {
           buf[index] = flash.data[i].byte;
           maxInd = (maxInd > index) ? maxInd : index;
       } else {
           flashOffset = i;
       }

   }
/*	if (FLASH_PAGE->Page[0] == 0xFFFFFFFF) {
       //еще ничего не записано
       return (false);
   } else {
       // просматриваем весь флеш
       uint16_t MaxWordN = 0;
       for (uint16_t i = 0; i < 256; i++) {
           uint16_t WordN;
           WordN = FLASH_PAGE->NumData[i].num;
           if (WordN < QtyWords) {
               EEPROMbuf[WordN] = FLASH_PAGE->NumData[i].data;
               MaxWordN = (MaxWordN < WordN) ? WordN : MaxWordN;
           } else {
               FLASHOffset = i;
               if ( MaxWordN != (QtyWords - 1) ) {
                   return (false);	//не все данные записаны
               }
               break;
           }
       }
       /**
        * копируем данные в структуру
       uint16_t* ar = (uint16_t*)st;
       for (uint16_t i = 0; i < QtyWords; i++) {
           ar[i] = EEPROMbuf[i];
       }
       return (true);
   }*/
   return false;
}
template <class Data, uint8_t sector>
void EEPROM<Data,sector>::update ()
{
   
}



template<> constexpr uint32_t Addres<1>()  { return 0x08004000; }
template<> constexpr uint32_t Size<1>()    { return 16*1024;    }

template<> constexpr uint32_t Addres<2>()  { return 0x08008000; }
template<> constexpr uint32_t Size<2>()    { return 16*1024;    }

template<> constexpr uint32_t Addres<3>()  { return 0x0800C000; }
template<> constexpr uint32_t Size<3>()    { return 16*1024;    }

template<> constexpr uint32_t Addres<4>()  { return 0x08010000; }
template<> constexpr uint32_t Size<4>()    { return 64*1024;    }

template<> constexpr uint32_t Addres<5>()  { return 0x08020000; }
template<> constexpr uint32_t Size<5>()    { return 128*1024;   }

template<> constexpr uint32_t Addres<6>()  { return 0x08040000; }
template<> constexpr uint32_t Size<6>()    { return 128*1024;   }

template<> constexpr uint32_t Addres<7>()  { return 0x08060000; }
template<> constexpr uint32_t Size<7>()    { return 128*1024;   }

template<> constexpr uint32_t Addres<8>()  { return 0x08080000; }
template<> constexpr uint32_t Size<8>()    { return 128*1024;   }

template<> constexpr uint32_t Addres<9>()  { return 0x080A0000; }
template<> constexpr uint32_t Size<9>()    { return 128*1024;   }

template<> constexpr uint32_t Addres<10>() { return 0x080C0000; }
template<> constexpr uint32_t Size<10>()   { return 128*1024;   }

template<> constexpr uint32_t Addres<11>() { return 0x080E0000; }
template<> constexpr uint32_t Size<11>()   { return 128*1024;   }



