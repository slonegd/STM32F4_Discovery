v0.08   перенес объвление перечислений llul функций
        в bf файл, так как они используються в 
        методах классов пинов;
        битовые поля определил с перечислениями;
        сделал переменные таймеров статическими
        чтобы к ним отсутсвовал доступ вне функций;
        добавил функцию таймера для прерывания;
        начал работу с аппаратным таймером для ШИМ;
        переименовал проект;

v0.11   компиляция -02 1540 байт

v0.12   начал создание двух уровней абстракции
        hal - hardware abstract level
            : классы с методами,
              не привязанными к конкретному контроллеру
              сделал pin_hal
        ral - register abstract level
            : обёртка из структур над регистрами
              с функциями по работе с ними со строгой типизацией
              этот уровень необходим для hal
              сделал GPIO_ral, RCC_ral

v0.13   переработал программный таймер под стиль с++

v0.14   ещё раз переделал программный таймер
        без оверхеда в виде массива указателей

v0.15   исправил ошибку в Timers::update
        рефакторинг портов для списка пинов
        добавление полей для списка пинов
        начал разбираться со списком пинов

v0.16   неоптимизированная запись в список пинов

v0.17   избавился от файлов старой разработки
        начал создание FLASH_t
        начал создание TIM_t и pwm_hal

v0.18   продолжил TIM_ral и pwm_hal
        красный светодиод работает от шим

v0.19   pwm_hal в процессе

v0.20   закончил pwm_hal

v0.21   имитация еепром в процессе

v0.220  имитация еепром закончил, flash_hal.h

v0.221  USART_ral USART_hal DMA_ral в процессе

v0.222  начал modbusSlave.h

v0.223  начал adc_hal.h, в работе уарт модбас дма ацп

v0.224  static_assert в hal

v0.225  uart в процессе


