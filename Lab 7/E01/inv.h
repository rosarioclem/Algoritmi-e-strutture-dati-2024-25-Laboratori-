#ifndef INVH
#define INVH

#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 31
typedef struct{
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
}stat_t;
typedef struct{
    char nome[MAXLEN];
    char tipo[MAXLEN];
    stat_t stat;
}inv_t;

void inv_getName(inv_t *el);
void inv_getType(inv_t *el);
void inv_getStats(inv_t *el);
void inv_updateStats(inv_t *el, stat_t *newStats);
void inv_printObj(inv_t *el);
void inv_readObj(FILE *fp, inv_t *el);
void inv_readStats(FILE *fp, stat_t *sp);

#endif