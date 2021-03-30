/*--------------------------------------------------------------------*/
/* stack.c (Version 5)                                                */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "symtable.h"

/* Return a hash code for pcKey that is between 0 and uBucketCount-1,
        inclusive. */
        
static size_t SymTable_hash(const char *pcKey, size_t uBucketCount)
{
        const size_t HASH_MULTIPLIER = 65599;
        size_t u;
        size_t uHash = 0;

        assert(pcKey != NULL);

        for (u = 0; pcKey[u] != '\0'; u++)
        uHash = uHash * HASH_MULTIPLIER + (size_t)pcKey[u];
        
        return uHash % uBucketCount;
}




typedef struct SymTableNode SymTableNode;
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

/* A SymTable is an array of buckets. */
struct SymTable {

    struct SymTableNode **bucketArray;
    size_t numNodes;
    size_t numBuckets;

};

/*--------------------------------------------------------------------*/

SymTable_T SymTable_new(void)
{
    const size_t INITIAL_LENGTH = 509;
    SymTable_T oSymTable;


   oSymTable = (SymTable_T)malloc(sizeof(struct SymTable));
   if (oSymTable == NULL)
      return NULL;
    oSymTable->numBuckets = INITIAL_LENGTH;
    oSymTable->numNodes = 0;
    oSymTable->bucketArray = (SymTableNode**)calloc(oSymTable->numBuckets, 
    sizeof(SymTableNode*));

    if (oSymTable->bucketArray == NULL){
        free(oSymTable);
        return NULL;
    }
    int i;
    for (i = 0; i< oSymTable->numBuckets; i++){
        oSymTable->bucketArray[i] = NULL;
    } 
   return oSymTable;
}

/*--------------------------------------------------------------------*/

void SymTable_free(SymTable_T oSymTable)
{
   struct SymTableNode *psCurrentNode;
   struct SymTableNode *psNextNode;
   struct SymTableNode *bucket;

   assert(oSymTable != NULL);
   int i;
   for (i=0; i<oSymTable->numNodes; i++) {
        bucket = oSymTable->bucketArray[i];
        if (bucket != NULL){
            for (psCurrentNode = bucket;
            psCurrentNode != NULL; psCurrentNode = psNextNode){
                psNextNode = psCurrentNode->psNextNode;
                free(psCurrentNode);
                }
        }
    }
 
    free(oSymTable->bucketArray);
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
   size_t hashCode;

   assert(oSymTable != NULL);

   psNewNode = (struct SymTableNode*)malloc(sizeof(struct SymTableNode));
   if (psNewNode == NULL){
       return 0;
   }
   contains = SymTable_contains(oSymTable, pcKey);
   if (contains == 1){
       return 0;
   }
   hashCode = SymTable_hash(pcKey, oSymTable->numBuckets);
   psNewNode->pvValue = pvValue;
   psNewNode->pcKey = (const char*)malloc(strlen(pcKey)+1);
   if (psNewNode->pcKey == NULL){
       return 0;
   } 
   strcpy((char*)psNewNode->pcKey, pcKey);
   psNewNode->psNextNode = oSymTable->bucketArray[hashCode];
   oSymTable->bucketArray[hashCode] = psNewNode;
   oSymTable->numNodes = oSymTable->numNodes+1;
   return 1;
}

void *SymTable_replace(SymTable_T oSymTable, const char *pcKey,
    const void *pvValue)
{
    struct SymTableNode *psCurrentNode;
    struct SymTableNode *bucket;
    const void *pvOldValue;
    int comparison;
    size_t hashCode;

    assert(oSymTable != NULL);
    hashCode = SymTable_hash(pcKey, oSymTable->numBuckets);
    bucket = oSymTable->bucketArray[hashCode];
    for (psCurrentNode = bucket;
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
    struct SymTableNode *bucket; 
    int comparison;
    int i;
    size_t hashCode;
    assert(oSymTable != NULL);
    hashCode = SymTable_hash(pcKey, oSymTable->numBuckets);
    bucket = oSymTable->bucketArray[hashCode];
    for (psCurrentNode = bucket; psCurrentNode != NULL; 
        psCurrentNode = psCurrentNode->psNextNode){
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
    struct SymTableNode *bucket; 
    size_t hashCode;

    assert(oSymTable != NULL);
    hashCode = SymTable_hash(pcKey, oSymTable->numBuckets);
    bucket = oSymTable->bucketArray[hashCode];

    for (psCurrentNode = bucket;
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
    struct SymTableNode *bucket; 
    size_t hashCode;
    int comparison;


   assert(oSymTable != NULL);
   hashCode = SymTable_hash(pcKey, oSymTable->numBuckets);
   bucket = oSymTable->bucketArray[hashCode];
   /* checks if the SymTable contains a node with the same key */
   if (SymTable_contains(oSymTable, pcKey) == 0){
       return NULL;
   }
   /* Checks if the first node has the same key */
   psCurrentNode = bucket;
   comparison = strcmp(pcKey, psCurrentNode->pcKey);
   if (comparison == 0){
       oSymTable->numNodes = oSymTable->numNodes-1;
       pvValue = psCurrentNode->pvValue;
       oSymTable->bucketArray[hashCode] = psCurrentNode->psNextNode;
       free(psCurrentNode);
       return (void*) pvValue;
   }

   /* Checks if the remaining nodes has the same key */
   while (psCurrentNode != NULL){
        psPrevNode = psCurrentNode;
        psCurrentNode = psCurrentNode->psNextNode;

        comparison = strcmp(pcKey, psCurrentNode->pcKey);
        if (comparison == 0){
            oSymTable->numNodes = oSymTable->numNodes-1;
            pvValue = psCurrentNode->pvValue;
            psCurrentNode = psCurrentNode->psNextNode;
            psPrevNode->psNextNode = psCurrentNode;
            free(psCurrentNode);
            return (void*) pvValue;
        }
    }
    return NULL;
}

void SymTable_map(SymTable_T oSymTable,
    void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),
    const void *pvExtra)
{
    struct SymTableNode *psCurrentNode;
    struct SymTableNode *bucket; 
    size_t hashCode;


    assert(oSymTable != NULL);
    assert(pfApply != NULL);
    int i;
    for (i = 0; i<oSymTable->numBuckets; i++){
        bucket = oSymTable->bucketArray[i];
        for (psCurrentNode = bucket; psCurrentNode != NULL;
            psCurrentNode = psCurrentNode->psNextNode){
                (*pfApply)((const char*)psCurrentNode->pcKey, 
                (void*)psCurrentNode->pvValue, (void*) pvExtra);
            }
    }
}



