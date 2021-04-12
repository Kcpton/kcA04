/*--------------------------------------------------------------------*/
/* node.c                                                             */
/* Author: Kevin Chen                                     */
/*--------------------------------------------------------------------*/

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#include "dynarray.h"
#include "node.h"

struct node {
   /* the full path of this directory */
   char* path;
   /* the subdirectories of this directory
      stored in sorted order by pathname */
   DynArray_T children;
   /* the files of this directory
      stored in sorted order by pathname */
   DynArray_T files;
};

Node_T Node_new(char* path) {
   Node_T output;
   assert(path != NULL);
   output = (Node_T) malloc(sizeof(struct node));
   if (output == NULL) {
      return NULL;
   }
   output->path = (char*) malloc(strlen(path) + 1);
   if (output->path == NULL) {
      return NULL;
   }
   strcpy(output->path, path);
   output->children = DynArray_new(0);
   output->files = DynArray_new(0);
   return output;
}

/*
  Node_compare compares node1 and node2 based on their paths.
  Returns <0, 0, or >0 if node1 is less than,
  equal to, or greater than node2, respectively.
*/
static int Node_compare(Node_T node1, Node_T node2) {
   assert(node1 != NULL);
   assert(node2 != NULL);
   return strcmp(node1->path, node2->path);
}

/* see node.h for specification */
char* Node_toString(Node_T n) {
   char* copyPath;
   assert(n != NULL);

   copyPath = malloc(strlen(n->path)+1);
   if(copyPath == NULL) {
      return NULL;
   }
   else {
      return strcpy(copyPath, n->path);
   }
}


Node_T Node_getChild(Node_T n, size_t childID) {
   assert(n != NULL);

   if(DynArray_getLength(n->children) > childID) {
      return DynArray_get(n->children, childID);
   }
   else {
      return NULL;
   }
}

int Node_getLocation(Node_T input, char* key, size_t *loc) {
   assert(input != NULL);
   assert(key != NULL);
   return DynArray_bsearch(input->children, key, loc,
                           (int (*)(const void*, const void*)) Node_compare) == 0;
}

int Node_addChild(Node_T parent, char* path, size_t loc) {
   Node_T newNode = Node_new(path);
   assert(parent != NULL);
   assert(path != NULL);
   if(newNode == NULL) {
      return MEMORY_ERROR;
   }
   if(DynArray_addAt(parent->children, loc, newNode)) {
      return SUCCESS;
   }
   else {
      Node_destroy(newNode);
      return MEMORY_ERROR;
   }
}

char* Node_getPath(Node_T input) {
   assert(input != NULL);
   return input->path;
}

size_t Node_getNumChildren(Node_T n) {
   assert(n != NULL);

   return DynArray_getLength(n->children);
}

size_t Node_destroy(Node_T input) {
   size_t i;
   size_t count = 0;
   Node_T tempNode;

   assert(input != NULL);

   for(i = 0; i < DynArray_getLength(input->children); i++)
   {
      tempNode = DynArray_get(input->children, i);
      count += Node_destroy(tempNode);
   }

   DynArray_free(input->children);
   free(input->path);
   free(input);
   count++;

   return count;
}



