#include <stdio.h>

/*
#include "myswap1.h"
/*/
#include "myswap2.h"
//*/

#define TEST(bits) test.u##bits,swap##bits(test.u##bits)

int main(void)
{
    union{
	uint16_t u16;
	uint32_t u32;
	uint64_t u64;
    }test;

    test.u64=
//	0x0123456789ABCDEF;
	0xEFCDAB8967452301;
    printf("Swap testing:\n");
    printf("uint16: %04X <=> %04X\n",    TEST(16));
    printf("uint32: %08X <=> %08X\n",    TEST(32));
    printf("uint64: %016lX <=> %016lX\n",TEST(64));

    return 0;
}
