/*--------------------------------------------------------------------*/
/* symtablehash.c                                                     */
/* Author: Sean Wang                                                  */
/*--------------------------------------------------------------------*/

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "symtable.h"
#include <stdio.h>

/* Array of bucket counts */
static size_t BUCKET_COUNTS[] = {509, 1021, 2039, 4093, 8191, 16381, 32749, 65521};
/* Index for the current bucket count */
static size_t INDEX_BUCKET_COUNTS = 0;
/* A SymTableNode holds each node which consists of a key and a value */
typedef struct SymTableNode SymTableNode;

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

/* Each item is stored in a SymTableNode.  SymTableNodes are linked to
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

/* A SymTable is an array of buckets which point to a SymTableNode. */
struct SymTable {
    /* The array in which the buckets are stored */
    struct SymTableNode **bucketArray;
    /* The number of nodes in the SymTable */
    size_t numNodes;
    /* The number of buckets in the SymTable */
    size_t numBuckets;

};

/*--------------------------------------------------------------------*/

SymTable_T SymTable_new(void)
{
    const size_t INITIAL_LENGTH = 509;
    SymTable_T oSymTable;
    size_t i;

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
   size_t i;

   assert(oSymTable != NULL);
   for (i=0; i<oSymTable->numBuckets; i++) {
        bucket = oSymTable->bucketArray[i];
        for (psCurrentNode = bucket;
            psCurrentNode != NULL; psCurrentNode = psNextNode){
                psNextNode = psCurrentNode->psNextNode;
                free((char*)psCurrentNode->pcKey);
                free(psCurrentNode);
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

/* Increase the physical length (number of buckets) of *oSymTable.  
Return 1 (TRUE) if successful, or 0 (FALSE) 
if insufficient memory is available. */

static int SymTable_grow(SymTable_T oSymTable)
{
   size_t newNumBuckets;
   size_t hashCode;
   struct SymTableNode **newBucketArray;
   struct SymTableNode *bucket;
   struct SymTableNode *psNewNode;
   struct SymTableNode *psCurrentNode;
   struct SymTableNode *psNextNode;
   size_t i;
   assert(oSymTable != NULL);
   
   /* Unsuccessful when INDEX_BUCKET_COUNTS reaches the last element 
   of BUCKET_COUNTS */
   if (INDEX_BUCKET_COUNTS+1 == (sizeof(BUCKET_COUNTS)/sizeof(*BUCKET_COUNTS))){
       return 0;
   }
   newNumBuckets = BUCKET_COUNTS[INDEX_BUCKET_COUNTS+1];
   newBucketArray = (SymTableNode**)
      malloc(sizeof(SymTableNode*) * newNumBuckets);
   if (newBucketArray == NULL){
       return 0;
   }
   /* Initialize all the values in newBucketArray to null */
   for (i = 0; i< newNumBuckets; i++){
        newBucketArray[i] = NULL;
    } 
   
   /* loop through the current bucket array and copy then 
   reposition the nodes in the new bucket array */
   for (i = 0; i<oSymTable->numBuckets; i++){
       bucket = oSymTable->bucketArray[i];
       for (psCurrentNode = bucket; psCurrentNode != NULL;
            psCurrentNode = psCurrentNode->psNextNode){
                psNewNode = (struct SymTableNode*)malloc(sizeof(struct SymTableNode));
                if (psNewNode == NULL){
                    return 0;
                }
                hashCode = SymTable_hash(psCurrentNode->pcKey, newNumBuckets);
                psNewNode->pvValue = psCurrentNode->pvValue;
                psNewNode->pcKey = (const char*)malloc(strlen(psCurrentNode->pcKey)+1);
                if (psNewNode->pcKey == NULL){
                    free(psNewNode);
                    return 0;
                } 
                strcpy((char*)psNewNode->pcKey, psCurrentNode->pcKey);
                psNewNode->psNextNode = newBucketArray[hashCode];
                newBucketArray[hashCode] = psNewNode;
        }
    }
    /* free the original array */
    for (i=0; i<oSymTable->numBuckets; i++) {
        bucket = oSymTable->bucketArray[i];
        for (psCurrentNode = bucket;
            psCurrentNode != NULL; psCurrentNode = psNextNode){
                psNextNode = psCurrentNode->psNextNode;
                free((char*)psCurrentNode->pcKey);
                free(psCurrentNode);
        }
    }
    free(oSymTable->bucketArray);

    oSymTable->numBuckets = newNumBuckets;
    oSymTable->bucketArray = newBucketArray;
    INDEX_BUCKET_COUNTS+=1;
    return 1;
}

int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue)
{
   struct SymTableNode *psNewNode;
   int contains;
   size_t hashCode;

   assert(oSymTable != NULL);
   assert(pcKey != NULL);

   psNewNode = (struct SymTableNode*)malloc(sizeof(struct SymTableNode));
   if (psNewNode == NULL){
       return 0;
   }
   contains = SymTable_contains(oSymTable, pcKey);
   if (contains == 1){
       free(psNewNode);
       return 0;
   }
   hashCode = SymTable_hash(pcKey, oSymTable->numBuckets);
   psNewNode->pvValue = pvValue;
   psNewNode->pcKey = (const char*)malloc(strlen(pcKey)+1);
   if (psNewNode->pcKey == NULL){
       free(psNewNode);
       return 0;
   } 
   strcpy((char*)psNewNode->pcKey, pcKey);
   psNewNode->psNextNode = oSymTable->bucketArray[hashCode];
   oSymTable->bucketArray[hashCode] = psNewNode;
   oSymTable->numNodes = oSymTable->numNodes+1;
   
   if (oSymTable->numNodes > BUCKET_COUNTS[INDEX_BUCKET_COUNTS]){
       SymTable_grow(oSymTable);
   }
   

   
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
    assert(pcKey != NULL);

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
    size_t hashCode;
    
    assert(oSymTable != NULL);
    assert(pcKey != NULL);

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
    assert(pcKey != NULL);

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
   assert(pcKey != NULL);

   hashCode = SymTable_hash(pcKey, oSymTable->numBuckets);
   bucket = oSymTable->bucketArray[hashCode];
 
   psCurrentNode = bucket;
   comparison = strcmp(pcKey, psCurrentNode->pcKey);

   /* Checks if the first node has the same key */
   if (comparison == 0){
       oSymTable->numNodes = oSymTable->numNodes-1;
       pvValue = psCurrentNode->pvValue;
       
       oSymTable->bucketArray[hashCode] = psCurrentNode->psNextNode;
       free((char*)psCurrentNode->pcKey);
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

            psPrevNode->psNextNode = psCurrentNode->psNextNode;;
            free((char*)psCurrentNode->pcKey);
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
    size_t i;


    assert(oSymTable != NULL);
    assert(pfApply != NULL);
    for (i = 0; i<oSymTable->numBuckets; i++){
        bucket = oSymTable->bucketArray[i];
        for (psCurrentNode = bucket; psCurrentNode != NULL;
            psCurrentNode = psCurrentNode->psNextNode){
                (*pfApply)((const char*)psCurrentNode->pcKey, 
                (void*)psCurrentNode->pvValue, (void*) pvExtra);
            }
    }
}






