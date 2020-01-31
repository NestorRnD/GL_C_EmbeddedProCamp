#include <stm32f30x.h>
#include <stdint.h>
#include "myusart_cms.h"

//               1 2  3  4  5  6  7  8
uint8_t aLeds[]="\011\012\013\014\015\016\017\010";

#define NLEDS 8

int main(void)
{
    int i;
    uint32_t mask=0;
    uint8_t data;

    // Enable CLK for port E 
    RCC->AHBENR |= RCC_AHBENR_GPIOEEN;

    // Enable PORTE pins as digital output
    for(i=0;i<NLEDS;i++)
	mask|=3<<(aLeds[i]<<1);
    GPIOE->MODER &= ~mask;
    mask=0;
    for(i=0;i<NLEDS;i++)
	mask|=1<<(aLeds[i]<<1);
    GPIOE->MODER |= mask;

    // Create mask for ODR
    mask=0;
    for(i=0;i<NLEDS;i++)
	mask|=1<<aLeds[i];

    GPIOE->ODR &= ~mask;

//
    usart1_init(115200);
/*/
    usart1_init(9600);
//*/
    usart1_open();

    while (1){
	while(!usart1_read(&data))
		__asm__("nop");;
	while(!usart1_write(data)); // Echo char
	if( (data>'0')&&(data<'9') )
	    GPIOE->ODR ^= 1<<aLeds[data-'1'];
	else switch(data){
	    case '0':
		GPIOE->ODR &= ~mask; // off all leds
		break;
	    case 'i':
		GPIOE->ODR ^= mask; // inverse all leds
		break;
	}
    }
}
