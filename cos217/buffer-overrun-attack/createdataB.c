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
   

   fclose(psFile);


   return 0;
}
