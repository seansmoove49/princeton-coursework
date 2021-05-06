/*--------------------------------------------------------------------*/
/* createdataB.c                                                      */
/* Author: Sean Wang, Giao Vu Dinh                                    */
/*--------------------------------------------------------------------*/


#include <stdio.h>

/*--------------------------------------------------------------------*/

/*  */

int main(void)
{
   FILE *psFile;
   psFile = fopen("data", "w");
   unsigned long ulData;

   ulData = 0x0123456789abcdef;
   fwrite(&ulData, sizeof(unsigned long), 1, psFile);

   fclose(psFile);


   return 0;
}
