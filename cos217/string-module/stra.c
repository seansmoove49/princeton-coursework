/*--------------------------------------------------------------------*/
/* stra.c                                                             */
/* Author: Sean Wang                                                  */
/*--------------------------------------------------------------------*/

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
    size_t pcDestLen;
    assert(pcSrc != NULL);
    assert(pcDest != NULL);
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
    int string1Length;
    int string2Length;
    assert(pcString1 != NULL);
    assert(pcString2 != NULL);
    string1Length = (int) Str_getLength(pcString1);
    string2Length = (int) Str_getLength(pcString2);
    while(pcString1[i]!='\0' && pcString2[i]!='\0'){
        if((int)(pcString1[i] - pcString2[i])<0)
            return -1;
        else if ((int)(pcString1[i] - pcString2[i])>0)
            return 1;   
        i++;
    }
    /* covers the cases where every char is the same */
    return (string1Length-string2Length);
}

char *Str_search(const char pcHaystack[], const char pcNeedle[]){
    size_t indexHaystack = 0;
    size_t indexNeedle = 0;
    /* startIndex helps track the beginning of the substring 
    in pcHaystack*/
    size_t startIndex = 0;
    /* numMatches is a counter for consecutive char matches */
    size_t numMatch = 0;
    size_t needleLength;

    assert(pcHaystack != NULL);
    assert(pcNeedle != NULL);

    needleLength = Str_getLength(pcNeedle);

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
            /* moves the index of pcHaystack back */
            indexHaystack = indexHaystack-numMatch;
            numMatch = 0;
            indexNeedle = 0;
        }
        indexHaystack++;
    }
    if ((numMatch != 0) && (indexNeedle == needleLength)){
        return (char*) &pcHaystack[startIndex];
    }
    return NULL;
    

}


