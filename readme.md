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


