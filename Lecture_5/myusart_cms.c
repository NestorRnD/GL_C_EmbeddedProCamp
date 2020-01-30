#include "stm32f30x.h"
#include "myusart_cms.h"

void usart1_init(uint32_t Speed)
{
    // 1
    // Enable Port C and USART1
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;	 //Enable port C
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;//Enable USART1

    // 2
    // Port C pins configuration
    // pin 4 as TX
    GPIOC->MODER &= ~GPIO_MODER_MODER4;
    GPIOC->MODER |= GPIO_MODER_MODER4_1;// Set MODE for port 4 to 10 - AF;
    GPIOC->OTYPER &= ~GPIO_OTYPER_OT_4; // Set TYPE for port 4 to 0 - Push-Pull
    GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR4; // Set HiSpeed mode
    GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR4;
    GPIOC->PUPDR |= GPIO_PUPDR_PUPDR4_0; // Set Pull Up for pin 4
    GPIOC->AFR[0] &= GPIO_AFRL_AFRL4;
    GPIOC->AFR[0] |= 7<<(4<<2); // Set AF -- USART1

    // pin 5 as RX
    GPIOC->MODER &= ~GPIO_MODER_MODER5;
    GPIOC->MODER |= GPIO_MODER_MODER5_1;// Set MODE for port 5 to 10 - AF;
//    GPIOC->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR5; // Set HiSpeed mode
    GPIOC->AFR[0] &= GPIO_AFRL_AFRL5;
    GPIOC->AFR[0] |= 7<<(5<<2);

    // 3
    // USART1 configuration
    USART1->BRR = SystemCoreClock/Speed;
    USART1->CR1 |= USART_CR1_RE ; // Receiver enabled
//    USART1->CR1 |= USART_CR1_OVER8 ; // Oversampling by 8
    USART1->CR1 &= ~(
		USART_CR1_M |	  // Word length 8 bit
		USART_CR1_PCE	  // Parity control disabled
		| USART_CR1_OVER8 // Oversampling by 16
		);

    USART1->CR2 &= ~USART_CR2_STOP; // 1 stop bit
}

void usart1_deInit()
{
    RCC->AHBENR &= ~RCC_AHBENR_GPIOCEN;	 //Disable port C
    RCC->APB2ENR &= ~RCC_APB2ENR_USART1EN;//Disable USART1
}

void usart1_open() // Enable USART1
{
    USART1->CR1 |=USART_CR1_TE; // Transmission Enabled
    USART1->CR1 |=USART_CR1_UE; // USART Enabled
}

void usart1_close()
{
    USART1->CR1 &= ~USART_CR1_TE;	   // Transmission disabled
    while( !(USART1->ISR & USART_ISR_TC) ) // Wait for transmission completed
	__asm__("nop");
    USART1->CR1 &= ~USART_CR1_UE;	   // USART Disabled
}

int usart1_read(uint8_t *data) // Resive byte from USART1
{
    if (USART1->ISR & USART_ISR_RXNE) {
	*data = USART1->RDR;
	return 1;
    }
    return 0;
}

int usart1_write(uint8_t data) // Send byte over USART1
{
    if (USART1->ISR & USART_ISR_TXE){
	USART1->TDR=data;
	return 1;
    }
    return 0;
}
