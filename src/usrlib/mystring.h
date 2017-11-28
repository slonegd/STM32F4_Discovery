#pragma once

template <uint8_t n>
class MyString
{
public:
    static const size_t size = n;
    char string[n];
    MyString (const char ( &string )[n])
    {
        for (uint8_t i = 0; i < size; ++i)
            this->string[i] = string[i];
    }
    
};