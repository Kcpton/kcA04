/*--------------------------------------------------------------------*/
/* file.h                                                             */
/* Author: Kevin Chen                                     */
/*--------------------------------------------------------------------*/

#ifndef FILE_INCLUDED
#define FILE_INCLUDED

#include <stddef.h>
#include "node.h"


/*
   a File_T is an object that contains a path  and references to
   the node's parent (if it exists) and children (if they exist).
*/
typedef struct file* File_T;

/*
   File_insert takes in an inNode, path, contents, length and creates
   a new file with path, contents and length, then insert it into 
   inNode. Return SUCCESS done successfully. Returns ALREADY_IN_TREE 
   if the file is already in the tree. Returns MEMORY_ERROR if 
   there is insufficent space.
 */
int File_insert(Node_T inNode, char* path, void* contents, 
   size_t length);

/*
   File_replace takes in an inNode, a path and contents, and length
   if the file exist in the node, then it replaces the old content 
   with the new content and returns the old content. It also replace
   the the old len with the new length. If the file doesn't exist
   return NULL.
*/
void* File_replace(Node_T inNode, char* path, void* contents, 
   size_t length);

/*
   File_getcontents takes in an inNode and a path and returns
   the contents of the file with name path inside the inNode. 
   If there is no such file, return NULL.
*/
void* File_getcontents(Node_T inNode, char* path);


/*
   File_getFileName takes in an inNode and size_t fileID and 
   return the path of the File. Otherwise return NULL.
*/
char* File_getFileName(Node_T inNode, size_t fileID);

/*
   File_rmFile takes in an inNode and path and removes the
   file with name path. If success return SUCCESS. If the
   file does not exist, return NO_SUCH_PATH. 
*/
int File_rmFile(Node_T inNode, char* path);

/*
   File_contains take in an inNode and path and returns
   TRUE if the file path exist inside the inNode. Otherwise
   return FALSE.
*/
int File_contains(Node_T inNode, char* path);

/*
   File_getNumFiles take in an inNode and path. It returns the
   number of files in the inNode.
*/
size_t File_getNumFiles(Node_T inNode, char* path);

/*
   File_freeAll takes in an inNode and frees all the files in
   the inNode.
*/
void File_freeAll(Node_T inNode);

/* File_getLength takes in an inNode and a path and returns the
   length of the file */
size_t File_getLength(Node_T inNode, char* path);
#endif