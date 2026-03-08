#ifndef PGLISTH
#define PGLISTH

#include "pg.h"

typedef struct node *link;
typedef struct pgList_t *pgList;

pgList initPgList();
void pgList_freeList(pgList list);
void pgList_pgInsertion(pgList L, pg_t *p_pg);
link pgList_NEW(pg_t *p_pg);
link pgList_searchPg(pgList L, char *code);
void pgList_editEquipment(pgList L, invArray inv, char *cmd);
void pgList_addPg(pgList L);
void pgList_removePg(pgList L);
int pgList_checkInput(pgList L, pg_t *newPg);
void pgList_printPg(pgList L, invArray inv);

#endif