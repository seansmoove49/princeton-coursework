/*--------------------------------------------------------------------*/
/* ft.c                                                               */
/* Author: Sean Wang '24 and Giao Vu Dinh '24                         */
/*--------------------------------------------------------------------*/

#include <stddef.h>
#include "a4def.h"
#include "dynarray.h"
#include "ft.h"
#include "node.h"

/*--------------------------------------------------------------------*/

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