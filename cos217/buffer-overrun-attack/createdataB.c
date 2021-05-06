/*--------------------------------------------------------------------*/
/* createdataB.c                                                      */
/* Author: Sean Wang, Giao Vu Dinh                                    */
/*--------------------------------------------------------------------*/


#include <stdio.h>
#include <string.h>

/*--------------------------------------------------------------------*/

/*  */

int main(void)
{
   FILE *psFile;
   char *psName;
   int i;
   unsigned int uiData;
   uiData = 0x400858; 
   psFile = fopen("dataB", "w");
   
   psName = "Sean Wang";
   for (i = 0; i<strlen(psName); i++){
       fprintf(psFile, "%c", psName[i]);
   }
   fprintf(psFile, "%c", 0x00);
   for (i = 0; i<(48-(strlen(psName)+1)); i++){
       fprintf(psFile, "%c", 0x00);
   }
   
   unsigned int uiData;
   uiData = 0x01234567;
   fwrite(&uiData, sizeof(unsigned int), 1, psFile);

/* Writes 01100111 01000101 00100011 00000001 */

   fclose(psFile);


   return 0;
}
