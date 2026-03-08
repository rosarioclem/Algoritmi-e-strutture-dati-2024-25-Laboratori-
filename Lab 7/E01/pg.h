#ifndef PGH
#define PGH

#include "equipArray.h"
#include "invArray.h"
#include "inv.h"

typedef struct{
    char codice[7];
    char nome[MAXLEN];
    char classe[MAXLEN];
    equipArray equip;
    stat_t stats;
}pg_t;

int pg_read(FILE *fp, pg_t *p_pg);
void pg_clean(pg_t *p_pg);
void pg_print(pg_t *p_pg, invArray inv);
char *pg_getCode(pg_t *p_pg);
void pg_recalcStats(pg_t *p_pg, char* cmd, int i, invArray inv);
void pg_addObj(pg_t *p_pg, invArray inv);
void pg_removeObj(pg_t *p_pg, invArray inv);
pg_t pg_stdin();

#endif