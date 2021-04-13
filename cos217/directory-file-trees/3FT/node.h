/*--------------------------------------------------------------------*/
/* node.h                                                             */
/* Author: Giao Vu Dinh '24 and Sean Wang '24                         */
/*--------------------------------------------------------------------*/

#ifndef NODE_INCLUDED
#define NODE_INCLUDED

#include <stddef.h>
#include <stdlib.h>
#include "a4def.h"

/*
   a Node_T is an object that contains a path payload and references to
   the node's parent (if it exists) and children (if they exist).
*/
typedef struct node* Node_T;


/*
   Given a parent node and a directory string dir, returns a new
   Node_T or NULL if any allocation error occurs in creating
   the node or its fields.

   The new structure is initialized to have its path as the parent's
   path (if it exists) prefixed to the directory string parameter,
   separated by a slash. It is also initialized with its parent link
   as the parent parameter value, but the parent itself is not changed
   to link to the new node.  
   
   If isFile is TRUE, the new structure will represent a file, with the
   file contents and length being represented by the contents and length
   parameters. If isFile is FALSE, the new structure will represent
   a directory node, where the children links are initialized but
   do not point to any children.
*/

Node_T Node_create(const char* dir, const Node_T parent, 
						 boolean isFile, void* contents, size_t length);

/*
   Destroys the hierarchy of nodes rooted at n, including n itself.
   Returns the number of nodes destroyed.
*/
size_t Node_destroy(Node_T n);

/*
   Compares node1 and node2 based on their paths. Returns <0, 0, or >0 
   if node1 is less than, equal to, or greater than node2, respectively.
*/
int Node_compare(Node_T node1, Node_T node2);

/*
   Returns n's path.
*/
const char* Node_getPath(const Node_T n);

/*
   Returns the length of n's file contents. Returns 0 if n represents
   a directory node.
*/
size_t Node_getFileLength(const Node_T n);

/*
   Returns the number of child directories n has.
*/
size_t Node_getNumDirChildren(Node_T n);

/*
   Returns the number of child files n has.
*/
size_t Node_getNumFileChildren(Node_T n);

/*
   Returns TRUE if Node n represents a file and FALSE if a directory.
*/
boolean Node_isFile(Node_T n);

/*
   Returns the file contents if the node n represents a file. 
*/
void* Node_getFileContents(Node_T n);

/*
   Returns the child directory node of n with identifier childID, 
   if one exists, otherwise returns NULL.
*/
Node_T Node_getDirChild(Node_T n, size_t childID);

/*
   Returns the child file node of n with identifier childID, 
   if one exists, otherwise returns NULL.
*/
Node_T Node_getFileChild(Node_T n, size_t childID);

/*
   Returns the parent node of n, if it exists, otherwise returns NULL
*/
Node_T Node_getParent(Node_T n);

/*
   Makes child a child of parent, if possible, and returns SUCCESS.
   This is not possible in the following cases:
   * child's path is not parent's path + / + directory,
      in which case returns PARENT_CHILD_ERROR
   * parent already has a child with child's path,
      in which case returns ALREADY_IN_TREE
   * parent is unable to allocate memory to store new child link,
      in which case returns MEMORY_ERROR
 */
int Node_linkChild(Node_T parent, Node_T child);

/*
   Unlinks node parent from its child node child. child is unchanged.
   Returns PARENT_CHILD_ERROR if child is not a child of parent,
   and SUCCESS otherwise.
 */
int Node_unlinkChild(Node_T parent, Node_T child);

/*
   Returns a string representation for n or NULL if there is an 
   allocation error. Allocates memory for the returned string,
   which is then owned by client!
*/
char* Node_toString(Node_T n);

/*
   Changes the file contents and length of node n to the given 
   parameters contents and length respectively. Returns the old file
   contents of n, or NULL if there were no previously assigned contents.
*/
void*  Node_assignContents(Node_T n, void* contents, size_t length);

#endif
