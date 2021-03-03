#include "str.h"
#include <assert.h>
#include <stddef.h>

size_t Str_getLength(const char pcSrc[])
{
   size_t uLength = 0;
   assert(pcSrc != NULL);
   while (pcSrc[uLength] != '\0')
      uLength++;
   return uLength;
}


char *Str_copy(char pcDest[], const char pcSrc[])
{
    size_t i = 0;
    assert(pcSrc != NULL);
    assert(pcDest != NULL);
    while (pcSrc[i] != '\0'){
        pcDest[i] = pcSrc[i];
        i++;
    }
    pcDest[i] = '\0';
    return pcDest;
        
}

char *Str_concat(char pcDest[], const char pcSrc[])
{
    size_t i = 0;
    assert(pcSrc != NULL);
    assert(pcDest != NULL);
    size_t pcDestLen;
    pcDestLen = Str_getLength(pcDest);
    while (pcSrc[i]!='\0'){
        pcDest[i+pcDestLen] = pcSrc[i];
        i++;
    }
    pcDest[i+pcDestLen] = '\0';
    return pcDest;
}

int Str_compare(const char pcString1[], const char pcString2[]){
    size_t i = 0;
    assert(pcString1 != NULL);
    assert(pcString2 != NULL);
    while(pcString1[i]!='\0' && pcString2[i]!='\0'){
        if((pcString1[i] - pcString2[i])<0)
            return -1;
        else if ((pcString1[i] - pcString2[i])>0)
            return 1;   
        i++;
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


