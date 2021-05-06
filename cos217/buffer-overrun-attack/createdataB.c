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
   
   unsigned int uiData;
   uiData = 0x01234567;
   fwrite(&uiData, sizeof(unsigned int), 1, psFile);

/* Writes 01100111 01000101 00100011 00000001 */

   fclose(psFile);


   return 0;
}
