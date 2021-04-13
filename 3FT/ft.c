/***********************************************************************
Authors: Jackie Chen, Kevin Chen
ID: jackieyc, kc46
Date: 4/10/2021
File: ft.c
Description: Implements ft.h interface. Creates a tree of directories.
Allows files to be inserted into the tree as well
***********************************************************************/

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "ft.h"
#include "file.h"
#include "node.h"

/* Remember to write some comment here, dumbass*/
static boolean isInitialized;

static Node_T root;

int FT_insertDir(char *path)
{
   char* currentPath;
   char* currentTok;
   char* nextTok;
   char* copyPath;
   size_t loc;

   Node_T currentNode = root;

   if(!isInitialized)
      return INITIALIZATION_ERROR;

   assert(path != NULL);
   currentPath =  malloc(strlen(path) + 1);
   copyPath = malloc(strlen(path) + 1);

   if(currentPath == NULL || copyPath == NULL)
      return MEMORY_ERROR;

   strcpy(copyPath, path);
   currentTok = strtok(copyPath, "/");
   nextTok = strtok(NULL, "/");
   strcpy(currentPath, currentTok);
   if(root == NULL)
   {
      root = Node_new(currentPath);
      Node_addChild(root, currentPath, 0);
      currentTok = nextTok;
      if(currentTok == NULL)
      {
         free(copyPath);
         free(currentPath);
         return SUCCESS;
      }
   }

   else if(strcmp(Node_getPath(root),currentPath) != 0)
   {
      free(copyPath);
      free(currentPath);
      return CONFLICTING_PATH;
   }
   currentNode = root;
   while(nextTok != NULL)
   {
      if(File_contains(currentNode, currentPath))
      {
         free(copyPath);
         free(currentPath);
         return NOT_A_DIRECTORY;
      }
      if(Node_getLocation(currentNode, currentPath, &loc) == 0)
      {
         if(Node_addChild(currentNode, currentPath, loc) != SUCCESS)
         {
            free(copyPath);
            free(currentPath);
            return MEMORY_ERROR;
         }
      }
      currentNode = Node_getChild(currentNode, loc);
      currentTok = nextTok;
      nextTok = strtok(NULL, "/");
      strcat(currentPath, "/");
      strcat(currentPath, currentTok);
   }
   if(File_contains(currentNode, currentPath))
   {
      free(copyPath);
      free(currentPath);
      return ALREADY_IN_TREE;
   }
   if(Node_getLocation(currentNode, currentPath, &loc))
   {
      free(copyPath);
      free(currentPath);
      return ALREADY_IN_TREE;
   }
   free(copyPath);
   free(currentPath);
   return Node_addChild(currentNode, path, loc);
}

boolean FT_containsDir(char *path)
{
   char* currentPath;
   char* currentTok;
   char* nextTok;
   char* copyPath;
   size_t loc;
   Node_T currentNode = root;

   if(!isInitialized)
      return FALSE;

   if(root == NULL)
      return FALSE;

   assert(path != NULL);
   if(strcmp(Node_getPath(root), path) == 0)
      return TRUE;

   currentPath = malloc(strlen(path) + 1);
   copyPath = malloc(strlen(path) + 1);

   assert(copyPath != NULL);
   assert(currentPath != NULL);

   strcpy(copyPath, path);
   currentTok = strtok(copyPath, "/");
   nextTok = strtok(NULL, "/");
   strcpy(currentPath, currentTok);
   while(nextTok != NULL)
   {
      if(!Node_getLocation(currentNode, currentPath, &loc)){
         free(copyPath);
         free(currentPath);
         return FALSE;
      }
      currentNode = Node_getChild(currentNode, loc);
      currentTok = nextTok;
      nextTok = strtok(NULL, "/");
      strcat(currentPath, "/");
      strcat(currentPath, currentTok);
   }
   if(!Node_getLocation(currentNode, currentPath, &loc))
   {
      free(copyPath);
      free(currentPath);
      return FALSE;
   }
   free(copyPath);
   free(currentPath);
   return TRUE;
}

int FT_rmDir(char *path)
{
   char* currentPath;
   char* currentTok;
   char* nextTok;
   char* copyPath;
   size_t loc;
   Node_T currentNode = root;

   if(!isInitialized)
      return INITIALIZATION_ERROR;

   assert(path != NULL);
   if(root == NULL)
      return NO_SUCH_PATH;

   if(strcmp(Node_getPath(root), path) == 0)
   {
      Node_destroy(root);
      return SUCCESS;
   }


   currentPath =  malloc(strlen(path) + 1);
   copyPath = malloc(strlen(path) + 1);
   assert(currentPath != NULL);
   assert(copyPath != NULL);

   strcpy(copyPath, path);
   currentTok = strtok(copyPath, "/");
   nextTok = strtok(NULL, "/");
   strcpy(currentPath, currentTok);
   strcat(currentPath, "/");
   strcat(currentPath, nextTok);
   nextTok = strtok(NULL, "/");
   while(nextTok != NULL)
   {
      if(!Node_getLocation(currentNode, currentPath, &loc)){
         free(copyPath);
         free(currentPath);
         return NO_SUCH_PATH;
      }
      currentNode = Node_getChild(currentNode, loc);
      currentTok = nextTok;
      nextTok = strtok(NULL, "/");
      strcat(currentPath, "/");
      strcat(currentPath, currentTok);
   }
   if(Node_getLocation(currentNode, currentPath, &loc))
   {
      currentNode = Node_getChild(currentNode, loc);
      Node_destroy(currentNode);
      free(copyPath);
      free(currentPath);
      return SUCCESS;
   }
   if(File_contains(currentNode, currentPath)){
      free(copyPath);
      free(currentPath);
      return NOT_A_DIRECTORY;
   }
   free(copyPath);
   free(currentPath);
   return NO_SUCH_PATH;
}

int FT_insertFile(char *path, void *contents, size_t length)
{
   char* currentPath;
   char* currentTok;
   char* nextTok;
   char* copyPath;
   size_t loc;
   Node_T currentNode = root;

   if(!isInitialized)
      return INITIALIZATION_ERROR;

   assert(path != NULL);
   currentPath =  malloc(strlen(path) + 1);
   copyPath = malloc(strlen(path) + 1);

   if(currentPath == NULL || copyPath == NULL)
      return MEMORY_ERROR;

   strcpy(copyPath, path);
   currentTok = strtok(copyPath, "/");
   nextTok = strtok(NULL, "/");
   strcpy(currentPath, currentTok);

   if(root == NULL)
   {
      if(nextTok == NULL)
      {
         free(copyPath);
         free(currentPath);
         return CONFLICTING_PATH;
      }
      root = Node_new(currentPath);
      currentTok = nextTok;

      nextTok = strtok(NULL, "/");
      strcat(currentPath, "/");
      strcat(currentPath, currentTok);
   }

   else if (strcmp(Node_getPath(root),currentPath) != 0)
   {
      free(copyPath);
      free(currentPath);
      return CONFLICTING_PATH;
   }
   
   while(nextTok != NULL)
   {
      if(File_contains(currentNode, currentPath))
      {
         free(copyPath);
         free(currentPath);
         return NOT_A_DIRECTORY;
      }
      if(Node_getLocation(currentNode, currentPath, &loc) == 0)
      {
         if(Node_addChild(currentNode, currentPath, loc) != SUCCESS)
         {
            free(copyPath);
            free(currentPath);
            return MEMORY_ERROR;
         }
      }
      currentNode = Node_getChild(currentNode, loc);
      currentTok = nextTok;
      nextTok = strtok(NULL, "/");
      strcat(currentPath, "/");
      strcat(currentPath, currentTok);
   }
   if(File_contains(currentNode, currentPath))
   {
      free(copyPath);
      free(currentPath);
      return ALREADY_IN_TREE;
   }
   if(Node_getLocation(currentNode, currentPath, &loc))
   {
      free(copyPath);
      free(currentPath);
      return ALREADY_IN_TREE;
   }
   free(copyPath);
   free(currentPath);
   return File_insert(currentNode, path, contents);
}

boolean FT_containsFile(char *path)
{
   char* currentPath;
   char* currentTok;
   char* nextTok;
   char* copyPath;
   size_t loc;
   Node_T currentNode = root;

   if(!isInitialized)
      return FALSE;

   assert(path != NULL);
   if(root == NULL)
      return FALSE;

   if(strcmp(Node_getPath(root), path) == 0)
      return FALSE;

   currentPath =  malloc(strlen(path) + 1);
   copyPath = malloc(strlen(path) + 1);
   assert(copyPath != NULL);
   assert(currentPath != NULL);

   strcpy(copyPath, path);
   currentTok = strtok(copyPath, "/");
   nextTok = strtok(NULL, "/");
   strcpy(currentPath, currentTok);
   while(nextTok != NULL)
   {
      if(!Node_getLocation(currentNode, currentPath, &loc)){
         free(copyPath);
         free(currentPath);
         return FALSE;
      }
      currentNode = Node_getChild(currentNode, loc);
      currentTok = nextTok;
      nextTok = strtok(NULL, "/");
      strcat(currentPath, "/");
      strcat(currentPath, currentTok);
   }
   if(File_contains(currentNode, currentPath))
   {
      free(copyPath);
      free(currentPath);
      return TRUE;
   }
   free(copyPath);
   free(currentPath);
   return FALSE;
}

int FT_rmFile(char *path){
   char* currentPath;
   char* currentTok;
   char* nextTok;
   char* copyPath;
   size_t loc;
   Node_T currentNode = root;

   if(!isInitialized)
      return INITIALIZATION_ERROR;

   assert(path != NULL);
   if(root == NULL)
      return NO_SUCH_PATH;

   if(strcmp(Node_getPath(root),path) == 0)
      return NOT_A_FILE;

   currentPath =  malloc(strlen(path) + 1);
   copyPath = malloc(strlen(path) + 1);
   assert(currentPath != NULL);
   assert(copyPath != NULL);

   strcpy(copyPath, path);
   currentTok = strtok(copyPath, "/");
   nextTok = strtok(NULL, "/");
   strcpy(currentPath, currentTok);
   while(nextTok != NULL)
   {
      if(!Node_getLocation(currentNode, currentPath, &loc)){
         free(copyPath);
         free(currentPath);
         return NO_SUCH_PATH;
      }
      currentNode = Node_getChild(currentNode, loc);
      currentTok = nextTok;
      nextTok = strtok(NULL, "/");
      strcat(currentPath, "/");
      strcat(currentPath, currentTok);
   }
   if(File_contains(currentNode, currentPath))
   {
      File_rmFile(currentNode, currentPath);
      free(copyPath);
      free(currentPath);
      return SUCCESS;
   }
   if(Node_getLocation(currentNode, currentPath, &loc)){
      free(currentPath);
      free(copyPath);
      return NOT_A_FILE;
   }
   free(currentPath);
   free(copyPath);
   return NO_SUCH_PATH;
}

void *FT_getFileContents(char *path){
   char* currentPath;
   char* currentTok;
   char* nextTok;
   char* copyPath;
   size_t loc;
   Node_T currentNode = root;

   if(!isInitialized)
      return NULL;

   assert(path != NULL);

   if(root == NULL)
      return NULL;

   currentPath =  malloc(strlen(path) + 1);
   copyPath = malloc(strlen(path) + 1);
   assert(currentPath != NULL);
   assert(copyPath != NULL);
   strcpy(copyPath, path);
   currentTok = strtok(copyPath, "/");
   nextTok = strtok(NULL, "/");
   strcpy(currentPath, currentTok);
   while(nextTok != NULL)
   {
      if(!Node_getLocation(currentNode, currentPath, &loc)){
         free(copyPath);
         free(currentPath);
         return NULL;
      }
      currentNode = Node_getChild(currentNode, loc);
      currentTok = nextTok;
      nextTok = strtok(NULL, "/");
      strcat(currentPath, "/");
      strcat(currentPath, currentTok);
   }
   if(File_contains(currentNode, currentPath))
   {
      free(currentPath);
      free(copyPath);
      return File_getcontents(currentNode, path);
   }
   free(currentPath);
   free(copyPath);
   return NULL;
}

void *FT_replaceFileContents(char *path, void *newContents,
                             size_t newLength)
{
   char* currentPath;
   char* currentTok;
   char* nextTok;
   char* copyPath;
   size_t loc;
   Node_T currentNode = root;

   if(!isInitialized)
      return NULL;

   assert(path != NULL);
   if(root == NULL)
      return NULL;

   currentPath =  malloc(strlen(path) + 1);
   copyPath = malloc(strlen(path) + 1);
   assert(currentPath != NULL);
   assert(copyPath != NULL);
   strcpy(copyPath, path);
   currentTok = strtok(copyPath, "/");
   nextTok = strtok(NULL, "/");
   strcpy(currentPath, currentTok);
   while(nextTok != NULL)
   {
      if(!Node_getLocation(currentNode, currentPath, &loc)){
         free(copyPath);
         free(currentPath);
         return NULL;
      }
      currentNode = Node_getChild(currentNode, loc);
      currentTok = nextTok;
      nextTok = strtok(NULL, "/");
      strcat(currentPath, "/");
      strcat(currentPath, currentTok);
   }
   if(File_contains(currentNode, currentPath))
   {
      free(copyPath);
      free(currentPath);
      return File_replace(currentNode, path, newContents);
   }
   free(currentPath);
   free(copyPath);
   return NULL;
}

int FT_stat(char *path, boolean *type, size_t *length)
{
   char* currentPath;
   char* currentTok;
   char* nextTok;
   char* copyPath;
   size_t loc;
   Node_T currentNode = root;

   if(!isInitialized)
      return INITIALIZATION_ERROR;

   assert(path != NULL);
   if(root == NULL)
      return NO_SUCH_PATH;

   if(strcmp(Node_getPath(root), path) == 0)
   {
      *type = FALSE;
      return SUCCESS;
   }

   currentPath =  malloc(strlen(path) + 1);
   copyPath = malloc(strlen(path) + 1);
   assert(currentPath != NULL);
   assert(copyPath != NULL);
   strcpy(copyPath, path);
   while(nextTok != NULL)
   {
      if(!Node_getLocation(currentNode, currentPath, &loc)){
         free(currentPath);
         free(copyPath);
         return NO_SUCH_PATH;
      }
      currentNode = Node_getChild(currentNode, loc);
      currentTok = nextTok;
      nextTok = strtok(NULL, "/");
      strcat(currentPath, "/");
      strcat(currentPath, currentTok);
   }
   if(File_contains(currentNode, currentPath))
   {
      *type = TRUE;
      *length = sizeof(File_getcontents(currentNode, path));
      free(currentPath);
      free(copyPath);
      return SUCCESS;
   }
   if(Node_getLocation(currentNode, currentPath, &loc))
   {
      currentNode = Node_getChild(currentNode, loc);
      *type = FALSE;
      free(currentPath);
      free(copyPath);
      return SUCCESS;
   }
   free(currentPath);
   free(copyPath);
   return NO_SUCH_PATH;
}

int FT_init(void)
{
   if(isInitialized)
      return INITIALIZATION_ERROR;
   isInitialized = 1;
   root = NULL;
   return SUCCESS;
}

int FT_destroy(void)
{
   if(!isInitialized)
      return INITIALIZATION_ERROR;
   assert(root != NULL);
   Node_destroy(root);
   root = NULL;
   isInitialized = 0;
   return SUCCESS;
}

/*
   Performs a pre-order traversal of the tree rooted at n,
   inserting each payload to DynArray_T d beginning at index i.
   Returns the next unused index in d after the insertion(s).
*/
static size_t FT_preOrderTraversal(Node_T n , DynArray_T d,
                                   DynArray_T f, size_t i)
{
   size_t c;
   assert(d != NULL);

   if(n != NULL) {
      (void) DynArray_set(d, i, Node_getPath(n));

      for(c = 0; c < Node_getNumFiles(n); c++)
         (void) DynArray_add(f, File_getFileName(n, c));

      i++;
      for(c = 0; c < Node_getNumChildren(n); c++)
         i = FT_preOrderTraversal(Node_getChild(n, c), d, f, i);
   }
   return i;
}

/*
   Alternate version of strlen that uses pAcc as an in-out parameter
   to accumulate a string length, rather than returning the length of
   str, and also always adds one more in addition to str's length.
*/
static void FT_strlenAccumulate(char* str, size_t* pAcc) {
   assert(pAcc != NULL);

   if(str != NULL)
      *pAcc += (strlen(str) + 1);
}

/*
   Alternate version of strcat that inverts the typical argument
   order, appending str onto acc, and also always adds a newline at
   the end of the concatenated string.
*/
static void FT_strcatAccumulate(char* str, char* acc) {
   assert(acc != NULL);

   if(str != NULL)
      strcat(acc, str); strcat(acc, "\n");
}

char *FT_toString(void)
{
   DynArray_T directories;
   DynArray_T files;
   size_t totalStrlen = 1;
   char* result = NULL;

   if(!isInitialized)
      return NULL;

   directories = DynArray_new(0);
   files = DynArray_new(0);

   (void) FT_preOrderTraversal(root, directories, files, 0);

   DynArray_map(directories,
                (void (*)(void*, void*)) FT_strlenAccumulate,
                (void*) &totalStrlen);
   DynArray_map(files,
                (void (*)(void*, void*)) FT_strlenAccumulate,
                (void*) &totalStrlen);

   result = malloc(totalStrlen);
   if(result == NULL)
   {
      DynArray_free(directories);
      DynArray_free(files);
      return NULL;
   }
   *result = '\0';

   DynArray_map(directories,
                (void (*)(void*, void*)) FT_strcatAccumulate,
                (void*) result);
   DynArray_map(files,
                (void (*)(void*, void*)) FT_strcatAccumulate,
                (void*) result);

   DynArray_free(directories);
   DynArray_free(files);
   return result;
}
