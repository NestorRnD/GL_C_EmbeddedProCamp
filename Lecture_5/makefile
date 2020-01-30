CPU=cortex-m4
DATAFORMAT=little-endian

CC=arm-none-eabi-gcc

OPTIONS= -mcpu=$(CPU) -m$(DATAFORMAT) -mthumb -DSTM32F303xC

ifdef DEBUG
    OPTIONS+= -O0 -g
endif

LINK=$(CC) -Tstm32_flash.ld -Wl,--gc-sections
OBJCP=arm-none-eabi-objcopy -Oihex
FLASH=./myflash

INC_PATH=./h

usart_test.elf: usart_test.o system_stm32f30x.o startup_stm32f30x.o myusart_cms.o
	$(LINK) -o $@ $^
	chmod -x $@

clean:
	rm *.o
	rm *.elf
	rm *.hex

flash: usart_test.hex
	$(FLASH) $^

#-------------------------------------

%.o: %.c
	$(CC) $(OPTIONS) -I$(INC_PATH) -c $^

%.o: %.s
	$(CC) $(OPTIONS) -I$(INC_PATH) -c $^

%.hex: %.elf
	$(OBJCP) $^ $@
