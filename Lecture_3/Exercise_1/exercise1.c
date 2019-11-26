#include <stdio.h>
#include <stdint.h>

/*
 * Function for copy strings from src to dest but no more then size-1 chars.
 * The dest string always ended with '\0'
 */
void myStrCp8(char *dest, const char *src, size_t size)
{
    while((size>1)&&(*src!='\0')){
//*
	*dest=*src;
	dest++;
	src++;
/*/ or all three commands in one line
	 *(dest++)=*(src++);
//*/
	size--;
    }
    *dest='\0';
}

// Next varian usable for 16 bit arch (for better performance)
void myStrCp16(char *dest, const char *src, size_t size)
{
    uint16_t *pSrc=(uint16_t *)src;
    uint16_t *pDest=(uint16_t *)dest;
    while((size>2)&&((*pSrc&0xFF)&&(*pSrc&0xFF00))){
	*(pDest++)=*(pSrc++);
	size-=2;
    }
    if(size>1) *pDest=*pSrc;
    *((char *)pDest +(size-1))='\0';
}

// Next varian usable for 32 bit arch (for better performance)
void myStrCp32(char *dest, const char *src, size_t size)
{
    uint32_t *pSrc=(uint32_t *)src;
    uint32_t *pDest=(uint32_t *)dest;
    while( (size>4) && ((*pSrc&0xFF) && (*pSrc&0xFF00) && (*pSrc&0xFF0000) && (*pSrc&0xFF000000)) ){
	*(pDest++)=*(pSrc++);
	size-=4;
    }
    if(size>3){
	*pDest=*pSrc;
	*((char *)pDest +(size-1))='\0';
    }else{
	dest=(char *)pDest;
	src=(char *)pSrc;
	while((size>1)&&(*src!='\0')){
	    *(dest++)=*(src++);
	    size--;
	}
	*dest='\0';
    }
}

#define TESTMYSTRCOPY(bits,size) \
    printf("Using %i bit copy function.\n",bits);\
    myStrCp##bits(dest,src1,size);\
    printf("     Source string: '%s'\n",src1);\
    printf("Destination string: '%s'\n",dest);\
    *dest='\0';\
    myStrCp##bits(dest,src2,size);\
    printf("     Source string: '%s'\n",src2);\
    printf("Destination string: '%s'\n",dest);\
    *dest='\0';\
    myStrCp##bits(dest,src3,size);\
    printf("     Source string: '%s'\n",src3);\
    printf("Destination string: '%s'\n",dest);\
    *dest='\0';\
    myStrCp##bits(dest,src4,size);\
    printf("     Source string: '%s'\n",src4);\
    printf("Destination string: '%s'\n\n",dest);\
    *dest='\0';


int main(void)
{
    char *src1="test string 1";
    char *src2="test string 12";
    char *src3="test string 123";
    char *src4="test string 1234";
    char dest[20];

    TESTMYSTRCOPY(8,20);
    TESTMYSTRCOPY(16,20);
    TESTMYSTRCOPY(32,20);

    printf("Now try with buffer size=13\n");

    TESTMYSTRCOPY(8,13);
    TESTMYSTRCOPY(16,13);
    TESTMYSTRCOPY(32,13);

    printf("Now try with buffer size=14\n");

    TESTMYSTRCOPY(8,14);
    TESTMYSTRCOPY(16,14);
    TESTMYSTRCOPY(32,14);

    printf("Now try with buffer size=15\n");

    TESTMYSTRCOPY(8,15);
    TESTMYSTRCOPY(16,15);
    TESTMYSTRCOPY(32,15);

    printf("Now try with buffer size=16\n");

    TESTMYSTRCOPY(8,16);
    TESTMYSTRCOPY(16,16);
    TESTMYSTRCOPY(32,16);

    return 0;
}