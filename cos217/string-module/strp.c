#include "str.h"
#include <assert.h>
#include <stddef.h>

size_t Str_getLength(const char *pcSrc)
{
   const char *pcEnd;
   assert(pcSrc != NULL);
   pcEnd = pcSrc;
   while (*pcEnd != '\0')
      pcEnd++;
   return (size_t)(pcEnd - pcSrc);
}


char *Str_copy(char *pcDest, const char *pcSrc)
{
   char *start = pcDest;
    assert(pcSrc != NULL);
    assert(pcDest != NULL);
    while (*pcSrc != '\0'){
        *pcDest = *pcSrc;
        pcDest++;
        pcSrc++;
    }
    *pcDest = '\0';
    return start;
        
}

char *Str_concat(char *pcDest, const char *pcSrc)
{
    assert(pcSrc != NULL);
    assert(pcDest != NULL);
    char *pc = pcDest;
    while (*pc != '\0'){
       pc++;
    }
    while (*pcSrc != '\0'){
       *pc = *pcSrc;
       pc++;
       pcSrc++;
    }
    *pc = '\0';
    return pcDest;
}

int Str_compare(const char pcString1[], const char pcString2[]){
    assert(pcString1 != NULL);
    assert(pcString2 != NULL);
    while(*pcString1!='\0' && *pcString2!='\0'){
        if((*pcString1 - *pcString2)<0)
            return -1;
        else if ((*pcString1 - *pcString2)>0)
            return 1;   
        pcString1++;
        pcString2++;
    }
    return (Str_getLength(pcString1)-Str_getLength(pcString2));
}

char *Str_search(const char pcHaystack[], const char pcNeedle[]){
    size_t indexHaystack = 0;
    size_t indexNeedle = 0;
    size_t startIndex = 0;
    size_t numMatch = 0;
    char *pc = NULL;
    size_t needleLength = Str_getLength(pcNeedle);
    assert(pcHaystack != NULL);
    assert(pcNeedle != NULL);

    if (pcNeedle[indexNeedle] == '\0'){
        return (char*) pcHaystack;
    }
    while(pcHaystack[indexHaystack]!='\0' && pcNeedle[indexNeedle]!='\0'){
        if(pcNeedle[indexNeedle]==pcHaystack[indexHaystack]){
            if (numMatch==0){
                startIndex = indexHaystack;
            }
            numMatch++;
            indexNeedle++;
        }
        else{
            indexHaystack = indexHaystack-numMatch;
            numMatch = 0;
            indexNeedle = 0;
        }
        indexHaystack++;
        
    }
    if ((numMatch != 0) && (indexNeedle == needleLength)){
        return (char*) &pcHaystack[startIndex];
    }
    else{
        return NULL;
    }

}
