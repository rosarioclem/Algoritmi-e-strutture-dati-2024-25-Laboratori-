#include "inv.h"

void inv_getName(inv_t *el){
    printf("Nome: %s\n", el->nome);
}
void inv_getType(inv_t *el){
    printf("Tipo: %s\n", el->tipo);
}
void inv_getStats(inv_t *el){
    printf("\nLe statistiche dell' oggetto sono:\n\n");
    printf("Mod. hp: %d\n", el->stat.hp);
    printf("Mod. mp: %d\n", el->stat.mp);
    printf("Mod. atk: %d\n", el->stat.atk);
    printf("Mod. def: %d\n", el->stat.def);
    printf("Mod. mag: %d\n", el->stat.mag);
    printf("Mod. spr: %d\n", el->stat.spr);
}
void inv_updateStats(inv_t *el, stat_t *newStats){
    el->stat.hp = newStats->hp;
    el->stat.mp = newStats->mp;
    el->stat.atk = newStats->atk;
    el->stat.def = newStats->def;
    el->stat.mag = newStats->mag;
    el->stat.spr = newStats->spr;
}
void inv_printObj(inv_t *el){
    printf("Stampo tutti i dettagli dell'oggetto:\n\n");
    inv_getName(el);
    inv_getType(el);
    inv_getStats(el);
}
void inv_readObj(FILE *fp, inv_t *el){
    fscanf(fp, "%s %s", el->nome, el->tipo);
    inv_readStats(fp, &el->stat);
}
void inv_readStats(FILE *fp, stat_t *sp){
    fscanf(fp, "%d %d %d %d %d %d", &sp->hp, &sp->mp, &sp->atk, &sp->def, &sp->mag, &sp->spr);
}