/** шаблонный класс сохранения данных во flash
 *  при инициализации необходимо указать
 *      структуру, которая будет сохраняться
 *      сектор флеша, куда записывать
 *  Размер структуры не более 255 байт, поскольку кодируються во флеше
 *  в виде двух байт, один данные, второй их индекс в байтовом массиве
 * 
 *  Перед работой с данными, их надо сначала прочитать, и если результат
 *  отрицательный, то инициировать значениями по умолчанию
 * 
 *  Для обновления изменённых данных периодически вызывать update
 * 
 *////////////////////////////////////////////////////////////////////////////
  
#pragma once

#include <stdbool.h>
#include <string.h>
#include "FLASH_ral.h"

template <uint8_t sector> static constexpr uint32_t Addres();
template <uint8_t sector> static constexpr int32_t  Size();


template <class DATA, uint8_t sector>
class Flash 
{
public:
    // обязательно должен быть первым
    // потому что использую this как указатель к структуре
    DATA data;
    bool readFromFlash ();
    void update();
    Flash ()
    {
        static_assert (
            sector >= 2 && sector <= 11,
            "недопустимый сектор"
        );
        static_assert (
            sizeof(DATA) < 255,
            "структура данных слишком велика"
        );
        FLASH_t::EndOfProgInterruptEn();
    }
private:
    static constexpr uint8_t QtyBytes = sizeof(DATA);
    uint8_t copy[QtyBytes];
    uint8_t* original = (uint8_t*)this;
    int32_t flashOffset;
    uint8_t needErase;
    struct ByteInd_t {
        uint8_t byte;
        uint8_t ind;   
    };
    union Flash_t {
        ByteInd_t data[Size<sector>()/2];
        uint16_t word[Size<sector>()/2];
    };
    volatile Flash_t& flash = *( (Flash_t *) Addres<sector>() );
};


template <class Data, uint8_t sector>
bool Flash<Data,sector>::readFromFlash ()
{
    // обнуляем буфер перед заполнением
    memset (copy, 0xFF, QtyBytes);
 
    // чтение данных в копию data в виде массива
    flashOffset = -1;
    bool indExist[QtyBytes] = {false};
    for (uint32_t i = 0; i < Size<sector>(); i++) {
        uint8_t index;
        index = flash.data[i].ind;
        if ( index < QtyBytes) {
            copy[index] = flash.data[i].byte;
            indExist[index] = true;
        } else if (index == 0xFF) {
            flashOffset = i;
            break;
        }
    }

    // проверка есть ли ещё место
    if ( flashOffset == -1) {
        needErase = true;
        return false;    
    }

    // проверка остальной части сектора флэш
    for (uint32_t i = flashOffset; i < Size<sector>(); i++) {
        if (flash.word[i] != 0xFFFF) {
            needErase = true;
            return false;    
        }
    }

    // проверка, что все данные прочитаны
    bool tmp = true;
    for (uint8_t i = 0; i < QtyBytes; i++) {
        tmp &= indExist[i];
    }
    if (tmp) {
        memcpy(original, copy, QtyBytes);
        return true;
    } else {
        return false;
    }

}
template <class Data, uint8_t sector>
void Flash<Data,sector>::update ()
{
    // реализация автоматом
	enum FuncState {
		CheckChanges,
		StartWrite,
		CheckWrite,
		Errase,
		CheckErase
	};
    static FuncState state = CheckChanges;
    static volatile uint8_t dataWrite = 0;
    static uint8_t byteN = 0;

	switch (state) {

    case CheckChanges:
        if (needErase) {
            state = Errase;
        } else if (original[byteN] == copy[byteN]) {
            byteN++;
            if (byteN == QtyBytes) {
                byteN = 0;
            }
        } else {
            state = StartWrite;
        }
		break;

    case StartWrite:
        if ( !FLASH_t::Busy() ) {
            FLASH_t::Unlock();
            FLASH_t::SetProgMode();
            FLASH_t::SetProgSize (FLASH_t::ProgSize::x16);
            dataWrite = original[byteN];
            flash.word[flashOffset] = (uint16_t)byteN << 8 | dataWrite;
            state = CheckWrite;
        }
        break;

    case CheckWrite:
        if ( FLASH_t::EndOfProg() ) {
            FLASH_t::ClearEndOfProgFlag();
            FLASH_t::Lock();
            copy[byteN] = dataWrite;
            flashOffset++;
            if ( flashOffset >= Size<sector>() ) {
                needErase = true;
            }
            state = CheckChanges;
        }
        break;

    case Errase:
        if ( !FLASH_t::Busy() ) {
            FLASH_t::Unlock();
            FLASH_t::template StartEraseSector<(FLASH_t::Sectors)sector>();
            state = CheckErase;
        }
        break;

    case CheckErase:
        if ( FLASH_t::EndOfProg() ) {
            FLASH_t::ClearEndOfProgFlag();
            FLASH_t::Lock();
            // проверка, что стёрли
            bool tmp = true;
            for (uint32_t i = 0; i < Size<sector>(); i++) {
                tmp &= (flash.word[i] == 0xFFFF);
            }
            if (tmp) {
                needErase = false;
                memset (copy, 0xFF, QtyBytes);
                flashOffset = 0;
            }
            state = CheckChanges;
        }
        break;
	} // switch
}



template<> constexpr uint32_t Addres<1>()  { return 0x08004000; }
template<> constexpr int32_t Size<1>()     { return 16*1024;    }

template<> constexpr uint32_t Addres<2>()  { return 0x08008000; }
template<> constexpr int32_t Size<2>()     { return 16*1024;    }

template<> constexpr uint32_t Addres<3>()  { return 0x0800C000; }
template<> constexpr int32_t Size<3>()     { return 16*1024;    }

template<> constexpr uint32_t Addres<4>()  { return 0x08010000; }
template<> constexpr int32_t Size<4>()     { return 64*1024;    }

template<> constexpr uint32_t Addres<5>()  { return 0x08020000; }
template<> constexpr int32_t Size<5>()     { return 128*1024;   }

template<> constexpr uint32_t Addres<6>()  { return 0x08040000; }
template<> constexpr int32_t Size<6>()     { return 128*1024;   }

template<> constexpr uint32_t Addres<7>()  { return 0x08060000; }
template<> constexpr int32_t Size<7>()     { return 128*1024;   }

template<> constexpr uint32_t Addres<8>()  { return 0x08080000; }
template<> constexpr int32_t Size<8>()     { return 128*1024;   }

template<> constexpr uint32_t Addres<9>()  { return 0x080A0000; }
template<> constexpr int32_t Size<9>()     { return 128*1024;   }

template<> constexpr uint32_t Addres<10>() { return 0x080C0000; }
template<> constexpr int32_t Size<10>()    { return 128*1024;   }

template<> constexpr uint32_t Addres<11>() { return 0x080E0000; }
template<> constexpr int32_t Size<11>()    { return 128*1024;   }





