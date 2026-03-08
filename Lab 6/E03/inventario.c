#include "inventario.h"

tabInv_t *initTabInv(tabInv_t *tabInv){
    tabInv_t *x = malloc(sizeof(tabInv_t));
    return x;
}
void importEq(tabInv_t *tabInv){
    int N;
    FILE *fin = fopen("../inventario.txt", "r");
    if(fin == NULL){
        printf("\nIl file inventario non esiste");
        exit(-1);
    }
    fscanf(fin, "%d\n", &N);
    tabInv->nInv = N; tabInv->maxInv = N;
    tabInv->vettInv = malloc(N * sizeof(inv_t));
    for(int i = 0; i < N; i++){
        fscanf(fin, "%s %s %d %d %d %d %d %d", tabInv->vettInv[i].nome, tabInv->vettInv[i].tipo,
               &tabInv->vettInv[i].stat.hp, &tabInv->vettInv[i].stat.mp, &tabInv->vettInv[i].stat.atk,
               &tabInv->vettInv[i].stat.def, &tabInv->vettInv[i].stat.mag, &tabInv->vettInv[i].stat.spr);
    }

    fclose(fin);
}
int searchObj(tabInv_t *tabInv){
    int i = 0;
    char s[MAXLEN];
    printf("\nInserisci il nome dell'oggetto che vuoi cercare:\n");
    scanf("%s", s);
    while(i < tabInv->nInv){
        if(strcmp(s, tabInv->vettInv[i].nome) == 0){
            printf("\nHo trovato un oggetto di nome '%s' nell'inventario!\n\n", s);
            return i;
        }
        i++;
    }
    printf("\nNon esiste un oggetto chiamato '%s' nell' inventario\n\n", s);
    return -1;
}
void printObj(tabInv_t *tabInv, int i){
    printf("\nStampo i dettagli dell'oggetto cercato:\n\n");
    printf("Nome: %s\n", tabInv->vettInv[i].nome);
    printf("Tipo: %s\n", tabInv->vettInv[i].tipo);
    printf("Mod. hp: %d\n", tabInv->vettInv[i].stat.hp);
    printf("Mod. mp: %d\n", tabInv->vettInv[i].stat.mp);
    printf("Mod. atk: %d\n", tabInv->vettInv[i].stat.atk);
    printf("Mod. def: %d\n", tabInv->vettInv[i].stat.def);
    printf("Mod. mag: %d\n", tabInv->vettInv[i].stat.mag);
    printf("Mod. spr: %d\n", tabInv->vettInv[i].stat.spr);
}