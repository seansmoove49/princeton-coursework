/*--------------------------------------------------------------------*/
/* miniassembler.c                                                    */
/* Author: Bob Dondero, Donna Gabai                                   */
/*--------------------------------------------------------------------*/

#include "miniassembler.h"
#include <assert.h>
#include <stddef.h>

/*--------------------------------------------------------------------*/
/* Modify *puiDest in place,
   setting iNumBits starting at iDestStartBit (where 0 is
   the least significant bit) with bits taken from uiSrc,
   starting at iSrcStartBit.
   setField sets the appropriate bits in *puiDest to 1.
   setField never unsets any bits in *puiDest.                        */
static void setField(unsigned int uiSrc, int iSrcStartBit,
       unsigned int *puiDest, int iDestStartBit, int iNumBits)
{
   unsigned int uextractedShiftedBits;
   uextractedShiftedBits =  (((1 << iNumBits) - 1) & (uiSrc >> iSrcStartBit)) << iDestStartBit; 
   *puiDest = *puiDest | uextractedShiftedBits;

   

}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_mov(unsigned int uiReg, int iImmed)
{
   unsigned int uiInstr;

   /* Base Instruction Code */
   uiInstr = 0x52800000;

   /* register to be inserted in instruction */
   setField(uiReg, 0, &uiInstr, 0, 5);

   setField((unsigned int)(iImmed), 0, &uiInstr, 5, 16);

   return uiInstr;

}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_adr(unsigned int uiReg, unsigned long ulAddr,
   unsigned long ulAddrOfThisInstr)
{
   unsigned int uiInstr;
   unsigned int uiDisp;

   /* Base Instruction Code */
   uiInstr = 0x10000000;

   /* register to be inserted in instruction */
   setField(uiReg, 0, &uiInstr, 0, 5);

   /* displacement to be split into immlo and immhi and inserted */
   uiDisp = (unsigned int)(ulAddr - ulAddrOfThisInstr);

   setField(uiDisp, 0, &uiInstr, 29, 2);
   setField(uiDisp, 2, &uiInstr, 5, 19);

   return uiInstr;
}

/*--------------------------------------------------------------------*/


unsigned int MiniAssembler_strb(unsigned int uiFromReg,
   unsigned int uiToReg)
{
   unsigned int uiInstr;

   /* Base Instruction Code */
   uiInstr = 0x39000000;

   /* register to be inserted in instruction */
   setField(uiFromReg, 0, &uiInstr, 0, 5);

   setField(uiToReg, 0, &uiInstr, 5, 5);

   return uiInstr;

}

/*--------------------------------------------------------------------*/


unsigned int MiniAssembler_b(unsigned long ulAddr,
   unsigned long ulAddrOfThisInstr)
{
   unsigned int uiInstr;
   unsigned int uiDisp;

   /* Base Instruction Code */
   uiInstr = 0x14000000;

   uiDisp = (unsigned int)(ulAddr - ulAddrOfThisInstr)>>2;

   /* register to be inserted in instruction */
   setField(uiDisp, 0, &uiInstr, 0, 26);

   return uiInstr;
   

}
