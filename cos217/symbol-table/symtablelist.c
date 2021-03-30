/*--------------------------------------------------------------------*/
/* stack.c (Version 5)                                                */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "symtable.h"

/*--------------------------------------------------------------------*/

/* Each item is stored in a StackNode.  StackNodes are linked to
   form a list.  */

struct SymTableNode
{
    /* The key. */
   const char *pcKey;
   /* The value. */
   const void *pvValue;

   /* The address of the next StackNode. */
   struct SymTableNode *psNextNode;
};

/*--------------------------------------------------------------------*/

/* A Stack is a structure that points to the first StackNode. */

struct SymTable
{
   /* The address of the first SymTableNode. */
   struct SymTableNode *psFirstNode;
   size_t numNodes;
};

/*--------------------------------------------------------------------*/

SymTable_T SymTable_new(void)
{
   SymTable_T oSymTable;

   oSymTable = (SymTable_T)malloc(sizeof(struct SymTable));
   if (oSymTable == NULL)
      return NULL;

   oSymTable->psFirstNode = NULL;
   oSymTable->numNodes = 0;
   return oSymTable;
}

/*--------------------------------------------------------------------*/

void SymTable_free(SymTable_T oSymTable)
{
   struct SymTableNode *psCurrentNode;
   struct SymTableNode *psNextNode;

   assert(oSymTable != NULL);

   for (psCurrentNode = oSymTable->psFirstNode;
        psCurrentNode != NULL;
        psCurrentNode = psNextNode)
   {
      psNextNode = psCurrentNode->psNextNode;
      free(psCurrentNode);
   }
   oSymTable->numNodes = 0;

   free(oSymTable);
}

/*--------------------------------------------------------------------*/
size_t SymTable_getLength(SymTable_T oSymTable)
{
    assert(oSymTable != NULL);
    return (oSymTable->numNodes);
}
/*--------------------------------------------------------------------*/

int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue)
{
   struct SymTableNode *psNewNode;
   int contains;

   assert(oSymTable != NULL);

   psNewNode = (struct SymTableNode*)malloc(sizeof(struct SymTableNode));
   contains = SymTable_contains(oSymTable, pcKey);
   if ((psNewNode == NULL) || (contains == 1))
      return 0;
   psNewNode->pvValue = pvValue;
   psNewNode->pcKey = (const char*)malloc(strlen(pcKey)+1);
   strcpy((char*)psNewNode->pcKey, pcKey);
   psNewNode->psNextNode = oSymTable->psFirstNode;
   oSymTable->psFirstNode = psNewNode;
   oSymTable->numNodes = oSymTable->numNodes+1;
   return 1;
}

void *SymTable_replace(SymTable_T oSymTable, const char *pcKey,
    const void *pvValue)
{
    struct SymTableNode *psCurrentNode;
    const void *pvOldValue;
    int comparison;
    assert(oSymTable != NULL);
    for (psCurrentNode = oSymTable->psFirstNode;
        psCurrentNode != NULL;
        psCurrentNode = psCurrentNode->psNextNode)
    {
        comparison = strcmp(pcKey, psCurrentNode->pcKey);
        if (comparison == 0){
            pvOldValue = psCurrentNode->pvValue;
            psCurrentNode->pvValue = pvValue;
            return (void*) pvOldValue;
        }
    }
    return NULL;
}

int SymTable_contains(SymTable_T oSymTable, const char *pcKey)
{
    struct SymTableNode *psCurrentNode;
    int comparison;
    assert(oSymTable != NULL);
    for (psCurrentNode = oSymTable->psFirstNode;
        psCurrentNode != NULL;
        psCurrentNode = psCurrentNode->psNextNode)
    {
        comparison = strcmp(pcKey, psCurrentNode->pcKey);
        if (comparison == 0){
            return 1;
        }
    }
    return 0;
}

void *SymTable_get(SymTable_T oSymTable, const char *pcKey)
{
    struct SymTableNode *psCurrentNode;
    assert(oSymTable != NULL);
    for (psCurrentNode = oSymTable->psFirstNode;
        psCurrentNode != NULL;
        psCurrentNode = psCurrentNode->psNextNode)
    {
        int comparison = strcmp(pcKey, psCurrentNode->pcKey);
        if (comparison == 0){
            return (void*)(psCurrentNode->pvValue);
        }
    }
    return NULL;

}

void *SymTable_remove(SymTable_T oSymTable, const char *pcKey)
{
    const void *pvValue;
    struct SymTableNode *psCurrentNode;
    struct SymTableNode *psPrevNode;

   assert(oSymTable != NULL);
   /* checks if the SymTable contains a node with the same key */
   if (SymTable_contains(oSymTable, pcKey) == 0){
       return NULL;
   }
   /* Checks if the first node has the same key */
   psCurrentNode = oSymTable->psFirstNode;
   int comparison = strcmp(pcKey, psCurrentNode->pcKey);
   if (comparison == 0){
       oSymTable->numNodes = oSymTable->numNodes-1;
       pvValue = psCurrentNode->pvValue;
       oSymTable->psFirstNode = psCurrentNode->psNextNode;
       free(psCurrentNode);
       return (void*) pvValue;
   }

   /* Checks if the remaining nodes has the same key */
   while (psCurrentNode != NULL){
        psPrevNode = psCurrentNode;
        psCurrentNode = psCurrentNode->psNextNode;

        int comparison = strcmp(pcKey, psCurrentNode->pcKey);
        if (comparison == 0){
            oSymTable->numNodes = oSymTable->numNodes-1;
            pvValue = psCurrentNode->pvValue;
            psCurrentNode = psCurrentNode->psNextNode;
            psPrevNode->psNextNode = psCurrentNode;
            free(psCurrentNode);
            return (void*) pvValue;
        }
    }
}

void SymTable_map(SymTable_T oSymTable,
    void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),
    const void *pvExtra)
{
    struct SymTableNode *psCurrentNode;
    assert(oSymTable != NULL);
    assert(pfApply != NULL);

   for (psCurrentNode = oSymTable->psFirstNode;
        psCurrentNode != NULL;
        psCurrentNode = psCurrentNode->psNextNode)
      (*pfApply)((const char*)psCurrentNode->pcKey, (void*)psCurrentNode->pvValue,
      (void*) pvExtra);
}



