#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/*
 * Function strDigSel select all digits from
 * source string. The memory for resulting string is
 * dynamicaly allocated. Therefore it mast by free
 * when result was not needed!!!
 * !!! The input string mast end with '\0' in other case
 * !!! the beheviour is undefined.
 *
 *  (c) Nestor Tyshko, email:tyshko.n@gmail.com
 */

char *strDigSel(const char *source)
{
    char *p=source,*pres,*pp;
    size_t len=0;
    while(*p){
	if(isdigit(*p)) len++;
	p++;
    }
    pres=malloc(len+1);
    p=source;
    pp=pres;
    while(*p){
	if(isdigit(*p)){
	    *pp=*p;
	    pp++;
	}
	p++;
    }
    *pp='\0';
    return pres;
}

int main(void)
{
    char
	*testStr="a1vj2hhf3 h4jg5 6gh7gjj8hg9g",
	*resStr;
    resStr=strDigSel(testStr);
    printf("Input  string: %s\n"
	   "Output string: %s\n",
	   testStr, resStr
	);
    free(resStr);
    return 0;
}