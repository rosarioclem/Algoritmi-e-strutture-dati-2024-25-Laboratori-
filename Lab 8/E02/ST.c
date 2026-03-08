#include "ST.h"

struct symboltab{
    Item *v;
    int numSym;
};

ST STinit(char *filename, int *numE){
    Item tmp1, tmp2;
    int tmp;
    FILE *fin = fopen(filename, "r");
    if(fin == NULL) {
        printf("Il file non esiste\n");
        return NULL;
    }
    ST st = malloc(sizeof(*st));
    if(st == NULL){
        printf("Qualcosa e' andato storto con l'allocazione della tabella di simboli\n");
        return NULL;
    }
    st->numSym = 0;

    while(fscanf(fin, "%s %s %s %s %d", tmp1.id_elab, tmp1.id_elab, tmp1.id_elab, tmp1.id_elab, &tmp) == 5)
        (*numE)++;
    st->v = malloc((*numE) * sizeof(Item));
    fclose(fin);

    fin = fopen(filename, "r");
    while(fscanf(fin, "%s %s %s %s %d", tmp1.id_elab, tmp1.id_rete, tmp2.id_elab, tmp2.id_rete, &tmp) == 5){
        if(STsearch(st, &tmp1) == -1){
            STinsert(st, &tmp1);
            st->numSym++;
        }
        if(STsearch(st, &tmp2) == -1){
            STinsert(st, &tmp2);
            st->numSym++;
        }
    }

    fclose(fin);
    return st;
}
int STsearch(ST st, Item *tmp){
    int i;
    for(i = 0; i < st->numSym; i++){
        if(ITEMcmp(&st->v[i], tmp) == 0)
        return i;
    }

    return -1;
}
void STinsert(ST st, Item *tmp){
    st->v[st->numSym] = *tmp;
}
int STcount(ST st){
    return st->numSym;
}
void STprintName(ST st, int index){
    printf("%s", st->v[index].id_elab);
}
void STfree(ST st){
    free(st->v);
    free(st);
}
Item *STgetItems(ST st){
    return st->v;
}
Item STgetItem(ST st, int index){
    return st->v[index];
}
int STsearchIndex(ST st, char *name){
    Item a;
    strcpy(a.id_elab, name);
    strcpy(a.id_rete, "");

    return STsearch(st, &a);
}