#include <stdint.h>
#include <stdlib.h>

#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

#include <stm32f30x.h>

#include "myusart.h"

// Number of philosophers
#define N 8

// Number of leds
#define NLEDS 8

uint32_t aLeds[]={9,10,11,12,13,14,15,8};
uint8_t aPhs[]={0,1,2,3,4,5,6,7};

char *strTaskNames[]={
	"Ph1",
	"Ph2",
	"Ph3",
	"Ph4",
	"Ph5",
	"Ph6",
	"Ph7",
	"Ph8"
    };

void vInitAll()
{
    uint32_t mask;
    int i;

    // Enable CLK for port E 
    RCC -> AHBENR |= RCC_AHBENR_GPIOEEN;

    // Configure PORTE pins as digital output
    mask=0;
    for(i=0;i<NLEDS;i++)
	mask|=3<<(aLeds[i]<<1);
    GPIOE->MODER &= ~mask;
    mask=0;
    for(i=0;i<NLEDS;i++)
	mask|=1<<(aLeds[i]<<1);
    GPIOE->MODER |= mask;
}

void ErrorBlink (int n)
{
    uint32_t i,leds=0;

    for(i=0;i<NLEDS;i++)
	leds |= 1<<(aLeds[i]);

    while(n>0) {
	GPIOE -> ODR ^= leds;
	for(i=1000000;i>0;i--)
	    __asm__("nop");
	n--;
    }
}

static SemaphoreHandle_t aForksMtx[N];

void CreateMutexes(void)
{
    int i;
    for(i=0;i<N;i++){
	aForksMtx[i]=xSemaphoreCreateMutex();
	if(aForksMtx[i]==NULL)
	    while(1) ErrorBlink(10);
    }
}

void vPhilosophTask (void *pvParameter)
{
    uint8_t fork_l, fork_r;
    uint32_t leds, wait;

    fork_l=*((uint8_t*)pvParameter);
    fork_r=(fork_l+1)%N;
    leds= 1<<(aLeds[fork_l]);
    leds |= 1<<(aLeds[fork_r]);

    while(1){
	wait=rand()%500+200;
	usart1_puts(strTaskNames[fork_l]);
	usart1_puts(" T\n"); //Думае
	vTaskDelay(wait);
	while(1){
	    if(xSemaphoreTake(aForksMtx[fork_l],(TickType_t)1000)==pdTRUE) {
		if(xSemaphoreTake(aForksMtx[fork_r],(TickType_t)500)==pdTRUE) {
		    wait=rand()%300+200;
		    GPIOE->ODR |= leds;
		    usart1_puts(strTaskNames[fork_l]);
		    usart1_puts(" E\n"); // Їсть
		    vTaskDelay(wait);
		    GPIOE->ODR &= ~leds;
		    xSemaphoreGive(aForksMtx[fork_r]);
		    xSemaphoreGive(aForksMtx[fork_l]);
		    break;
		}
		xSemaphoreGive(aForksMtx[fork_l]);
	    } else {
		usart1_puts(strTaskNames[fork_l]);
		usart1_puts(" D!!!\n"); // Помер з голоду
		while(1) ErrorBlink(10);
	    }
	}
    }
    vTaskDelete(NULL);
}


int main ()
{
    uint32_t i;
    BaseType_t ret;
    char *Name="Philosopher?";
    vInitAll();
    usart1_init();

    CreateMutexes();

    usart1_puts("Start\n");
    for(i=0;i<N;i++){
	ret=xTaskCreate(vPhilosophTask, strTaskNames[i],
		configMINIMAL_STACK_SIZE, (void *)(aPhs+i), tskIDLE_PRIORITY+1, NULL);
	if(ret!=pdPASS)break;
    }
    if(ret==pdPASS)
	vTaskStartScheduler();
    while(1)
	ErrorBlink(10);
}
