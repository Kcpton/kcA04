/*--------------------------------------------------------------------*/
/* node.h                                                             */
/* Author: Kevin Chen                                     */
/*--------------------------------------------------------------------*/

#ifndef NODE_INCLUDED
#define NODE_INCLUDED

#include <stddef.h>
#include "a4def.h"

typedef struct node* Node_T;
/*
   Node_getLocation takes a Node_T input and looks for a char
   key inside of the Node_T and stores the location of where
   it is/supposed to be. Returns 0 if the Node key is not
   in the location. Otherwise returns 1;
*/
int Node_getLocation(Node_T input, char* key, size_t *loc);

/*
   Node_getChild returns the child node of input with
   identifier childID, if one exists, otherwise returns NULL.
*/
Node_T Node_getChild(Node_T input, size_t childID);

/*
   Node_new takes an input parent node and key and returns

*/
Node_T Node_new(char* key);

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
   Node_destory takes a input node and frees all the files and
   Nodes under it. It returns the number of nodes it destorys.
*/
size_t Node_destroy(Node_T input);

/*
   Node_contains take a node parent and a node child. If the child
   is in the parent then return 1. Otherwise return 0.
*/
int Node_contains(Node_T parent, Node_T child);

#endif
