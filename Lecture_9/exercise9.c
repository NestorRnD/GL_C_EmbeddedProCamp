#include <stdint.h>

#include <FreeRTOS.h>
#include <task.h>

#include <stm32f30x.h>


// Number of leds
#define NLEDS 8
// every 4bits is port number conected to led
#define ALEDS 0xABCDEF89

int BlinkOn=0;

void vInitAll()
{
    RCC -> AHBENR |= RCC_AHBENR_GPIOEEN;

    // Enable PORTE pin 8 as digital output
    GPIOE->MODER &= ~3<<(LED<<1);
    GPIOE->MODER |= 1<<(LED<<1);
}

void vLedTask (void *pvParameters)
{
    int i;
    for(i=0;i<10;i++){
	GPIOE -> ODR ^= 1<<LED;
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