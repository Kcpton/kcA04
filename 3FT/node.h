/*--------------------------------------------------------------------*/
/* node.h                                                             */
/* Author: Kevin Chen                                     */
/*--------------------------------------------------------------------*/

#ifndef NODE_INCLUDED
#define NODE_INCLUDED

#include <stddef.h>
#include "a4def.h"
#include "dynarray.h"

/*
   a Node_T is an object that represents a directory, it also
   contains a path and references to the node's files and children 
   directory(if they exist).
*/
typedef struct node* Node_T;
/*
   Node_getLocation takes a Node_T input and looks for a char
   path inside of the Node_T and stores the location of where
   it is/supposed to be. Returns 0 if the Node key is not
   in the location. Otherwise returns 1;
*/
int Node_getLocation(Node_T input, char* path, size_t *loc);

/*
   Node_getChild returns the child node of input with
   identifier childID, if one exists, otherwise returns NULL.
*/
Node_T Node_getChild(Node_T input, size_t childID);

/*
   Node_new takes a path and creates and returns a node with 
   that path.
*/
Node_T Node_new(char* path);

/*
   Node_addChild takes a parent Node and a char*. It creates
   a new child node based on the char* and insert it as a
   child of parent at the location loc.
   It returns SUCCESS if node is added.
   It returns MEMORY_ERROR if space cannot be allocated for it.
*/
int Node_addChild(Node_T parent, char* child, size_t loc);

/*
   Node_getPath takes an input Node and returns the
   path of the input Node as a char*.
*/
char* Node_getPath(Node_T input);

/*
   Node_getNumChildren takes an input node and returns a size_t
   based on the number of directory children it has.
*/
size_t Node_getNumChildren(Node_T input);

/*
   Node_getNumFiles takes an input node and returns a size_t
   based on the number of file children it has.
*/
size_t Node_getNumFiles(Node_T input);

/*
   Node_destory takes a parent node, an input Node, and size_t
   loc. It removes the input Node from the parent based on
   loc and frees the input. It returns the number of nodes it 
   destorys.
*/
size_t Node_destroy(Node_T parent, Node_T input, size_t loc);

/*
   Node_destoryhelp takes a input node and frees and the files
   and Nodes under it. It returns the number of nodes 
   that it destorys.
*/
size_t Node_destroyhelp(Node_T input);

/*
   Node_getFiles takes in a node input and returns the files
   DynArray_T
*/
DynArray_T Node_getFiles(Node_T input);

#endif
