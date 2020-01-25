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

OBJDIR= obj

tCMSISOBJs= system_stm32f30x.o startup_stm32f30x.o stm32f30x_gpio.o stm32f30x_rcc.o stm32f30x_usart.o

tFRTOSOBJs= port.o tasks.o croutine.o event_groups.o heap_4.o list.o \
    queue.o stream_buffer.o timers.o

CMSISOBJs= $(addprefix $(OBJDIR)/, $(tCMSISOBJs))
FRTOSOBJs= $(addprefix $(OBJDIR)/, $(tFRTOSOBJs))

exercise12.elf: $(OBJDIR)/exercise12.o $(OBJDIR)/myusart.o $(CMSISOBJs) $(FRTOSOBJs)
	$(LINK) -o $@ $^
	chmod -x $@

clean:
	-rm $(OBJDIR)/*.o
	-rm *.elf
	-rm *.hex

flash: exercise12.hex
	$(FLASH) $^

$(CMSISOBJs): | $(OBJDIR)
$(FRTOSOBJs): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

#=======================================================

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CMSISINC) $(FRTOSINC) -c $^ -o $@

%.hex: %.elf
	$(OBJCP) $^ $@

$(OBJDIR)/%.o: CMSIS_src/%.c
	$(CC) $(CMSISINC) -c $^ -o $@

$(OBJDIR)/%.o: CMSIS_src/%.s
	$(CC) $(CMSISINC) -c $^ -o $@

$(OBJDIR)/%.o: FRTOS_src/%.c
	$(CC) $(CMSISINC) $(FRTOSINC) -c $^ -o $@

$(OBJDIR)/%.o: FRTOS_port/%.c
	$(CC) $(CMSISINC) $(FRTOSINC) -c $^ -o $@

