#include <stdint.h>

void usart1_init(uint32_t); // Enable (tacting) and configure port C (pins 4,5) and USART1 (VCP in Discovery)
void usart1_deInit(); // Disable port C and USART1
void usart1_open(); // Allow transmission and enable USART1
void usart1_close(); //Disable transmission and USART1
int usart1_read(uint8_t *); // Resive byte from USART1. Return 1 if ok otherwise 0
int usart1_write(uint8_t); // Send byte over USART1. Return 1 if ok otherwise 0
