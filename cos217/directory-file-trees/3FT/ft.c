/*--------------------------------------------------------------------*/
/* ft.c                                                               */
/* Author: Sean Wang '24 and Giao Vu Dinh '24                         */
/*--------------------------------------------------------------------*/

#include <stddef.h>
#include "a4def.h"
#include "dynarray.h"
#include "ft.h"
#include "node.h"

/* A File Tree is an AO with 3 state variables: */
/* a flag for if it is in an initialized state (TRUE) or not (FALSE) */
static boolean isInitialized;
/* a pointer to the root node in the hierarchy */
static Node_T root;
/* a count of the number of nodes in the hierarchy */
static size_t count;

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
   return 0;
}

/*--------------------------------------------------------------------*/

boolean FT_containsDir(char *path) {
   return TRUE;
}

/*--------------------------------------------------------------------*/

int FT_rmDir(char *path) {
   return 0;
}

/*--------------------------------------------------------------------*/

int FT_insertFile(char *path, void *contents, size_t length) {
   return 0;
}

/*--------------------------------------------------------------------*/

boolean FT_containsFile(char *path) {
   return FALSE;
}

/*--------------------------------------------------------------------*/

int FT_rmFile(char *path) {
   return 0;
}

/*--------------------------------------------------------------------*/

void *FT_getFileContents(char *path) {
   return NULL;
}

/*--------------------------------------------------------------------*/

void *FT_replaceFileContents(char *path, void *newContents,
                             size_t newLength) {
   return NULL;                             
}

/*--------------------------------------------------------------------*/

int FT_stat(char *path, boolean *type, size_t *length) {
   return 0;
}

/*--------------------------------------------------------------------*/

int FT_init(void) {
   return 0;
}

/*--------------------------------------------------------------------*/

int FT_destroy(void) {
   return 0;
}

/*--------------------------------------------------------------------*/

char *FT_toString(void) {
   return NULL;
}

/*--------------------------------------------------------------------*/