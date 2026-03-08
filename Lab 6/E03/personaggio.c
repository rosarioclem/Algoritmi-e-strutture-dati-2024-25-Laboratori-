#include "personaggio.h"

tabPg_t *initTabPg(tabPg_t *tabPg){
    tabPg_t *x = malloc(sizeof(tabPg_t));
    x->headPg = NULL; x->tailPg = NULL;
    x->nPg = 0;
    return x;
}
link newPg(pg_t *pg){
    link x = malloc(sizeof(*x));
    if(x == NULL){
        printf("\nNon c'e' piu' spazio per inserire personaggi\n\n");
        return NULL;
    }
    strcpy(x->pg.nome, pg->nome);
    strcpy(x->pg.codice, pg->codice);
    strcpy(x->pg.classe, pg->classe);
    x->pg.stat = pg->stat;
    x->pg.equip.inUso = 0;
    x->pg.equip.nOggetti = 0;
    x->pg.equip.vettEq = malloc(8 * sizeof(inv_t *));
    for(int i = 0; i < 8; i++){
        x->pg.equip.vettEq[i] = NULL;
    }
    return x;
}
void pgInsertion(tabPg_t *tabPg, link new, int N){
    if(N == 0){
        tabPg->headPg = new;
        tabPg->headPg->next = tabPg->tailPg;
    }else if(N == 1){
        tabPg->tailPg = new;
        tabPg->headPg->next = tabPg->tailPg;
        tabPg->tailPg->next = NULL;
    }
    else{
        new->next = NULL;
        tabPg->tailPg->next = new;
        tabPg->tailPg = tabPg->tailPg->next;
    }
}
void importPg(tabPg_t *tabPg){
    link new;
    pg_t pg;
    FILE *fin = fopen("../pg.txt", "r");
    if(fin == NULL){
        printf("Il file dei personaggi non esiste\n\n");
        exit(-1);
    }

    while(fscanf(fin, "%s %s %s %d %d %d %d %d %d", pg.codice, pg.nome, pg.classe,
                 &pg.stat.hp, &pg.stat.mp, &pg.stat.atk, &pg.stat.def, &pg.stat.mag, &pg.stat.spr) == 9){
        new = newPg(&pg);
        pgInsertion(tabPg, new, tabPg->nPg++);
    }
}
void importFromIn(tabPg_t *tabPg){
    int found = 0;
    link new, x;
    pg_t pg;
    printf("\nInserisci le informazioni del personaggio da inserire:\n\n");
    printf("Codice: "); scanf("%s", pg.codice); printf("\n");
    printf("Nome (max 50 caratt.): "); scanf("%s", pg.nome); printf("\n");
    printf("Classe (max 50 caratt.): "); scanf("%s", pg.classe); printf("\n");
    printf("Stat. hp (solo interi positivi o nulli): "); scanf("%d", &pg.stat.hp);  printf("\n");
    printf("Stat. mp (solo interi positivi o nulli): "); scanf("%d", &pg.stat.mp);  printf("\n");
    printf("Stat. atk (solo interi positivi o nulli): "); scanf("%d", &pg.stat.atk);  printf("\n");
    printf("Stat. def (solo interi positivi o nulli): "); scanf("%d", &pg.stat.def);  printf("\n");
    printf("Stat. mag (solo interi positivi o nulli): "); scanf("%d", &pg.stat.mag);  printf("\n");
    printf("Stat. spr (solo interi positivi o nulli): "); scanf("%d", &pg.stat.spr);  printf("\n\n");
    printf("L'equipaggiamento si aggiungera' con un altro comando\n\n");

    if(pg.stat.hp < 0 || pg.stat.mp < 0 || pg.stat.atk < 0 || pg.stat.def < 0 || pg.stat.mag < 0 || pg.stat.spr < 0){
        printf("\nIl personaggio inserito non e' valido\n");
    }else {
        for(x = tabPg->headPg; x != NULL; x = x->next){
            if(strcmp(pg.codice, x->pg.codice) == 0 || strcmp(pg.nome, x->pg.nome) == 0){
                found = 1; break;
            }
        }
        if(!found) {
            new = newPg(&pg);
            pgInsertion(tabPg, new, tabPg->nPg);
            printf("\nPersonaggio aggiunto con successo!\n\n");
        }else
            printf("\nEsiste gia' un personaggio con quel nome/codice\n");
    }
}
void searchPg(tabPg_t *tabPg, char *name, char *choice, tabInv_t *tabInv){
    link x, t;
    for(x = tabPg->headPg, t = NULL; x != NULL; t = x, x=x->next){
        if(strcmp(name, x->pg.nome) == 0){
            break;
        }
    }
    if(x == NULL){
        printf("\nIl personaggio che vuoi cercare non esiste\n\n");
    }else{
        if(strcmp(choice, "stampaPg") == 0){
            printPg(x);
        }else if(strcmp(choice, "cancellaPg") == 0){
            deletePg(tabPg, t, x);
        }else if(strcmp(choice, "aggiungiOggetto") == 0){
            addEquipment(x, tabInv);
        }else if(strcmp(choice, "rimuoviOggetto") == 0){
            removeEquipment(x);
        }
    }
}
void printPg(link x){
    int j = 1;
    printf("\nStampo i dettagli del personaggio cercato:\n\n");
    printf("Codice: %s\n", x->pg.codice);
    printf("Nome: %s\n", x->pg.nome);
    printf("Classe: %s\n", x->pg.classe);
    if(x->pg.stat.hp > 0) {
        printf("Stat. hp: %d\n", x->pg.stat.hp);
    }else{
        printf("Stat. hp: 0\n");
    }
    if(x->pg.stat.mp > 0) {
        printf("Stat. mp: %d\n", x->pg.stat.mp);
    }else{
        printf("Stat. mp: 0\n");
    }
    if(x->pg.stat.atk > 0) {
        printf("Stat. atk: %d\n", x->pg.stat.atk);
    }else{
        printf("Stat. atk: 0\n");
    }
    if(x->pg.stat.def > 0) {
        printf("Stat. def: %d\n", x->pg.stat.def);
    }else{
        printf("Stat. def: 0\n");
    }
    if(x->pg.stat.mag > 0) {
        printf("Stat. mag: %d\n", x->pg.stat.mag);
    }else{
        printf("Stat. mag: 0\n");
    }
    if(x->pg.stat.spr > 0) {
        printf("Stat. spr: %d\n", x->pg.stat.spr);
    }else{
        printf("Stat. spr: 0\n");
    }
    if(x->pg.equip.inUso == 1){
        for(int i = 0; i < 8; i++){
            if(x->pg.equip.vettEq[i] != NULL){
                printf("\nOggetto num.%d:\n\n", j);
                printf("Nome: %s\n", x->pg.equip.vettEq[i]->nome);
                printf("Tipo: %s\n", x->pg.equip.vettEq[i]->tipo);
                printf("Stat. hp: %d\n", x->pg.equip.vettEq[i]->stat.hp);
                printf("Stat. mp: %d\n", x->pg.equip.vettEq[i]->stat.mp);
                printf("Stat. atk: %d\n", x->pg.equip.vettEq[i]->stat.atk);
                printf("Stat. def: %d\n", x->pg.equip.vettEq[i]->stat.def);
                printf("Stat. mag: %d\n", x->pg.equip.vettEq[i]->stat.mag);
                printf("Stat. spr: %d\n", x->pg.equip.vettEq[i]->stat.spr);
                j++;
            }
        }
    }
}
void deletePg(tabPg_t *tabPg, link prec, link canc){
    if(prec == NULL){
        link tmp = canc->next;
        canc->next = NULL;
        tabPg->headPg = tmp;
        free(canc);
        printf("\nPersonaggio cancellato correttamente\n");
    }else {
        prec->next = canc->next;
        canc->next = NULL;
        free(canc);
        printf("\nPersonaggio cancellato correttamente\n");
    }
}
void addEquipment(link nPg, tabInv_t *tabInv){
    int found = 0, flag = 0;
    if(nPg->pg.equip.nOggetti == 8){
        printf("\nNon puoi piu' equipaggiare oggetti al personaggio\n");
        return;
    }else {
        inv_t *obj, *f;
        char name[MAXLEN];
        printf("\nInserisci il nome dell'oggetto da equipaggiare: "); scanf("%s", name); printf("\n");
        for(int i = 0; i < tabInv->nInv; i++){
            if(strcmp(name, tabInv->vettInv[i].nome) == 0){
                obj = &tabInv->vettInv[i];
                for(int k = 0; k < 8; k++){
                    if(nPg->pg.equip.vettEq[k] != NULL) {
                        if (strcmp(obj->nome, nPg->pg.equip.vettEq[k]->nome) == 0) {
                            flag = 1;
                            break;
                        }
                    }
                }
                if(flag){
                    printf("\nHai gia' equipaggiato %s con %s\n", nPg->pg.nome, obj->nome);
                    return;
                }else{
                    for (int j = 0; j < 8; j++) {
                        if (nPg->pg.equip.vettEq[j] == NULL) {
                            nPg->pg.equip.vettEq[j] = &tabInv->vettInv[i];
                            nPg->pg.equip.nOggetti++;
                            nPg->pg.equip.inUso = 1;
                            found = 1;
                            printf("\nOggetto aggiunto correttamente\n");
                            break;
                        }
                    }
                }
                break;

            }
        }
        if(!found)
            printf("\nL'oggetto inserito non esiste\n");
        recalcStats(nPg, 1, obj);
    }
}
void removeEquipment(link nPg){
    int found = 0;
    if(nPg->pg.equip.nOggetti == 0){
        printf("\nIl personaggio non possiede alcun oggetto\n");
        return;
    }else{
        char name[MAXLEN];
        inv_t *obj;
        printf("\nInserisci il nome dell'oggetto da rimuovere: "); scanf("%s", name); printf("\n");
        for(int i = 0; i < nPg->pg.equip.nOggetti; i++){
            if(strcmp(name, nPg->pg.equip.vettEq[i]->nome) == 0){
                obj = nPg->pg.equip.vettEq[i];
                nPg->pg.equip.vettEq[i] = NULL;
                nPg->pg.equip.nOggetti--;
                found = 1;
                if(nPg->pg.equip.nOggetti == 0)
                    nPg->pg.equip.inUso = 0;
                printf("\nOggetto rimosso correttamente\n");
                break;
            }
        }
        if(!found)
            printf("\nL'oggetto inserito non esiste\n");
        recalcStats(nPg, 0, obj);
    }
}
void recalcStats(link nPg, int choice, inv_t *obj){
    if(choice){
        nPg->pg.stat.hp += obj->stat.hp;
        nPg->pg.stat.mp += obj->stat.mp;
        nPg->pg.stat.atk += obj->stat.atk;
        nPg->pg.stat.def += obj->stat.def;
        nPg->pg.stat.mag += obj->stat.mag;
        nPg->pg.stat.spr += obj->stat.spr;
    }else{
        nPg->pg.stat.hp -= obj->stat.hp;
        nPg->pg.stat.mp -= obj->stat.mp;
        nPg->pg.stat.atk -= obj->stat.atk;
        nPg->pg.stat.def -= obj->stat.def;
        nPg->pg.stat.mag -= obj->stat.mag;
        nPg->pg.stat.spr -= obj->stat.spr;
    }
}