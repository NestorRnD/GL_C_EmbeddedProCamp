#include <stm32f30x.h>
#include <stdint.h>

void delay(uint32_t n)
{
    volatile uint32_t i;
    for(i=n;i>0;i--) __asm__("nop");
}

#define DELAY 1500000

// Number of leds
#define NLEDS 8
// every 4bits is port number conected to led
#define ALEDS 0xABCDEF89
// mask that will be rolled left and right
#define CONF 0b00010001

// Next 2 functions roll mask.
// First - clockwise
void cwRotMask(uint8_t *pmask)
{
    *pmask=(*pmask>>1)|((*pmask&1)<<(NLEDS-1));
}
// Second - contrclockwise
void ccwRotMask(uint8_t *pmask)
{
    *pmask=(*pmask<<1)|((*pmask&(1<<(NLEDS-1)))>>(NLEDS-1));
}

// Next function on/off leds accoding to mask
uint32_t SwitchLeds(uint8_t mask)
{
    uint32_t odr=0;
    int i;
    for(i=0;i<NLEDS;i++)
	if( mask&(1<<i) )
	    odr|=1<<((ALEDS>>(i<<2))&0xF);
    return odr;
}

int main(void)
{
    uint32_t mask=0;
    uint8_t mask8b=CONF;
    int i;

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
