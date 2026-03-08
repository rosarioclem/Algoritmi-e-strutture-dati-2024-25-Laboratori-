#include "pgList.h"

struct node{
    pg_t pg;
    link next;
};
struct pgList_t{
    link headPg;
    link tailPg;
    int nPg;
};

pgList initPgList(){
    pg_t tmp;
    char nome[MAXLEN];
    pgList L = malloc(sizeof(*L));
    L->headPg = NULL; L->tailPg = NULL; L->nPg = 0;
   // printf("Inserisci il nome del file dei personaggi:"); scanf("%s", nome); printf("\n");
    FILE *fin = fopen("../pg.txt", "r");
    if(fin == NULL){
        printf("Il file dei personaggi non esiste\n");
        return NULL;
    }
    while(pg_read(fin, &tmp) == 9){
        pgList_pgInsertion(L, &tmp);
    }

    return L;
}
void pgList_freeList(pgList list){
    link x, t;
    for(x = list->headPg, t = NULL; x != NULL; t = x, x = x->next){
        pg_clean(&x->pg);
        free(t);
    }
}
void pgList_pgInsertion(pgList L, pg_t *p_pg){
    link new = pgList_NEW(p_pg);
    if(L->nPg == 0){
        L->headPg = new;
        L->headPg->next = L->tailPg;
        L->nPg++;
        return;
    }
    if(L->nPg == 1){
        L->tailPg = new;
        L->headPg->next = L->tailPg;
        L->tailPg->next = NULL;
        L->nPg++;
        return;
    }
    else{
        L->tailPg->next = new;
        L->tailPg = L->tailPg->next;
        L->tailPg->next = NULL;
        L->nPg++;
    }

}
link pgList_NEW(pg_t *p_pg){
    link x = malloc(sizeof(*x));
    strcpy(x->pg.codice, p_pg->codice);
    strcpy(x->pg.nome, p_pg->nome);
    strcpy(x->pg.classe, p_pg->classe);
    x->pg.equip = p_pg->equip;
    x->pg.stats = p_pg->stats;
    x->next = NULL;

    return x;
}
link pgList_searchPg(pgList L, char *code){
    for(link x = L->headPg; x != NULL; x = x->next){
        if(strcmp(code, pg_getCode(&x->pg)) == 0) {
            printf("Personaggio trovato!\n");
            return x;
        }
    }
    printf("Il personaggio di codice %s non esiste\n", code);
    return NULL;
}
void pgList_editEquipment(pgList L, invArray inv, char *cmd){
    char code[7];
    printf("Di quale personaggio vuoi modificare l'equipaggiamento? (codice): ");
    scanf("%s", code); printf("\n");
    link p_pg = pgList_searchPg(L, code);
    if(p_pg != NULL){
        if(strcmp(cmd, "add") == 0)
            pg_addObj(&(p_pg->pg), inv);
        else if(strcmp(cmd, "remove") == 0)
            pg_removeObj(&(p_pg->pg), inv);
    }else
        printf("Personaggio non trovato\n");
}
void pgList_addPg(pgList L){
    pg_t newPg = pg_stdin();
    if(pgList_checkInput(L, &newPg)){
        printf("Personaggio aggiunto correttamente!\n");
        pgList_pgInsertion(L, &newPg);
    }
}
void pgList_removePg(pgList L){
    char code[7];
    printf("Inserisci il codice del personaggio che vuoi cancellare: ");
    scanf("%s", code); printf("\n");
    link rem = pgList_searchPg(L, code), prec;
    if(rem == NULL){
        return;
    }
    if(rem == L->headPg){
        L->headPg = L->headPg->next;
        free(rem);
    }else{
        for(prec = L->headPg; prec->next != rem; prec = prec->next);
        prec->next = rem->next;
        free(rem);
    }
}
int pgList_checkInput(pgList L, pg_t *newPg){
    for(link x = L->headPg; x != NULL; x = x->next){
        if(strcmp(newPg->nome, x->pg.nome) == 0 || strcmp(pg_getCode(&x->pg), pg_getCode(newPg)) == 0) {
            printf("Il codice/nome del personaggio che vuoi inserire esiste gia', personaggio non inserito\n");
            return 0;
        }
    }
    if(newPg->stats.hp < 0 || newPg->stats.mp < 0 || newPg->stats.atk < 0 || newPg->stats.def < 0 || newPg->stats.mag < 0 ||
            newPg->stats.spr < 0) {
        printf("Personaggio non valido, presenta una delle statistiche minore di 0\n");
        return 0;
    }
    return 1;
}
void pgList_printPg(pgList L, invArray inv){
    link x;
    char codicePg[7];
    printf("Inserisci il codice del personaggio da cercare: ");
    scanf("%s", codicePg); printf("\n");
    x = pgList_searchPg(L, codicePg);
    if(x == NULL)
        return;
    pg_print(&x->pg, inv);
}