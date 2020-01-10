#include <stm32f30x.h>
#include <stdint.h>


int Init()
{
}

int deInit()
{
}

int open()
{
}

int close()
{
}

int read()
{
}

int write()
{
}

int main(void)
{
    // Enable CLK for port E 
    RCC -> AHBENR |= RCC_AHBENR_GPIOEEN;

    // Enable PORTE pins as digital output
    for(i=0;i<NLEDS;i++)
	mask|=3<<(((ALEDS>>(i<<2))&0xF)<<1);
    GPIOE->MODER &= ~mask;
    mask=0;
    for(i=0;i<NLEDS;i++)
	mask|=1<<(((ALEDS>>(i<<2))&0xF)<<1);
    GPIOE->MODER |= mask;

    // Create mask for ODR
    mask=0;
    for(i=0;i<NLEDS;i++)
	mask|=1<<((ALEDS>>(i<<2))&0xF);

    i=0;
    while (1){
	GPIOE -> ODR &= ~mask;
	GPIOE -> ODR |= SwitchLeds(mask8b);
	if(i<50)
	    cwRotMask(&mask8b);
	else
	    ccwRotMask(&mask8b);
	i=(i+1)%100;
	delay(DELAY);
    }
}
