CPU=cortex-m4
FPU=-mfloat-abi=hard -mfpu=fpv4-sp-d16
DATAFORMAT=little-endian

CC=arm-none-eabi-gcc -mcpu=$(CPU) -m$(DATAFORMAT) $(FPU) -DSTM32F303xC -mthumb

ifdef DEBUG
    CC+= -O0 -g
endif

LINK=$(CC) -Tstm32_flash.ld -Wl,--gc-sections
OBJCP=arm-none-eabi-objcopy -Oihex
FLASH=./myflash

CMSISINC=-I ./CMSIS_inc
FRTOSINC=-I ./FRTOS_inc -I./FRTOS_port

CMSISOBJs= obj/system_stm32f30x.o obj/startup_stm32f30x.o obj/stm32f30x_gpio.o obj/stm32f30x_rcc.o

FRTOSOBJs= obj/port.o obj/tasks.o obj/croutine.o \
    obj/event_groups.o obj/heap_2.o obj/list.o \
    obj/queue.o obj/stream_buffer.o obj/timers.o


test_frtos.elf: obj/test_frtos.o $(CMSISOBJs) $(FRTOSOBJs)
	$(LINK) -o $@ $^
	chmod -x $@

clean:
	rm *.elf
	rm *.hex
	rm obj/*.o

flash: test_frtos.hex
	$(FLASH) $^


#=======================================================

obj/%.o: %.c
	$(CC) $(CMSISINC) $(FRTOSINC) -c $^ -o $@

%.hex: %.elf
	$(OBJCP) $^ $@

obj/%.o: CMSIS_src/%.c
	$(CC) $(CMSISINC) -c $^ -o $@


obj/%.o: CMSIS_src/%.s
	$(CC) $(CMSISINC) -c $^ -o $@

obj/%.o: FRTOS_src/%.c
	$(CC) $(CMSISINC) $(FRTOSINC) -c $^ -o $@

obj/%.o: FRTOS_port/%.c
	$(CC) $(CMSISINC) $(FRTOSINC) -c $^ -o $@

