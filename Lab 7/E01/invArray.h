#ifndef INVARRAYH
#define INVARRAYH

#include "inv.h"
#include <string.h>
typedef struct invArray_t *invArray;

invArray initInvArray();
void invArray_readFile(FILE *fin, invArray v);
void invArray_searchObj(invArray v, char *cmd);
int invArray_searchIndexObj(invArray v);
void freeInvArray(invArray v);
void invArray_printFromIndex(int i, invArray inv);
int invArray_getHp(invArray inv, int i);
int invArray_getMp(invArray inv, int i);
int invArray_getAtk(invArray inv, int i);
int invArray_getDef(invArray inv, int i);
int invArray_getMag(invArray inv, int i);
int invArray_getSpr(invArray inv, int i);

#endif