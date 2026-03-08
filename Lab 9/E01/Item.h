#ifndef ITEM_H
#define ITEM_H
#include <string.h>
#define MAXLEN 21

typedef struct item{
    char name[MAXLEN];
    int index;
}Item;

Item ITEMsetNull();
Item ITEMcreate(char *name, int index);
int ITEMcheckNull(Item a);
int KEYcmp(Item a, char *label);

#endif
