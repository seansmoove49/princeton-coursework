/*--------------------------------------------------------------------*/
/* node.h                                                             */
/* Author: Giao Vu Dinh '24 and Sean Wang '24                         */
/*--------------------------------------------------------------------*/

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "node.h"
#include "dynarray.h"
#include "checkerFT.h"

/*
   A node structure represents a directory or file in the file tree. 
*/
struct node {
   /* the full path of this node */
   char* path;

   /* the parent directory of this node
      NULL for the root of the directory tree */
   Node_T parent;

	/* represents whether this node is a file (TRUE) or dir (FALSE) */
	boolean isFile;

	/* the subfiles of this node if it represents a directory
      stored in sorted order by pathname */
   DynArray_T files;

   /* the subdirectories of this node if it represents a directory
      stored in sorted order by pathname */
   DynArray_T directories;

	/* the contents of the file if this node represents a file */
	void* contents;

	/* the length of the file if this node represents a file */
	size_t length;
};

/*--------------------------------------------------------------------*/

/*
  	returns a path with contents "n->path/dir"
  	or NULL if there is an allocation error.

  	Allocates memory for the returned string,
  	which is then owned by the caller!
*/
static char* Node_buildPath(Node_T n, const char* dir) {
   char* path;
	size_t dirLen;

   assert(dir != NULL);

	dirLen = strlen(dir);

   if(n == NULL)
      path = malloc(dirLen+1);
   else
      path = malloc(strlen(n->path) + dirLen + 2);

   if(path == NULL)
      return NULL;
   *path = '\0';

   if(n != NULL) {
      strcpy(path, n->path);
      strcat(path, "/");
   }
   strcat(path, dir);

   return path;
}

/*
	Returns a new a directory node with given parent and dir parameters.
	See description of Node_create in node.h for specification. 
*/
static Node_T Node_createDir(const char* dir, const Node_T parent) {
	Node_T new;

	assert(parent == NULL || CheckerFT_Node_isValid(parent));
	assert(dir != NULL);
	if (parent != NULL)
		assert(!Node_isFile(parent));

	new = malloc(sizeof(struct node));
	
	if (new == NULL) 
		return NULL;
	
	new->path = Node_buildPath(parent, dir);

	if (new->path == NULL) {
		free(new);
		return NULL;
	}

	new->isFile = FALSE;
	new->contents = NULL;
	new->length = 0;
	new->parent = parent;

	new->directories = DynArray_new(0);
	if (new->directories == NULL) {
		free(new->path);
		free(new);
		return NULL;
	}

	new->files = DynArray_new(0);
	if (new->files == NULL) {
		free(new->path);
		free(new);
		return NULL;
	}

	assert(CheckerFT_Node_isValid(new));
	
	return new;
}

/*
	Returns a new file node with given parent and dir parameters.
	File contents and length are given by contents and length parameters.
	See description of Node_create in node.h for specification. 
*/
static Node_T Node_createFile(const char* dir, const Node_T parent, 
							  void *contents, size_t length) {
	Node_T new;

	assert(parent != NULL);
	assert(CheckerFT_Node_isValid(parent));
	assert(dir != NULL);
	assert(!Node_isFile(parent)); /* will be moved */

	new = malloc(sizeof(struct node));
	if (new == NULL) 
		return NULL;

	new->path = Node_buildPath(parent, dir);

	if (new->path == NULL) {
		free(new);
		return NULL;
	}
	new->isFile = TRUE;
   new->contents = contents;
	new->length = length;

	new->parent = parent;
	new->directories = NULL;
	new->files = NULL;

	return new;
}

/*
   Returns 1 if n has a child directory or file with path, 0 if it does
   not have such a child, and -1 if there is an allocation error during
   search.

   If n does have such a child, and childID is not NULL, store the
   child's identifier in *childID. If n does not have such a child,
   store the identifier that such a child would have in *childID.
*/
static int Node_hasChild(Node_T n, const char* path, size_t* childID) {
	size_t index;
	int result = 0;
	Node_T checker;

	assert(n != NULL);
	assert(path != NULL);
	assert(!Node_isFile(n));

	checker = Node_create(path, NULL, FALSE, NULL, 0);
	if (checker == NULL) {
		return -1;
	}

	if (DynArray_bsearch(n->directories, checker, &index, (int (*)
	    (const void*, const void*)) Node_compare) == 1) {
		result = 1;	 
	} 
	else if (DynArray_bsearch(n->files, checker, &index, (int (*)
	    		(const void*, const void*)) Node_compare) == 1) {
		result = 1;
	}

   (void) Node_destroy(checker);

	if (childID != NULL)
		*childID = index;

	return result;
}

/* 
	Given a pair of parent and child nodes, return 1 if child's path is
	not parent's path + / + directory. Return 0 if otherwise
*/
static int Node_hasParentChildErr(const Node_T parent, 
                                  const Node_T child) {
	size_t i;
	char *rest;

	assert(parent != NULL);
	assert(child != NULL);
	assert(CheckerFT_Node_isValid(parent));
	assert(CheckerFT_Node_isValid(child));

	i = strlen(parent->path);
	if (strncmp(child->path, parent->path, i))
		return 1;

	if(child->parent != parent)
      return 1;
	rest = child->path + i;

	if (strlen(child->path) >= i && rest[0] != '/')
		return 1;
   rest++;

   if (strstr(rest, "/") != NULL)
      return 1;

   return 0;
}

/*--------------------------------------------------------------------*/

/* see node.h for specification */
Node_T Node_create(const char* dir, const Node_T parent, 
						 boolean isFile, void* contents, size_t length) {
	Node_T new;

	assert(parent == NULL || CheckerFT_Node_isValid(parent));
	assert(dir != NULL);
	
	if (isFile) {
		new = Node_createFile(dir, parent, contents, length);
	}
	else {
		new = Node_createDir(dir, parent);
	}
		
	return new;
}

/* see node.h for specification */
size_t Node_destroy(Node_T n) {
	size_t i;
	size_t count = 0;
	size_t dynArrLength;
	Node_T curr;

	assert(n != NULL);

	if (!Node_isFile(n)) {
		dynArrLength = DynArray_getLength(n->directories);

		for (i = 0; i < dynArrLength; i++) {
			curr = DynArray_get(n->directories, i);
			count += Node_destroy(curr);
		}
		DynArray_free(n->directories);

		dynArrLength = DynArray_getLength(n->files);

		for (i = 0; i < dynArrLength; i++) {
			curr = DynArray_get(n->files, i);
			count += Node_destroy(curr);
		}
		DynArray_free(n->files);
	}

	free(n->path);
	free(n);
	n = NULL;
	count++;

  	return count;
}

/* see node.h for specification */
int Node_compare(const Node_T node1, const Node_T node2) {
	assert(node1 != NULL);
	assert(node2 != NULL);

	return strcmp(node1->path, node2->path);
}

/* see node.h for specification */
const char* Node_getPath(const Node_T n) {
   assert(n != NULL);
   return n->path;
}

/* see node.h for specification */
size_t Node_getFileLength(const Node_T n) {
	assert(n != NULL);
	return n->length;
}

/* see node.h for specification */
size_t Node_getNumDirChildren(const Node_T n) {
	assert(n != NULL);

	if (Node_isFile(n))
		return 0;

	return DynArray_getLength(n->directories);
}

/* see node.h for specification */
size_t Node_getNumFileChildren(const Node_T n) {
	assert(n != NULL);

	if (Node_isFile(n))
		return 0;

	return DynArray_getLength(n->files);
}

/* see node.h for specification */
boolean Node_isFile(const Node_T n) {
	assert(n != NULL);
	return n->isFile;
}

/* see node.h for specification */
void* Node_getFileContents(const Node_T n) {
	assert(n != NULL);
	return n->contents;
}

/* see node.h for specification */
Node_T Node_getDirChild(Node_T n, size_t childID) {
	assert(n != NULL);
	assert(!Node_isFile(n));

	if (DynArray_getLength(n->directories) > childID) 
		return DynArray_get(n->directories, childID);
	else 
		return NULL;
}

/* see node.h for specification */
Node_T Node_getFileChild(Node_T n, size_t childID) {
	assert(n != NULL);
	assert(!Node_isFile(n));

	if (DynArray_getLength(n->files) > childID) 
		return DynArray_get(n->files, childID);
	else 
		return NULL;
}

/* see node.h for specification */
Node_T Node_getParent(Node_T n) {
	assert(n != NULL);
	return n->parent;
}

/* see node.h for specification */
int Node_linkChild(Node_T parent, const Node_T child) {
	size_t i;
	int added;

	assert(parent != NULL);
	assert(child != NULL);
	assert(CheckerFT_Node_isValid(parent));
	assert(CheckerFT_Node_isValid(child));

	if (Node_isFile(parent)) 
		return NOT_A_DIRECTORY;
	
	if (Node_hasChild(parent, child->path, NULL))
		return ALREADY_IN_TREE;

   if (Node_hasParentChildErr(parent, child))
      return PARENT_CHILD_ERROR;

	/* adding the two types */
	if (child->isFile) {
		if (DynArray_bsearch(parent->files, child, &i, 
			(int (*)(const void*, const void*)) Node_compare) == 1) 
			return ALREADY_IN_TREE;

		added = DynArray_addAt(parent->files, i, child);
	} else {
		if (DynArray_bsearch(parent->directories, child, &i, 
			(int (*)(const void*, const void*)) Node_compare) == 1) 
			return ALREADY_IN_TREE;

		added = DynArray_addAt(parent->directories, i, child);
	}

	assert(CheckerFT_Node_isValid(parent));

	if (added) return SUCCESS;
	else return MEMORY_ERROR;
}

/* see node.h for specification */
int Node_unlinkChild(Node_T parent, const Node_T child) {
   size_t i;

   assert(parent != NULL);
	assert(child != NULL);
	assert(CheckerFT_Node_isValid(parent));
	assert(CheckerFT_Node_isValid(child));

	/* handling types */
	if (child->isFile) {
		if (DynArray_bsearch(parent->files, child, &i, 
			(int (*)(const void*, const void*)) Node_compare) == 0) 
			return PARENT_CHILD_ERROR;

   	(void) DynArray_removeAt(parent->files, i);
	} else {
		if (DynArray_bsearch(parent->directories, child, &i, 
			(int (*)(const void*, const void*)) Node_compare) == 0) 
			return PARENT_CHILD_ERROR;

		(void) DynArray_removeAt(parent->directories, i);
	}

   assert(CheckerFT_Node_isValid(parent));
	return SUCCESS;
}

/* see node.h for specification */
char* Node_toString(Node_T n) {
   char *copyPath;
   assert(n != NULL);

   copyPath = malloc(strlen(n->path) + 1);
   if (copyPath == NULL)
      return NULL;
   else
      return strcpy(copyPath, n->path);

	return NULL;
}

/* see node.h for specification */
void* Node_assignContents(Node_T n, void* contents, size_t length) {
   void *oldContents;

   assert(n != NULL);
   assert(CheckerFT_Node_isValid(n));

   oldContents = n->contents;
   n->contents = contents;
	n->length = length;

   return oldContents;
}

/*--------------------------------------------------------------------*/