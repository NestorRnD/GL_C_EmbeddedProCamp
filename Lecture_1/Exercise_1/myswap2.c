/*             (version 2) source
 *  Function for conversion uint16, uint32 and uint64
 *  Little-Endian Memory Format <=> Big-Endian Memory Format
 *       (c) Nestor Tyshko, email:tyshko.n@gmail.com
 */

#include "myswap2.h"

// uncoment next line for self testing
//#define SELFTEST_MY_SWAP2

#define CONVERSION(size) \
    uint8_t i; \
    res=source&0xff; \
    for(i=0;i<(size)-1;i++){ \
	source>>=8; \
	res=(res<<8) + (source&0xff); \
    }


uint32_t swap32(uint32_t source)
{
    uint32_t res;
    CONVERSION(4);
    return res;
}

uint64_t swap64(uint64_t source)
{
    uint64_t res;
    CONVERSION(8);
    return res;
}

#undef CONVERSION

#ifdef SELFTEST_MY_SWAP2

#include <stdio.h>

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
    printf("uint16: %04X <=> %04X\n",	 test.u16,swap16(test.u16));
    printf("uint32: %08X <=> %08X\n",	 test.u32,swap32(test.u32));
    printf("uint64: %016lX <=> %016lX\n",test.u64,swap64(test.u64));

    return 0;
}

#endif
