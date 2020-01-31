#include <stdio.h>
#include "my_color_conv.h"

int main(void)
{
    uint32_t rgb888=0x0AAAAAA;
    printf("RGB888 to RGB565 test\n");
    printf("%06X => %0X\n",rgb888,rgb888_to_rgb565(rgb888));
    return 0;
}