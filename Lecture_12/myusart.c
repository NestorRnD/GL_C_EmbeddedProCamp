#include "stm32f30x.h"
#include "stm32f30x_rcc.h"
#include "stm32f30x_gpio.h"
#include "stm32f30x_usart.h"

// Грубе перше наближення для виводу через VCP (USART1)


static USART_InitTypeDef usart_1;
static GPIO_InitTypeDef gpio_usart1;

void usart1_init()
{
    // налаштування USART
    // 1
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
    GPIO_StructInit( &gpio_usart1 );
    gpio_usart1.GPIO_Mode = GPIO_Mode_AF;
    gpio_usart1.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_Init(GPIOC, &gpio_usart1);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource4, GPIO_AF_7);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource5, GPIO_AF_7);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    // 2
    USART_StructInit(&usart_1);
    usart_1.USART_BaudRate = 115200;
    usart_1.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    usart_1.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
    usart_1.USART_Parity = USART_Parity_No;
    usart_1.USART_StopBits = USART_StopBits_1;
    usart_1.USART_WordLength = USART_WordLength_8b;

    USART_Init(USART1, &usart_1);
    USART_Cmd(USART1, ENABLE);
}

uint8_t usart1_getc(uint8_t *data)
{
    if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET){
	*data = USART_ReceiveData(USART1);
	return 1;
    }
    return 0;
}

uint8_t usart1_putc(uint8_t data)
{
    if (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == SET){
	USART_SendData(USART1, data);
	return 1;
    }
    return 0;
}

void usart1_puts(char *buff)
{
    while(*buff){
/* якщо потрібно, то можем поміняти стиль кінця рядка
	if(*buff=='\n')
	    while(!usart1_putc('\r'));
//*/
	while(!usart1_putc(*buff));
	buff++;
    }
}


