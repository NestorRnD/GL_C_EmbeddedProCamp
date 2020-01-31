//#define ONLY_CMSIS

#include <stdint.h>

#include <FreeRTOS.h>
#include <task.h>

#include <stm32f30x.h>

#ifndef ONLY_CMSIS
#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>
#endif

#define LED    8

void vInitAll()
{
#ifndef ONLY_CMSIS
    GPIO_InitTypeDef gpio;

    // Blue LED is connected to port E, pin 8 (AHB bus)
    RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOE, ENABLE );

    // Configure port E (LED)
    GPIO_StructInit( &gpio );
    gpio.GPIO_Mode = GPIO_Mode_OUT;
    gpio.GPIO_Pin  = LED;
    GPIO_Init( GPIOE, &gpio );
#else
    RCC -> AHBENR |= RCC_AHBENR_GPIOEEN;

    // Enable PORTE pin 8 as digital output
    GPIOE->MODER &= ~3<<(LED<<1);
    GPIOE->MODER |= 1<<(LED<<1);
#endif
}

void vLedTask (void *pvParameters)
{
#ifndef ONLY_CMSIS
    char state=0;
#endif
    while(1) {
#ifndef ONLY_CMSIS
	if (state == 0) {
            GPIO_SetBits(GPIOE,LED);
	    state = 1;
	} else {
	    GPIO_ResetBits(GPIOE,LED);
	    state = 0;
	}
#else
	GPIOE -> ODR ^= 1<<LED;
#endif
	vTaskDelay(500);
    }
}

int main()
{
    vInitAll();
    xTaskCreate(vLedTask, (char*)"LedTask", configMINIMAL_STACK_SIZE,
		NULL, tskIDLE_PRIORITY + 1, NULL);
    vTaskStartScheduler();
}