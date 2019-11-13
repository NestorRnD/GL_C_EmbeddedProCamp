#include <stdio.h>

//*
#include "myswap1.h"
/*/
#include "myswap2.h"
//*/

int main(void){
    union{
	uint16_t u16;
	uint32_t u32;
	uint64_t u64;
    }test;

    test.u64=
//	0x0123456789ABCDEF;
	0xEFCDAB8967452301;
    printf("Swap testing:\n");
    printf("uint16: %04X <=> %04X\n",    test.u16,swap16(test.u16));
    printf("uint32: %08X <=> %08X\n",    test.u32,swap32(test.u32));
    printf("uint64: %016lX <=> %016lX\n",test.u64,swap64(test.u64));

    return 0;
}

