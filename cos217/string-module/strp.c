/*--------------------------------------------------------------------*/
/* strp.c                                                             */
/* Author: Sean Wang                                                  */
/*--------------------------------------------------------------------*/


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
   char *pc;
   assert(pcSrc != NULL);
   assert(pcDest != NULL);
   pc = pcDest;
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
   int string1Length;
   int string2Length;
    assert(pcString1 != NULL);
    assert(pcString2 != NULL);
    string1Length = (int) Str_getLength(pcString1);
    string2Length = (int) Str_getLength(pcString2);
    while(*pcString1!='\0' && *pcString2!='\0'){
        if((int)(*pcString1 - *pcString2)<0)
            return -1;
        else if ((int)(*pcString1 - *pcString2)>0)
            return 1;   
        pcString1++;
        pcString2++;
    }
    return (string1Length-string2Length);
}

/* Compares the first n chars of two strings 
pcString1 and pcString2. Returns an integer less than, equal to, 
or greater than zero if pcString1 is found, respectively, to be less than, 
to match, or be greater than pcString2.*/
static int Strn_compare(const char pcString1[], const char pcString2[], size_t n){
    size_t count = 0;
    assert(pcString1 != NULL);
    assert(pcString2 != NULL);
    while(count!=n){
        if((int)(*pcString1 - *pcString2)<0)
            return -1;
        else if ((int)(*pcString1 - *pcString2)>0)
            return 1;   
        pcString1++;
        pcString2++;
        count++;
    }
    return 0;
}


char *Str_search(const char *pcHaystack, const char *pcNeedle){
   size_t needleLength;
   assert(pcHaystack != NULL);
   assert(pcNeedle != NULL);
   needleLength = Str_getLength(pcNeedle);
   if (*pcNeedle == '\0'){
        return (char*) pcHaystack;
    }
   while (*pcHaystack!='\0'){
      if (*pcHaystack == *pcNeedle){
         /* Str_compare won't work as it will return a
         non-zero value in cases like: cd (haystack), c (needle)*/
          if (Strn_compare(pcHaystack, pcNeedle, needleLength)==0){
           return (char*) pcHaystack;
          }
          
      }
        pcHaystack++;
    }
    return NULL;

}
