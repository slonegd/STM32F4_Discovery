#include "init.h"

volatile uint32_t i = 0;
volatile uint32_t j = 0;


int main(void)
{
    InitCLK ();

	while (1)
	{
		i++;
		j--;
	}
}