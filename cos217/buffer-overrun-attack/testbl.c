/*--------------------------------------------------------------------*/
/* createdataAplus.c                                                      */
/* Author: Sean Wang, Giao Vu Dinh                                    */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include "miniassembler.h"
enum {BUFSIZE = 48};

/*--------------------------------------------------------------------*/


/* Does not accept any command-line arguments or read text from stdin. 
   Writes a sequence of characters to file dataA designed to perform a 
   "A+" buffer overrun attack on the grader executable. The sequence of 
   characters includes the student name, null bytes, and binary code.
   Returns 0. */

int main(void)
{
   unsigned int i;
   unsigned int uiInstr;
   unsigned long ulData;
   char* psName;
   FILE *psFile;
   psFile = fopen("blTest", "w");

   uiInstr = MiniAssembler_bl(0x400600, 0x420064);
   printf("%u", uiInstr);
   fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

   fclose(psFile);

   return 0;
}