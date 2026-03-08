#include "inventario.h"
typedef struct{
    char codice[7], nome[MAXLEN], classe[MAXLEN];
    tabEquip_t equip;
    stat_t stat;
}pg_t;
typedef struct nodoPg_t{
    pg_t pg;
    struct nodoPg_t *next;
} *link;
typedef struct{
    link headPg, tailPg;
    int nPg;
}tabPg_t;

tabPg_t *initTabPg(tabPg_t *tabPg);
link newPg(pg_t *pg);
void pgInsertion(tabPg_t *tabPg, link new, int N);
void importPg(tabPg_t *tabPg);
void importFromIn(tabPg_t *tabPg);
void searchPg(tabPg_t *tabPg, char *name, char *choice, tabInv_t *tabInv);
void printPg(link x);
void deletePg(tabPg_t *tabPg, link prec, link canc);
void addEquipment(link nPg, tabInv_t *tabInv);
void removeEquipment(link nPg);
void recalcStats(link nPg, int choice, inv_t *obj);