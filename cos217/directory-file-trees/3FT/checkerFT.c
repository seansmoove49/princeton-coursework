/*--------------------------------------------------------------------*/
/* checkerDT.c                                                        */
/* Author:                                                            */
/*--------------------------------------------------------------------*/

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "dynarray.h"
#include "checkerFT.h"


/* see checkerDT.h for specification */
boolean CheckerFT_Node_isValid(Node_T n) {
   return TRUE;
}

/*
   Performs a pre-order traversal of the tree rooted at n.
   Returns FALSE if a broken invariant is found and
   returns TRUE otherwise.

   You may want to change this function's return type or
   parameter list to facilitate constructing your checks.
   If you do, you should update this function comment.
*/
static boolean CheckerFT_treeCheck(Node_T n) {
   return TRUE;
}

/* see checkerDT.h for specification */
boolean CheckerFT_isValid(boolean isInit, Node_T root, size_t count) {
   return CheckerDT_treeCheck(root);
}
