/*
 *  Inline function for conversion uint16, uint32 and uint64
 *  Little-Endian Memory Format <=> Big-Endian Memory Format
 *       (c) Nestor Tyshko, email:tyshko.n@gmail.com
 */

#ifndef MY_SWAP1_H
#define MY_SWAP1_H

#include <stdint.h>

static inline uint16_t swap16(uint16_t word)
{
    return
	(word>>8)|		// 2B => 1B
	((word&0xff)<<8);	// 1B => 2B
}

static inline uint32_t swap32(uint32_t dword)
{
    return
	(dword>>24)|		// 4B => 1B
	((dword>>8)&0xff00)|	// 3B => 2B
	((dword&0xff00)<<8)|	// 2B => 3B
	(dword<<24);		// 1B => 4B
}


// maybe not good idea to inline this function
static inline uint64_t swap64(uint64_t qword)
{
    return
	(qword>>56)|		// 8B => 1B
	((qword>>40)&0xff00)|	// 7B => 2B
	((qword>>24)&0xff0000)|	// 6B => 3B
	((qword>>8)&0xff000000)|// 5B => 4B
	((qword&0xff000000)<<8)|// 4B => 5B
	((qword&0xff0000)<<24)|	// 3B => 6B
	((qword&0xff00)<<40)|	// 2B => 7B
	(qword<<56);		// 1B => 8B
}

#endif