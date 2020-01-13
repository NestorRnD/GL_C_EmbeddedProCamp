#include <stdint.h>

#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

#include <stm32f30x.h>

#define BUTTON	0
// Number of leds
#define NLEDS 8
// every 4bits is port number conected to led
#define ALEDS 0x8FEDCBA9

#define DELAY 2000000

volatile int LedsBlink=0; // 0 - no led blink
uint64_t idleTicks=0;

void vInitAll()
{
    uint32_t mask=0;
    int i;

    // Enable CLK for ports A and E 
    RCC -> AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOEEN;

    // Configure BUTTON pin (port A) as input
    GPIOA->MODER &= ~3<<(BUTTON<<1);
    GPIOA->PUPDR &= ~3<<(BUTTON<<1); // no pull-up/pull-down

    // Configure PORTE pins as digital output
    for(i=0;i<NLEDS;i++)
	mask|=3<<(((ALEDS>>(i<<2))&0xF)<<1);
    GPIOE->MODER &= ~mask;
    mask=0;
    for(i=0;i<NLEDS;i++)
	mask|=1<<(((ALEDS>>(i<<2))&0xF)<<1);
    GPIOE->MODER |= mask;
}

void myDelay(uint32_t n) // This function is only for priority demonstration (led will blink only for task with max priority)
{
    volatile uint32_t i;
    for(i=n;i>0;i--)
	__asm__("nop");
}

void vLedTask (void *pvParameters)
{
    uint32_t i,led;

    led=*((int*)pvParameters);
    led= 1<<((ALEDS>>(led<<2))&0xF);

    for(i=0;i<10;i++){
	GPIOE -> ODR ^= led;
	myDelay(DELAY);
    }
    taskENTER_CRITICAL();
    LedsBlink--;
    taskEXIT_CRITICAL();
    vTaskDelete(NULL);
}

void ErrorTask (int n)
{
    uint32_t i,leds=0;

    for(i=0;i<NLEDS;i++)
	leds |= 1<<((ALEDS>>(i<<2))&0xF);

    while(n>0) {
	GPIOE -> ODR ^= leds;
	myDelay(1000000);
	n--;
    }
}

void vButtonTask (void *pvParameters)
{
    uint32_t ledIndex;
    BaseType_t ret;
    while(1) {
	if((LedsBlink<8) && (GPIOA->IDR & (1<<BUTTON))){ // Button pressed
	    taskENTER_CRITICAL();
	    if(LedsBlink<8){
		ledIndex=LedsBlink++;
		ret=xTaskCreate(vLedTask, (char*)"LedTask", configMINIMAL_STACK_SIZE,
			&ledIndex, tskIDLE_PRIORITY+LedsBlink, NULL);
		if(ret!=pdPASS){
		    ErrorTask(6);
		    LedsBlink--;
		}
	    }
	    taskEXIT_CRITICAL();
	    vTaskDelay(200);
	}
	vTaskDelay(100);
    }
}

#define STATIC_TASK_STACK_SIZE 128
StaticTask_t xTaskBuffer;
StackType_t xStack[ STATIC_TASK_STACK_SIZE ];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
                                    StackType_t **ppxIdleTaskStackBuffer,
                                    uint32_t *pulIdleTaskStackSize )
{
    static StaticTask_t xIdleTaskTCB;
    static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer,
                                     StackType_t **ppxTimerTaskStackBuffer,
                                     uint32_t *pulTimerTaskStackSize )
{
    static StaticTask_t xTimerTaskTCB;
    static StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];

    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}

int main ()
{
    TaskHandle_t xHandle = NULL;
    vInitAll();

    xHandle=xTaskCreateStatic(vButtonTask, (char*)"ButtonTask",
		STATIC_TASK_STACK_SIZE, NULL,
		configMAX_PRIORITIES-1, xStack, &xTaskBuffer);
    if(xHandle!=NULL)
	vTaskStartScheduler();
    while(1)
	ErrorTask(10);
}

void vApplicationIdleHook( void ){
    idleTicks++;
}