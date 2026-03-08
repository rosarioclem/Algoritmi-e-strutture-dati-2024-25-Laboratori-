#include "invArray.h"
struct invArray_t{
    inv_t *objects;
    int numObjects;
};

invArray initInvArray(){
    invArray v = malloc(sizeof(*v));
    char nomefile[MAXLEN];
    //printf("Inserisci il nome del file dell'inventario: "); scanf("%s", nomefile); printf("\n");
    FILE *fin = fopen("../inventario.txt", "r");
    if(fin == NULL){
        printf("Il file dell'inventario non esiste\n");
        exit(-1);
    }
    fscanf(fin, "%d", &v->numObjects);
    v->objects = malloc(v->numObjects * sizeof(inv_t));
    invArray_readFile(fin, v);

    return v;
}
void invArray_readFile(FILE *fin, invArray v){
    for(int i = 0; i < v->numObjects; i++)
        inv_readObj(fin, &v->objects[i]);
}
void invArray_searchObj(invArray v, char *cmd){
    stat_t newStats;
    int i = invArray_searchIndexObj(v);
    if(i != -1){
        printf("Oggetto trovato\n\n");
        if(strcmp("stampaOggetto", cmd) == 0){
            inv_printObj(&v->objects[i]);
        }else if(strcmp("modificaStatsOggetto", cmd) == 0){
            printf("Inserisci le nuove stats:\n");
            printf("Nuovi hp:"); scanf("%d", &newStats.hp); printf("\n");
            printf("Nuovi mp:"); scanf("%d", &newStats.mp); printf("\n");
            printf("Nuovo atk:"); scanf("%d", &newStats.atk); printf("\n");
            printf("Nuova def:"); scanf("%d", &newStats.def); printf("\n");
            printf("Nuova mag:"); scanf("%d", &newStats.mag); printf("\n");
            printf("Nuovo spr:"); scanf("%d", &newStats.spr); printf("\n");
            inv_updateStats(&v->objects[i], &newStats);
            printf("Statistiche aggiornate correttamente\n");
        }else
            printf("Comando non valido\n");
        return;
    }
    printf("Oggetto non trovato\n");
}
int invArray_searchIndexObj(invArray v){
    char nome[MAXLEN];
    printf("Inserisci il nome dell'oggetto da cercare: ");
    scanf("%s", nome); printf("\n");
    for(int i = 0; i < v->numObjects; i++) {
        if (strcmp(nome, v->objects[i].nome) == 0)
            return i;
    }
    printf("Oggetto non trovato\n");
    return -1;
}
void freeInvArray(invArray v){
    free(v->objects);
    free(v);
}
void invArray_printFromIndex(int i, invArray inv){
    inv_printObj(&inv->objects[i]);
}
int invArray_getHp(invArray inv, int i){
    return inv->objects[i].stat.hp;
}
int invArray_getMp(invArray inv, int i){
    return inv->objects[i].stat.mp;
}
int invArray_getAtk(invArray inv, int i){
    return inv->objects[i].stat.atk;
}
int invArray_getDef(invArray inv, int i){
    return inv->objects[i].stat.def;
}
int invArray_getMag(invArray inv, int i){
    return inv->objects[i].stat.mag;
}
int invArray_getSpr(invArray inv, int i){
    return inv->objects[i].stat.spr;
}