/*--------------------------------------------------------------------*/
/* file.h                                                             */
/* Author: Kevin Chen                                     */
/*--------------------------------------------------------------------*/

#ifndef FILE_INCLUDED
#define FILE_INCLUDED

#include <stddef.h>
#include "a4def.h"
#include "node.h"


/*
   a File_T is an object that contains a path  and references to
   the node's parent (if it exists) and children (if they exist).
*/
typedef struct file* File_T;


File_T File_new(char* path, void* contents);

int File_insert(Node_T inNode, char* path, void* contents);

void* File_replace(Node_T inNode, char* path, void* contents);

void* File_getcontents(Node_T inNode, char* path);

char* File_getFileName(Node_T inNode, size_t fileID);

int File_rmFile(Node_T inNode, char* path);

int File_contains(Node_T inNode, char* path);

char* File_toString(Node_T inNode, char* path);

size_t File_getNumFiles(Node_T inNode, char* path);

void File_freeAll(Node_T inNode);
#endif
