/**
 * Библиотека классов портов
 * Каждый порт предствлен в виде отдельного статического клсса
 * и может быть передан в качестве параметра шаблона
 */

#include "stm32f4_bf.hpp"

#ifndef PORTC_HPP
#define PORTC_HPP

class PA 
{ 
protected:	
    static volatile uint32_t &moder()   { return (uint32_t &)GPIOA->MODER;    } 
    static volatile uint32_t &otyper()  { return (uint32_t &)GPIOA->OTYPER;   } 
    static volatile uint32_t &ospeedr() { return (uint32_t &)GPIOA->OSPEEDR;  }
    static volatile uint32_t &pupdr()   { return (uint32_t &)GPIOA->PUPDR;    } 
    static volatile uint32_t &odr()     { return (uint32_t &)GPIOA->ODR;      }
    static volatile uint32_t &idr()     { return (uint32_t &)GPIOA->IDR;      }  
    static volatile uint32_t &bsrr()    { return (uint32_t &)GPIOA->BSRR;     }
    static volatile RCC_AHB1ENR_t &ahb1enr() { return (RCC_AHB1ENR_t &)RCC->AHB1ENR; } 
public:
    inline static void ClockEnable (void) 
    { 
        ahb1enr().GPIOAEN = 0b1;
    } 
};

class PB
{ 
protected:	
    static volatile uint32_t &moder()   { return (uint32_t &)GPIOB->MODER;    } 
    static volatile uint32_t &otyper()  { return (uint32_t &)GPIOB->OTYPER;   } 
    static volatile uint32_t &ospeedr() { return (uint32_t &)GPIOB->OSPEEDR;  }
    static volatile uint32_t &pupdr()   { return (uint32_t &)GPIOB->PUPDR;    } 
    static volatile uint32_t &odr()     { return (uint32_t &)GPIOB->ODR;      } 
    static volatile uint32_t &idr()     { return (uint32_t &)GPIOB->IDR;      } 
    static volatile uint32_t &bsrr()    { return (uint32_t &)GPIOB->BSRR;     }
    static volatile RCC_AHB1ENR_t &ahb1enr() { return (RCC_AHB1ENR_t &)RCC->AHB1ENR; } 
public:
    inline static void ClockEnable (void) 
    { 
        ahb1enr().GPIOBEN = 0b1;
    } 
};

class PC
{ 
protected:	
    static volatile uint32_t &moder()   { return (uint32_t &)GPIOC->MODER;    } 
    static volatile uint32_t &otyper()  { return (uint32_t &)GPIOC->OTYPER;   } 
    static volatile uint32_t &ospeedr() { return (uint32_t &)GPIOC->OSPEEDR;  }
    static volatile uint32_t &pupdr()   { return (uint32_t &)GPIOC->PUPDR;    } 
    static volatile uint32_t &odr()     { return (uint32_t &)GPIOC->ODR;      }
    static volatile uint32_t &idr()     { return (uint32_t &)GPIOC->IDR;      } 
    static volatile uint32_t &bsrr()    { return (uint32_t &)GPIOC->BSRR;     }
    static volatile RCC_AHB1ENR_t &ahb1enr() { return (RCC_AHB1ENR_t &)RCC->AHB1ENR; } 
public:
    inline static void ClockEnable (void) 
    { 
        ahb1enr().GPIOCEN = 0b1;
    } 
};

class PD 
{ 
protected:	
    static volatile uint32_t &moder()   { return (uint32_t &)GPIOD->MODER;    } 
    static volatile uint32_t &otyper()  { return (uint32_t &)GPIOD->OTYPER;   } 
    static volatile uint32_t &ospeedr() { return (uint32_t &)GPIOD->OSPEEDR;  }
    static volatile uint32_t &pupdr()   { return (uint32_t &)GPIOD->PUPDR;    } 
    static volatile uint32_t &odr()     { return (uint32_t &)GPIOD->ODR;      }
    static volatile uint32_t &idr()     { return (uint32_t &)GPIOD->IDR;      }
    static volatile uint32_t &bsrr()    { return (uint32_t &)GPIOD->BSRR;     } 
    static volatile RCC_AHB1ENR_t &ahb1enr() { return (RCC_AHB1ENR_t &)RCC->AHB1ENR; } 
public:
    inline static void ClockEnable (void) 
    { 
        ahb1enr().GPIODEN = 0b1;
    } 
};

class PE
{ 
protected:	
    static volatile uint32_t &moder()   { return (uint32_t &)GPIOE->MODER;    } 
    static volatile uint32_t &otyper()  { return (uint32_t &)GPIOE->OTYPER;   } 
    static volatile uint32_t &ospeedr() { return (uint32_t &)GPIOE->OSPEEDR;  }
    static volatile uint32_t &pupdr()   { return (uint32_t &)GPIOE->PUPDR;    } 
    static volatile uint32_t &odr()     { return (uint32_t &)GPIOE->ODR;      } 
    static volatile uint32_t &idr()     { return (uint32_t &)GPIOE->IDR;      } 
    static volatile uint32_t &bsrr()    { return (uint32_t &)GPIOE->BSRR;     } 
    static volatile RCC_AHB1ENR_t &ahb1enr() { return (RCC_AHB1ENR_t &)RCC->AHB1ENR; } 
public:
    inline static void ClockEnable (void) 
    { 
        ahb1enr().GPIOEEN = 0b1;
    } 
};

class PF
{ 
protected:	
    static volatile uint32_t &moder()   { return (uint32_t &)GPIOF->MODER;    } 
    static volatile uint32_t &otyper()  { return (uint32_t &)GPIOF->OTYPER;   } 
    static volatile uint32_t &ospeedr() { return (uint32_t &)GPIOF->OSPEEDR;  }
    static volatile uint32_t &pupdr()   { return (uint32_t &)GPIOF->PUPDR;    } 
    static volatile uint32_t &odr()     { return (uint32_t &)GPIOF->ODR;      } 
    static volatile uint32_t &idr()     { return (uint32_t &)GPIOF->IDR;      } 
    static volatile uint32_t &bsrr()    { return (uint32_t &)GPIOF->BSRR;     } 
    static volatile RCC_AHB1ENR_t &ahb1enr() { return (RCC_AHB1ENR_t &)RCC->AHB1ENR; } 
public:
    inline static void ClockEnable (void) 
    { 
        ahb1enr().GPIOFEN = 0b1;
    } 
};

class PG
{ 
protected:	
    static volatile uint32_t &moder()   { return (uint32_t &)GPIOG->MODER;    } 
    static volatile uint32_t &otyper()  { return (uint32_t &)GPIOG->OTYPER;   } 
    static volatile uint32_t &ospeedr() { return (uint32_t &)GPIOG->OSPEEDR;  }
    static volatile uint32_t &pupdr()   { return (uint32_t &)GPIOG->PUPDR;    } 
    static volatile uint32_t &odr()     { return (uint32_t &)GPIOG->ODR;      }
    static volatile uint32_t &idr()     { return (uint32_t &)GPIOG->IDR;      }  
    static volatile uint32_t &bsrr()    { return (uint32_t &)GPIOG->BSRR;     } 
    static volatile RCC_AHB1ENR_t &ahb1enr() { return (RCC_AHB1ENR_t &)RCC->AHB1ENR; } 
public:
    inline static void ClockEnable (void) 
    { 
        ahb1enr().GPIOGEN = 0b1;
    } 
};

class PH
{ 
protected:	
    static volatile uint32_t &moder()   { return (uint32_t &)GPIOH->MODER;    } 
    static volatile uint32_t &otyper()  { return (uint32_t &)GPIOH->OTYPER;   } 
    static volatile uint32_t &ospeedr() { return (uint32_t &)GPIOH->OSPEEDR;  }
    static volatile uint32_t &pupdr()   { return (uint32_t &)GPIOH->PUPDR;    } 
    static volatile uint32_t &odr()     { return (uint32_t &)GPIOH->ODR;      } 
    static volatile uint32_t &idr()     { return (uint32_t &)GPIOH->IDR;      } 
    static volatile uint32_t &bsrr()    { return (uint32_t &)GPIOH->BSRR;     } 
    static volatile RCC_AHB1ENR_t &ahb1enr() { return (RCC_AHB1ENR_t &)RCC->AHB1ENR; } 
public:
    inline static void ClockEnable (void) 
    { 
        ahb1enr().GPIOHEN = 0b1;
    } 
};

class PI
{ 
protected:	
    static volatile uint32_t &moder()   { return (uint32_t &)GPIOI->MODER;    } 
    static volatile uint32_t &otyper()  { return (uint32_t &)GPIOI->OTYPER;   } 
    static volatile uint32_t &ospeedr() { return (uint32_t &)GPIOI->OSPEEDR;  }
    static volatile uint32_t &pupdr()   { return (uint32_t &)GPIOI->PUPDR;    } 
    static volatile uint32_t &odr()     { return (uint32_t &)GPIOI->ODR;      } 
    static volatile uint32_t &idr()     { return (uint32_t &)GPIOI->IDR;      } 
    static volatile uint32_t &bsrr()    { return (uint32_t &)GPIOI->BSRR;     } 
    static volatile RCC_AHB1ENR_t &ahb1enr() { return (RCC_AHB1ENR_t &)RCC->AHB1ENR; } 
public:
    inline static void ClockEnable (void) 
    { 
        ahb1enr().GPIOIEN = 0b1;
    } 
};


#endif // PORTC_HPP