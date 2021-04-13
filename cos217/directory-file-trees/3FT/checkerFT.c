/*--------------------------------------------------------------------*/
/* checkerFT.c                                                        */
/* Author: Sean Wang and Giao Vu Dinh                                 */
/*--------------------------------------------------------------------*/

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dynarray.h"
#include "checkerFT.h"


/* see checkerFT.h for specification */
boolean CheckerFT_Node_isValid(Node_T n) {
   Node_T parent;
   const char* npath;
   const char* ppath;
   const char* rest;
   size_t numChildren = 0;
   size_t i, c;

   /* Sample check: a NULL pointer is not a valid node */
   if (n == NULL) {
      fprintf(stderr, "A node is a NULL pointer\n");
      return FALSE;
   }

   /* Sample check: a node with a path field that is
   a NULL pointer is not a valid node */
   if (Node_getPath(n) == NULL) {
      fprintf(stderr, "Node has path field that is a NULL pointer\n");
      return FALSE;
   }

   numChildren += Node_getNumDirChildren(n);
   numChildren += Node_getNumFileChildren(n);

   /* Sample check: a file node cannot have children */
   if (Node_isFile(n) && numChildren != 0) {
      fprintf(stderr, "File node has children\n");
      return FALSE;
   }
   
   /* Sample check: a directory node cannot have contents */
   if (!Node_isFile(n) && Node_getFileContents(n) != NULL) {
      fprintf(stderr, "Directory node has contents\n");
      return FALSE;
   }

   parent = Node_getParent(n);
   if (parent != NULL) {
      npath = Node_getPath(n);

      /* Sample check that parent's path must be prefix of n's path */
      ppath = Node_getPath(parent);
      i = strlen(ppath);
      if (strncmp(npath, ppath, i)) {
         fprintf(stderr, "P's path is not a prefix of C's path\n");
         return FALSE;
      }
      
      /* Sample check that n's path after parent's path + '/'
         must have no further '/' characters */
      rest = npath + i;
      rest++;
      if (strstr(rest, "/") != NULL) {
         fprintf(stderr, "C's path has grandchild of P's path\n");
         return FALSE;
      }
   }
   
   /* Sample check: check if child node 
      has a neighboring sibling node whose path is less 
      than the child node's path (not in sorted order)*/
   for(c = 0; c < Node_getNumDirChildren(n); c++) {
      Node_T child = Node_getDirChild(n, c);
      if (c+1 < Node_getNumDirChildren(n)) {
         Node_T sibling = Node_getDirChild(n, c+1);

         if (Node_compare(child, sibling) >= 0) {
            fprintf(stderr, "The children are not stored"
                    " in sorted order\n");
            return FALSE;
         }
      }
   }

   /* repeat the check for the child file nodes */
   for(c = 0; c < Node_getNumFileChildren(n); c++) {
      Node_T child = Node_getFileChild(n, c);
      if (c+1 < Node_getNumFileChildren(n)) {
         Node_T sibling = Node_getFileChild(n, c+1);

         if (Node_compare(child, sibling)>=0) {
            fprintf(stderr, "The children are not stored"
                    " in sorted order\n");
            return FALSE;
         }
      }
   }

   return TRUE;
}

/*
   Performs a pre-order traversal of the tree rooted at n.
   Returns FALSE if a broken invariant is found and
   returns TRUE otherwise. 
   Updates pnumNodes to reflect the number of nodes in the file tree. 
*/
static boolean CheckerFT_treeCheck(Node_T n, size_t *pnumNodes) 
{
   size_t c;

   assert(pnumNodes != NULL);

   if (n != NULL) {
      /* Sample check on each non-root node: node must be valid */
      /* If not, pass that failure back up immediately */
      if (!CheckerFT_Node_isValid(n))
         return FALSE;
      *pnumNodes = *pnumNodes + 1;
      
      /* Sample check: check if child node 
      has a parent field equal to NULL (not a valid node)*/
      if (strchr(Node_getPath(n), '/') != NULL) {
            if (Node_getParent(n) == NULL) {
               fprintf(stderr, "The child node has a parent " 
                       "field equal to NULL\n");
               return FALSE;
            }
      }

      for (c = 0; c < Node_getNumDirChildren(n); c++) {
         Node_T child = Node_getDirChild(n, c);
         
         /* if recurring down one subtree results in a failed check
            farther down, passes the failure back up immediately */
         if(!CheckerFT_treeCheck(child, pnumNodes))
            return FALSE;
      }

      for (c = 0; c < Node_getNumFileChildren(n); c++) {
         Node_T child = Node_getFileChild(n, c);
         
         /* if recurring down one subtree results in a failed check
            farther down, passes the failure back up immediately */
         if(!CheckerFT_treeCheck(child, pnumNodes))
            return FALSE;
      }
   }
   return TRUE;
}

/* see checkerFT.h for specification */
boolean CheckerFT_isValid(boolean isInit, Node_T root, size_t count) {
   boolean treeCheck;
   size_t numNodes;

   numNodes = 0;

   /* Sample check on a top-level data structure invariant:
      if the DT is not initialized, its count should be 0
      and its root should be NULL. */
   if (!isInit) {
      if (root != NULL) {
         fprintf(stderr, "Not initialized, but root is not NULL\n");
         return FALSE;
      }
      if (count != 0) {
         fprintf(stderr, "Not initialized, but count is not 0\n");
         return FALSE;
      }
   }
   
   if(isInit) {
      if (root != NULL) {
         /* Sample check on a top-level data structure invariant:
         if the DT is  initialized and the root is not NULL, its count 
         should be greater than 0 */
         if (count == 0) {
            fprintf(stderr, "Initialized with a root node,"
                            " but count is 0\n");
            return FALSE;
         }
         /* Sample check on a top-level data structure invariant:
         if the DT is  initialized and the root is not NULL, 
         the root node should have a parent field  equal to NULL */
         if (Node_getParent(root) != NULL) {
            fprintf(stderr, "The root node has a parent " 
                    "field not equal to NULL\n");
            return FALSE;
         }  

         /* Sample check on a top-level data structure invariant:
            the root node cannot be a file. */
         if (Node_isFile(root)) {
            fprintf(stderr, "The root cannot be a file\n");
            return FALSE;
         }
      }
      /* Sample check on a top-level data structure invariant:
      if the DT is  initialized and the root is NULL, its count 
      should be 0 */
      if (root == NULL) {
         if (count != 0) {
            fprintf(stderr, "Initialized without a root node, "
                    "but count is not 0\n");
            return FALSE;
         }
      }
   }
      

   /* Now checks invariants recursively at each node from the root. */
   treeCheck = CheckerFT_treeCheck(root, &numNodes);
   if (numNodes != count) {
      fprintf(stderr, "The count does not match the number of nodes\n");
      return FALSE;
   }

   return treeCheck;
}