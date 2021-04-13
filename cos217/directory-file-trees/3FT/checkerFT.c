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
   size_t i, j, c;
   
   char *strChild, *strSibling;
   char *tempChildToken, *tempSiblingToken; 
   char *finalChildToken, *finalSiblingToken, *delimiter; 
   delimiter = "/";

   /* Sample check: a NULL pointer is not a valid node */
   if(n == NULL) {
      fprintf(stderr, "A node is a NULL pointer\n");
      return FALSE;
   }

   /* Sample check: a node with a path field that is
   a NULL pointer is not a valid node */
   if(Node_getPath(n) == NULL) {
      fprintf(stderr, "Node has path field that is a NULL pointer\n");
      return FALSE;
   }

   /* Sample check: a file node cannot have children */
   if (Node_isFile(n) && Node_getNumChildren(n) != 0) {
      fprintf(stderr, "File node has children\n");
      return FALSE;
   }
   
   /* Sample check: a directory node cannot have contents */
   if (!Node_isFile(n) && Node_getFileContents(n) != NULL) {
      fprintf(stderr, "Directory node has contents\n");
      return FALSE;
   }

   parent = Node_getParent(n);
   if(parent != NULL) {
      npath = Node_getPath(n);

      /* Sample check that parent's path must be prefix of n's path */
      ppath = Node_getPath(parent);
      i = strlen(ppath);
      j = strlen(npath);
      if(strncmp(npath, ppath, i)) {
         fprintf(stderr, "P's path is not a prefix of C's path\n");
         return FALSE;
      }
      else{
         /* Sample check that n's path is not the same as its parent's path */
         if (j==i){
            fprintf(stderr, "child: %s \n", Node_toString(n));
            fprintf(stderr, "parent: %s \n", Node_toString(parent));
            fprintf(stderr, "C's path is the same as P's path\n");
            return FALSE;
         }
      }
      
      /* Sample check that n's path after parent's path + '/'
         must have no further '/' characters */
      rest = npath + i;
      rest++;
      if(strstr(rest, "/") != NULL) {
         fprintf(stderr, "C's path has grandchild of P's path\n");
         return FALSE;
      }
   }
   
   /* Sample check: check if child node 
      has a neighboring sibling node whose path is less 
      than the child node's path (not in sorted order)*/

   /*
   for(c = 0; c < Node_getNumChildren(n); c++)
      {
         Node_T child = Node_getChild(n, c);
         if (c+1 < Node_getNumChildren(n))
         {
            
            Node_T sibling = Node_getChild(n, c+1);
            strChild = (char *)malloc(strlen(Node_getPath(child)+1));
            if (strChild == NULL)
            {
               fprintf(stderr, "There is not sufficient memory!\n");
               exit(EXIT_FAILURE);
            }
            strSibling = (char *)malloc(strlen(Node_getPath(sibling)+1));
            if (strSibling == NULL)
            {
               fprintf(stderr, "There is not sufficient memory!\n");
               exit(EXIT_FAILURE);
            }
            strcpy(strChild, Node_getPath(child));
            tempChildToken = strtok(strChild, delimiter);

            while (tempChildToken!=NULL)
            {
               finalChildToken = tempChildToken;
               tempChildToken = strtok(NULL, delimiter);

            }

            strcpy(strSibling, Node_getPath(sibling));

            tempSiblingToken = strtok(strSibling, delimiter);
            

            while (tempSiblingToken!=NULL)
            {
               finalSiblingToken = tempSiblingToken;
               tempSiblingToken = strtok(NULL, delimiter);
            }

            if (strcmp(finalChildToken, finalSiblingToken)>=0)
            {
               fprintf(stderr, "The children are not stored in sorted order\n");
               free(strSibling);
               free(strChild);
               return FALSE;
            }
            free(strSibling);
            free(strChild);
         }
      }
      */

   return TRUE;
}

/*
   Performs a pre-order traversal of the tree rooted at n.
   Returns FALSE if a broken invariant is found and
   returns TRUE otherwise. 
*/
static boolean CheckerFT_treeCheck(Node_T n, size_t *pnumNodes) 
{
   size_t c;
   

   if(n != NULL) 
   {
      /* Sample check on each non-root node: node must be valid */
      /* If not, pass that failure back up immediately */
      if(!CheckerFT_Node_isValid(n))
         return FALSE;
      *pnumNodes = *pnumNodes + 1;
      
      /* Sample check: check if child node 
      has a parent field equal to NULL (not a valid node)*/
      if(strchr(Node_getPath(n), '/')!=NULL)
      {
            if (Node_getParent(n)==NULL)
            {
               fprintf(stderr, "The child node has a parent " 
               "field equal to NULL\n");
               return FALSE;
            }
      }

      for(c = 0; c < Node_getNumChildren(n); c++)
      {
         Node_T child = Node_getChild(n, c);
         
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
   if(!isInit)
   {
      if (root != NULL) {
         fprintf(stderr, "Not initialized, but root is not NULL\n");
         return FALSE;
      }
      if(count != 0) {
         fprintf(stderr, "Not initialized, but count is not 0\n");
         return FALSE;
      }
   }
   
   if(isInit)
   {
      if (root != NULL){
         /* Sample check on a top-level data structure invariant:
         if the DT is  initialized and the root is not NULL, its count 
         should be greater than 0 */
         if (count == 0) {
            fprintf(stderr, "Initialized with a root node, but count is 0\n");
            return FALSE;
         }
         /* Sample check on a top-level data structure invariant:
         if the DT is  initialized and the root is not NULL, 
         the root node should have a parent field  equal to NULL */
         if (Node_getParent(root)!=NULL)
         {
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
      if (root == NULL){
         if (count != 0) {
            fprintf(stderr, "Initialized without a root node, but count is not 0\n");
            return FALSE;
         }
      }
   }
      

   /* Now checks invariants recursively at each node from the root. */
   treeCheck = CheckerFT_treeCheck(root, &numNodes);
   if (numNodes!=count){
      fprintf(stderr, "The count does not match the number of nodes\n");
      return FALSE;
   }

   return treeCheck;
}