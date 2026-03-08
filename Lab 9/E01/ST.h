#ifndef ST_H
#define ST_H
#include "Item.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct symboltable *ST;

ST STinit(int maxN, float alpha);
void STinsert(ST st, Item val);
int STsearch(ST st, char *label);
int hash(char *v, int M);
int STcount(ST st);
void STfree(ST st);
char *STsearchByIndex(ST st, int i);

#endif
