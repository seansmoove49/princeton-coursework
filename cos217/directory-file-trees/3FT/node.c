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
   a Node_T is an object that contains a path payload and references to
   the node's parent (if it exists) and children (if they exist).
*/
struct node {
   /* the full path of this directory */
   char* path;

   /* the parent directory of this directory
      NULL for the root of the directory tree */
   Node_T parent;

	/* the subdirectories of this directory
      stored in sorted order by pathname */
   DynArray_T files;

   /* the subdirectories of this directory
      stored in sorted order by pathname */
   DynArray_T directories;

	/* represents whether this node is a file (TRUE) or dir (FALSE) */
	boolean isFile;

	/* the contents of the file if this node represents a file */
	void* contents;

	/* the length of the file if this node represents a file */
	size_t length;
};

/*
  	returns a path with contents
  	n->path/dir
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
	The new structure is initialized to have its path as the parent's
   path (if it exists) prefixed to the directory string parameter,
   separated by a slash. It is also initialized with its parent link
   as the parent parameter value, but the parent itself is not changed
   to link to the new node.  The children links are initialized but
   do not point to any children.
*/

static Node_T Node_createDir(const char* dir, const Node_T parent) {
	Node_T new;

	assert(parent == NULL || CheckerFT_Node_isValid(parent));
	assert(dir != NULL);
	if (parent != NULL)
		assert(!Node_isFile(parent)); /* this will be moved into ft.c */

	/* original function keeps repeating the same assert even though
	   this function never modifies the parent - make parent const
		to fix this */

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
	same as above, but allocates space for the file contents
	file contents can be null
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

/* the public one - returns NULL if didn't work */

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


/*
	Destroys the entire hierarchy of nodes rooted at n,
	including n itself.

	Returns the number of nodes destroyed.
*/
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


/*
  Compares node1 and node2 based on their paths.
  Returns <0, 0, or >0 if node1 is less than,
  equal to, or greater than node2, respectively.
*/
int Node_compare(const Node_T node1, const Node_T node2) {
	assert(node1 != NULL);
	assert(node2 != NULL);

	return strcmp(node1->path, node2->path);
}

/*
   Returns n's path.
*/
const char* Node_getPath(const Node_T n) {
   assert(n != NULL);
   return n->path;
}

/*
   Returns n's length.
*/
size_t Node_getLength(const Node_T n) {
	assert(n != NULL);
	return n->length;
}

/*
  Returns the number of child directories n has.
  If n is a file, return 0. 
*/
size_t Node_getNumDirChildren(const Node_T n) {
	assert(n != NULL);

	if (Node_isFile(n))
		return 0;

	return DynArray_getLength(n->directories);
}

/*
  Returns the number of child directories n has.
  If n is a file, return 0. 
*/
size_t Node_getNumFileChildren(const Node_T n) {
	assert(n != NULL);

	if (Node_isFile(n))
		return 0;

	return DynArray_getLength(n->files);
}

/*
  Returns true if the node is a file, false if a directory. 
*/
boolean Node_isFile(const Node_T n) {
	assert(n != NULL);
	return n->isFile;
}

/*
  Returns the file contents if the node is a file. 
*/
void* Node_getFileContents(const Node_T n) {
	assert(n != NULL);
	return n->contents;
}

/*
   Returns 1 if n has a child directory with path,
   0 if it does not have such a child, and -1 if
   there is an allocation error during search.

   If n does have such a child, and childID is not NULL, store the
   child's identifier in *childID. If n does not have such a child,
   store the identifier that such a child would have in *childID.

	If n does have such a child, and the child is a file, store TRUE
	in *isFile. If the child is a directory, store FALSE. 
*/
int Node_hasChild(Node_T n, const char* path, size_t* childID) {
	size_t index;
	int result;
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
   Returns the child directory node of n with identifier childID, 
	if one exists, otherwise returns NULL. 
*/
Node_T Node_getDirChild(Node_T n, size_t childID) {
	assert(n != NULL);
	assert(!Node_isFile(n));

	if (DynArray_getLength(n->directories) > childID) 
		return DynArray_get(n->directories, childID);
	else 
		return NULL;
}

Node_T Node_getFileChild(Node_T n, size_t childID) {
	assert(n != NULL);
	assert(!Node_isFile(n));

	if (DynArray_getLength(n->files) > childID) 
		return DynArray_get(n->files, childID);
	else 
		return NULL;
}

/*
   Returns the parent node of n, if it exists, otherwise returns NULL
*/
Node_T Node_getParent(Node_T n) {
	assert(n != NULL);
	return n->parent;
}


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


/*
  Makes child a child of parent, if possible, and returns SUCCESS.
  This is not possible in the following cases:
  * parent is a file, 
    in which case return NOT_A_DIRECTORY
  * child's path is not parent's path + / + directory,
    in which case returns PARENT_CHILD_ERROR
  * parent already has a child with child's path,
    in which case returns ALREADY_IN_TREE
  * parent is unable to allocate memory to store new child link,
    in which case returns MEMORY_ERROR
 */
int Node_linkChild(Node_T parent, const Node_T child) {
	size_t i;
	int added;

	assert(parent != NULL);
	assert(child != NULL);
	assert(CheckerFT_Node_isValid(parent));
	assert(CheckerFT_Node_isValid(child));

   /* we need to assert that child's parent is already parent 
      this could be a parent child error */

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

/*
  Unlinks node parent from its child node child. child is unchanged.

  Returns PARENT_CHILD_ERROR if child is not a child of parent,
  and SUCCESS otherwise.
 */

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

/*
  Returns a string representation for n, 
  or NULL if there is an allocation error.

  Allocates memory for the returned string,
  which is then owned by client!
*/
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

/* 
   assign contents function - need to do for the file
*/

void* Node_assignContents(Node_T n, void* contents, size_t length) {
   void *oldContents;

   assert(n != NULL);
   assert(CheckerFT_Node_isValid(n));

   oldContents = n->contents;
   n->contents = contents;
	n->length = length;

   return oldContents;
}