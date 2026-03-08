#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 31

typedef struct{
    char id_elab[MAXLEN], id_rete[MAXLEN];
} Item;

int ITEMcmp(Item *a, Item *b);
void ITEMcopyArray(Item *dest, Item *source, int num);
int ITEMalphCmp(const void *a, const void *b);
char *ITEMgetElab(Item *a);

#endif