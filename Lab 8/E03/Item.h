#ifndef ITEM_H
#define ITEM_H
#include <stdio.h>

typedef struct dataeora{
    int anno, mese, giorno, ora, minuti;
}Item;

Item ITEMsetNull();
int ITEMcmp(Item *i1, Item *i2);
Item ITEMgetItem();

#endif