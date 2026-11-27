/*--------------------------------------------------------------------*/
/* symtable.h                                                         */
/* Author: Sean Wang                                                  */
/*--------------------------------------------------------------------*/


#ifndef SYMTABLE_INCLUDED
#define SYMTABLE_INCLUDED
#include <stddef.h>

/* A SymTable_T is an unordered collection of bindings/nodes
Nodes and bindings mean the same thing */
typedef struct SymTable *SymTable_T;

/* Return a new SymTable_T object, or NULL if insufficient memory is
   available. */
SymTable_T SymTable_new(void);

/* Free oSymTable. */
void SymTable_free(SymTable_T oSymTable);

/* Return the number of nodes in oSymTable */
size_t SymTable_getLength(SymTable_T oSymTable);

/* Push a node with key pcKey and value pvValue onto oSymTable if no node with 
key pcKey exists.  
Return 1 (TRUE) if successful, or 0 (FALSE) if insufficient memory is available. */
int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue);

/* Replace value of node in oSymTable with key pcKey to pvValue 
and return the old value. Return NULL if unsuccessful. */
void *SymTable_replace(SymTable_T oSymTable, const char *pcKey,
    const void *pvValue);

/* Return 1 (TRUE) if oSymTable contains a node whose key is pcKey, 
and 0 (FALSE) otherwise. */
int SymTable_contains(SymTable_T oSymTable, const char *pcKey);

/* Return the value of the node within oSymTable whose key is pcKey, 
or NULL if no such node exists.*/
void *SymTable_get(SymTable_T oSymTable, const char *pcKey);

/* Remove and return a node with pcKey of oSymTable. 
If unsuccesful return NULL */
void *SymTable_remove(SymTable_T oSymTable, const char *pcKey);

/* Apply (*pfApply)(pcKey, pvValue, pvExtra) for each 
pcKey/pvValue binding in oSymTable. */
void SymTable_map(SymTable_T oSymTable,
    void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),
    const void *pvExtra);

#endif