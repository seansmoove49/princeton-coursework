/*--------------------------------------------------------------------*/
/* createdataB.c                                                      */
/* Author: Sean Wang, Giao Vu Dinh                                    */
/*--------------------------------------------------------------------*/


#include <stdio.h>

/*--------------------------------------------------------------------*/

/*  */

int main(void)
{
   unsigned long ulData;
   FILE *psFile;
   psFile = fopen("data", "w");
   putc(0xef, psFile); /* Writes 11101111 */
putc(0xcd, psFile); /* Writes 11001101 */
putc(0xab, psFile); /* Writes 10101011 */
putc(0x89, psFile); /* Writes 10001001 */
putc(0x67, psFile); /* Writes 01100111 */
putc(0x45, psFile); /* Writes 01000101 */
putc(0x23, psFile); /* Writes 00100011 */
putc(0x01, psFile); /* Writes 00000001 */

   fclose(psFile);


   return 0;
}
