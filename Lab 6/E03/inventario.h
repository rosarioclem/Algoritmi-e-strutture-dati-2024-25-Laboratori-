#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 51
typedef struct{
    int hp, mp, atk, def, mag, spr;
}stat_t;
typedef struct{
    char nome[MAXLEN], tipo[MAXLEN];
    stat_t stat;
}inv_t;
typedef struct{
    int inUso;
    int nOggetti;
    inv_t **vettEq;
}tabEquip_t;
typedef struct{
    inv_t *vettInv;
    int nInv, maxInv;
}tabInv_t;

tabInv_t *initTabInv(tabInv_t *tabInv);
void importEq(tabInv_t *tabInv);
int searchObj(tabInv_t *tabInv);
void printObj(tabInv_t *tabInv, int i);