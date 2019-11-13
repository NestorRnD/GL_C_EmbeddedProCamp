/*              (version 2) header
 *  Function for conversion uint16, uint32 and uint64
 *  Little-Endian Memory Format <=> Big-Endian Memory Format
 *       (c) Nestor Tyshko, email:tyshko.n@gmail.com
 */

#ifndef MY_SWAP2_H
#define  MY_SWAP2_H

#include <stdint.h>

static inline uint16_t swap16(uint16_t word)
{
    return (word>>8)|(word<<8);
}
uint32_t swap32(uint32_t);
uint64_t swap64(uint64_t);

#endif