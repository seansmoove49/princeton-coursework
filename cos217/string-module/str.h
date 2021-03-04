/*--------------------------------------------------------------------*/
/* str.h                                                              */
/* Author: Sean Wang                                                  */
/*--------------------------------------------------------------------*/


#include <stddef.h>
#ifndef STR_INCLUDED
#define STR_INCLUDED


/* Return the length of string pcSrc 
excluding the terminating null byte. */
size_t Str_getLength(const char pcSrc[]);

/* Copies the string pointed to by pcSrc to pcDest.
Returns a pointer to the destination string pcDest. */
char *Str_copy(char pcDest[], const char pcSrc[]);

/* Appends the string pcSrc to the string pcDest.
Returns a pointer to the resulting string pcDest. */
char *Str_concat(char pcDest[], const char pcSrc[]);

/* Compares two strings pcString1 and pcString2. 
Returns an integer less than, equal to, or greater than 
zero if pcString1 is found, respectively, to be less than, 
to match, or be greater than pcString2.*/

int Str_compare(const char pcString1[], const char pcString2[]);

/* Finds the first occurence of the substring pcNeedle in the
string pcHaystack. Returns a pointer to the beginning of the
substring in pcHaystack. Return NULLL if not found. */
char *Str_search(const char pcHaystack[], const char pcNeedle[]);

#endif