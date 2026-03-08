#ifndef ST_H
#define ST_H
#include "Item.h"

typedef struct symboltab *ST;

ST STinit(char *filename, int *numE);
int STsearch(ST st, Item *tmp);
void STinsert(ST st, Item *tmp);
int STcount(ST st);
void STprintName(ST st, int index);
void STfree(ST st);
Item *STgetItems(ST st);
Item STgetItem(ST st, int index);
int STsearchIndex(ST st, char *name);

#endif