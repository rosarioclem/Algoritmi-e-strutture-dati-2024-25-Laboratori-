#include "Item.h"

int ITEMcmp(Item *a, Item *b){
    if(strcmp(a->id_elab, b->id_elab) == 0)
        return 0;

    return -1;
}
void ITEMcopyArray(Item *dest, Item *source, int num){
    for(int i = 0; i < num; i++)
        dest[i] = source[i];
}
int ITEMalphCmp(const void *a, const void *b){
    return strcmp(ITEMgetElab((Item *) a), ITEMgetElab((Item *) b));
}
char *ITEMgetElab(Item *a){
    return a->id_elab;
}