/*--------------------------------------------------------------------*/
/* ft.c                                                               */
/* Author: Sean Wang '24 and Giao Vu Dinh '24                         */
/*--------------------------------------------------------------------*/

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "a4def.h"
#include "dynarray.h"
#include "ft.h"
#include "node.h"
#include "checkerFT.h"

/* A File Tree is an AO with 3 state variables: */
/* a flag for if it is in an initialized state (TRUE) or not (FALSE) */
static boolean isInitialized;
/* a pointer to the root node in the hierarchy */
static Node_T root;
/* a count of the number of nodes in the hierarchy */
static size_t count;

/*--------------------------------------------------------------------*/

/* Starting at the parameter curr, traverses as far down the hierarchy
   as possible while still matching the path parameter. 
   
   Returns a pointer to the farthest matching node down the path, or 
   NULL if there is no node in curr's hierarchy that matches a prefix
   of that path. */

static Node_T FT_traversePathFrom(char* path, Node_T curr) {
   Node_T found;
   size_t i;

   assert(path != NULL);

   if (curr == NULL) return NULL;

   else if (!strcmp(path, Node_getPath(curr)))
      return curr;

   /* theoretically our checker should make sure that files never have
      children, so that's not something we need to take care of here */

   else if (!strncmp(path, Node_getPath(curr), 
            strlen(Node_getPath(curr)))) {
      for (i = 0; i < Node_getNumChildren(curr); i++) {
         found = FT_traversePathFrom(path, Node_getChild(curr, i));
         if (found != NULL)
            return found;
      }
      return curr;
   }
   return NULL;
}

/*--------------------------------------------------------------------*/

static int FT_insertRestOfPath(char* path, Node_T parent, 
                        boolean isFile, void* contents, size_t length) {
   Node_T curr = parent; 
   Node_T firstNew = NULL;
   Node_T new;

   char* copyPath;
   char* restPath = path;
   char* dirToken;
   char* tempToken;

   int result;
   size_t newCount = 0;

   assert(path != NULL);

   if (curr == NULL) {
      if (root != NULL) {
         return CONFLICTING_PATH;
      }
   } else {
      if (!strcmp(path, Node_getPath(curr)))
         return ALREADY_IN_TREE;

      restPath += (strlen(Node_getPath(curr)) + 1);
   }

   if (parent != NULL && Node_isFile(parent))
      return NOT_A_DIRECTORY;

   copyPath = malloc(strlen(restPath) + 1);
   if (copyPath == NULL)
      return MEMORY_ERROR;
   strcpy(copyPath, restPath);
   dirToken = strtok(copyPath, "/");

   while (dirToken != NULL) {
      tempToken = dirToken;
      dirToken = strtok(NULL, "/");

      /* last node is a file */
      if (isFile && dirToken == NULL) {
         new = Node_create(tempToken, curr, TRUE, contents, length);
      } else {
         /* creating a directory node */
      new = Node_create(tempToken, curr, FALSE, NULL, 0);
      }
      newCount++;

      if (firstNew == NULL)
         firstNew = new;
      else {
         /* ft link parent to child code with curr and new as params */
         if (Node_linkChild(curr, new) != SUCCESS) {
            (void) Node_destroy(new);
            (void) Node_destroy(firstNew);
            free(copyPath);
            return PARENT_CHILD_ERROR;
         }
      }

      if (new == NULL) {
         (void) Node_destroy(firstNew);
         free(copyPath);
         return MEMORY_ERROR;
      }

      curr = new;
   }

   free(copyPath);

   if (parent == NULL) {
      root = firstNew;
      count = newCount;
      return SUCCESS;
   }
   else {
      result = Node_linkChild(parent, firstNew);
      if (result == SUCCESS) 
         count += newCount;
      else
         Node_destroy(firstNew);
      
      return result;
   }
}

/*--------------------------------------------------------------------*/

/*
   Inserts a new directory into the tree at path, if possible.
   Returns SUCCESS if the new directory is inserted.
   Returns INITIALIZATION_ERROR if not in an initialized state.
   Returns CONFLICTING_PATH if path is not underneath existing root.
   Returns NOT_A_DIRECTORY if a proper prefix of path exists as a file.
   Returns ALREADY_IN_TREE if the path already exists (as dir or file).
   Returns PARENT_CHILD_ERROR if a new child cannot be added in path.
   Returns MEMORY_ERROR if unable to allocate sufficient memory.
*/

int FT_insertDir(char *path) {
   Node_T curr;
   int result;

   assert(CheckerFT_isValid(isInitialized, root, count));
   assert(path != NULL);

   if (!isInitialized)
      return INITIALIZATION_ERROR;

   curr = FT_traversePathFrom(path, root);
   result = FT_insertRestOfPath(path, curr, FALSE, NULL, 0);
   assert(CheckerFT_isValid(isInitialized, root, count));

   return result;
}

/*--------------------------------------------------------------------*/

boolean FT_containsDir(char *path) {
   Node_T curr;
   boolean result = TRUE;
   
   assert(CheckerFT_isValid(isInitialized, root, count));
   assert(path != NULL);

   if (!isInitialized)
      return FALSE;

   curr = FT_traversePathFrom(path, root);

   if (curr == NULL)
      result = FALSE;
   else if (Node_isFile(curr))
      result = FALSE;
   else if (strcmp(path, Node_getPath(curr)))
      result = FALSE;

   assert(CheckerFT_isValid(isInitialized, root, count));
   return result;
}

/*--------------------------------------------------------------------*/
/*
   Destroys the entire hierarchy of nodes rooted at curr,
   including curr itself.
*/
static void FT_removePathFrom(Node_T curr) {
   if(curr != NULL) {
      count -= Node_destroy(curr);
   }
}

/*--------------------------------------------------------------------*/
/*
  Removes the directory hierarchy rooted at path starting from
  curr. If curr is the data structure's root, root becomes NULL.
  Returns NO_SUCH_PATH if curr is not the node for path,
  and SUCCESS otherwise.
 */
static int FT_rmPathAt(char* path, Node_T curr) {

   Node_T parent;

   assert(path != NULL);
   assert(curr != NULL);

   parent = Node_getParent(curr);

   if(!strcmp(path,Node_getPath(curr))) {
      if(parent == NULL)
         root = NULL;
      else
         Node_unlinkChild(parent, curr);

      FT_removePathFrom(curr);

      return SUCCESS;
   }
   else
      return NO_SUCH_PATH;

}

/*--------------------------------------------------------------------*/

int FT_rmDir(char *path) {
   Node_T curr;
   int result;

   assert(CheckerFT_isValid(isInitialized,root,count));
   assert(path != NULL);

   if(!isInitialized)
      return INITIALIZATION_ERROR;

   curr = FT_traversePathFrom(path, root);
   if(curr == NULL)
      result =  NO_SUCH_PATH;
   else if (Node_isFile(curr)==TRUE){
      result  = NOT_A_DIRECTORY;
   }
   else{
      result = FT_rmPathAt(path, curr);
   }
      

   assert(CheckerFT_isValid(isInitialized,root,count));
   return result;
}

/*--------------------------------------------------------------------*/

int FT_insertFile(char *path, void *contents, size_t length) {
   Node_T curr;
   int result;

   assert(CheckerFT_isValid(isInitialized, root, count));
   assert(path != NULL);

   if (!isInitialized)
      return INITIALIZATION_ERROR;

   /* a file can't be the root */
   if (!strstr(path, "/"))
      return CONFLICTING_PATH;

   curr = FT_traversePathFrom(path, root);
   result = FT_insertRestOfPath(path, curr, TRUE, contents, length);
   assert(CheckerFT_isValid(isInitialized, root, count));

   return result;
}

/*--------------------------------------------------------------------*/

boolean FT_containsFile(char *path) {
   Node_T curr;
   boolean result = TRUE;
   
   assert(CheckerFT_isValid(isInitialized, root, count));
   assert(path != NULL);

   if (!isInitialized)
      return FALSE; 

   curr = FT_traversePathFrom(path, root);

   if (curr == NULL)
      result = FALSE;
   else if (!Node_isFile(curr))
      result = FALSE;
   else if (strcmp(path, Node_getPath(curr)))
      result = FALSE;

   assert(CheckerFT_isValid(isInitialized, root, count));
   return result;
}

/*--------------------------------------------------------------------*/

int FT_rmFile(char *path) {
   Node_T curr, parent;

   assert(CheckerFT_isValid(isInitialized,root,count));
   assert(path != NULL);

   if(!isInitialized)
      return INITIALIZATION_ERROR;

   curr = FT_traversePathFrom(path, root);
   if(curr == NULL)
      return NO_SUCH_PATH;
   else if (Node_isFile(curr)==FALSE){
      return NOT_A_FILE;
   }
   else if (strcmp(Node_getPath(curr), path)) {
      return NO_SUCH_PATH;
   }
   
   parent = Node_getParent(curr);
   Node_unlinkChild(parent, curr);
   count -= Node_destroy(curr);
   

   assert(CheckerFT_isValid(isInitialized,root,count));
   return SUCCESS;
}

/*--------------------------------------------------------------------*/

void *FT_getFileContents(char *path) {
   Node_T curr;
   
   assert(CheckerFT_isValid(isInitialized, root, count));
   assert(path != NULL);

   if (!isInitialized)
      return NULL;

   curr = FT_traversePathFrom(path, root);

   if (curr == NULL)
      return NULL;
   else if (!Node_isFile(curr))
      return NULL;
   else if (strcmp(path, Node_getPath(curr)))
      return NULL;

   assert(CheckerFT_isValid(isInitialized, root, count));

   return Node_getFileContents(curr);
}

/*--------------------------------------------------------------------*/

void *FT_replaceFileContents(char *path, void *newContents,
                             size_t newLength) {
   Node_T curr;
   void *oldContents;
   
   assert(CheckerFT_isValid(isInitialized, root, count));
   assert(path != NULL);

   if (!isInitialized)
      return NULL;

   curr = FT_traversePathFrom(path, root);

   if (curr == NULL)
      return NULL;
   else if (!Node_isFile(curr))
      return NULL;
   else if (strcmp(path, Node_getPath(curr)))
      return NULL;

   oldContents = Node_assignContents(curr, newContents, newLength);
   assert(CheckerFT_isValid(isInitialized, root, count));

   return oldContents;                         
}

/*--------------------------------------------------------------------*/

/*
  Returns SUCCESS if path exists in the hierarchy,
  returns NO_SUCH_PATH if it does not, and
  returns INITIALIZATION_ERROR if the structure is not initialized.
  When returning SUCCESSS,
  if path is a directory: *type is set to FALSE, *length is unchanged
  if path is a file: *type is set to TRUE, and
                     *length is set to the length of file's contents.
  When returning a non-SUCCESS status, *type and *length are unchanged.
 */

int FT_stat(char *path, boolean *type, size_t *length) {
   Node_T curr;

   assert(CheckerFT_isValid(isInitialized,root,count));
   assert(path != NULL);

   if(!isInitialized)
      return INITIALIZATION_ERROR;

   curr = FT_traversePathFrom(path, root);
   if(curr == NULL)
      return NO_SUCH_PATH;
   else if (strcmp(path, Node_getPath(curr)))
      return NO_SUCH_PATH;
   else if (Node_isFile(curr)==FALSE){
      *type = FALSE;
   }
   else if (Node_isFile(curr)==TRUE){
      *type = TRUE;
      *length = Node_getLength(curr);
   }
   
   return SUCCESS;
}


/*--------------------------------------------------------------------*/

int FT_init(void) {
   assert(CheckerFT_isValid(isInitialized, root, count));
   if (isInitialized)
      return INITIALIZATION_ERROR;

   isInitialized = 1;
   root = NULL;
   count = 0;
   assert(CheckerFT_isValid(isInitialized, root, count));
   return SUCCESS;
}

/*--------------------------------------------------------------------*/

int FT_destroy(void) {
   assert(CheckerFT_isValid(isInitialized,root,count));
   if(!isInitialized)
      return INITIALIZATION_ERROR;
   FT_removePathFrom(root);
   root = NULL;
   isInitialized = 0;
   assert(CheckerFT_isValid(isInitialized,root,count));
   return SUCCESS;
}

/*--------------------------------------------------------------------*/

/*
   Performs a pre-order traversal of the tree rooted at n,
   inserting each payload to DynArray_T d beginning at index i.
   Returns the next unused index in d after the insertion(s).
*/
static size_t FT_preOrderTraversal(Node_T n, DynArray_T d, size_t i) {
   size_t c;

   assert(d != NULL);

   if(n != NULL) {
      (void) DynArray_set(d, i, Node_getPath(n));
      i++;
      for(c = 0; c < Node_getNumChildren(n); c++)
         i = FT_preOrderTraversal(Node_getChild(n, c), d, i);
   }
   return i;
}

/*
   Alternate version of strlen that uses pAcc as an in-out parameter
   to accumulate a string length, rather than returning the length of
   str, and also always adds one more in addition to str's length.
*/
static void FT_strlenAccumulate(char* str, size_t* pAcc) {
   assert(pAcc != NULL);

   if(str != NULL)
      *pAcc += (strlen(str) + 1);
}

/*
   Alternate version of strcat that inverts the typical argument
   order, appending str onto acc, and also always adds a newline at
   the end of the concatenated string.
*/
static void FT_strcatAccumulate(char* str, char* acc) {
   assert(acc != NULL);

   if(str != NULL)
      strcat(acc, str); strcat(acc, "\n");
}

/*--------------------------------------------------------------------*/

char *FT_toString(void) {
   DynArray_T nodes;
   size_t totalStrlen = 1;
   char* result = NULL;

   assert(CheckerFT_isValid(isInitialized,root,count));

   if(!isInitialized)
      return NULL;

   nodes = DynArray_new(count);
   (void) FT_preOrderTraversal(root, nodes, 0);

   DynArray_map(nodes, (void (*)(void *, void*)) FT_strlenAccumulate, 
                        (void*) &totalStrlen);

   result = malloc(totalStrlen);
   if(result == NULL) {
      DynArray_free(nodes);
      assert(CheckerFT_isValid(isInitialized,root,count));
      return NULL;
   }
   *result = '\0';

   DynArray_map(nodes, (void (*)(void *, void*)) FT_strcatAccumulate, 
                        (void *) result);

   DynArray_free(nodes);
   assert(CheckerFT_isValid(isInitialized,root,count));
   return result;
}

/*--------------------------------------------------------------------*/
