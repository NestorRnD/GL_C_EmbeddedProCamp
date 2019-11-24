#include <stdio.h>

/*
 * Function for copy strings from src to dest but no more then size-1 chars.
 * The dest string always ended with '\0'
 */
void myStrCp(char *dest, const char *src, size_t size)
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
    if(size>0)
	*dest='\0';
}

int main(void)
{
    char *src="test string";
    char dest[80];

    myStrCp(dest,src,80);
    printf("     Source string: '%s'\n",src);
    printf("Destination string: '%s'\n",dest);

    return 0;
}