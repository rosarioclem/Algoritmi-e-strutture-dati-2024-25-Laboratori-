#include "pg.h"

int pg_read(FILE *fp, pg_t *p_pg){
    int i = fscanf(fp, "%s %s %s %d %d %d %d %d %d", p_pg->codice, p_pg->nome, p_pg->classe, &p_pg->stats.hp,
           &p_pg->stats.mp, &p_pg->stats.atk, &p_pg->stats.def, &p_pg->stats.mag, &p_pg->stats.spr);
    p_pg->equip = initEquipArray();

    return i;
}
void pg_clean(pg_t *p_pg){
    equipArray_free(p_pg->equip);
}
void pg_print(pg_t *p_pg, invArray inv){
    printf("Ecco i tutti i dettagli del personaggio :\n\n");
    printf("Codice: %s\n", p_pg->codice);
    printf("Nome: %s\n", p_pg->nome);
    printf("Classe: %s\n", p_pg->classe);
    if(p_pg->stats.hp > 0)
        printf("Stat. hp: %d\n", p_pg->stats.hp);
    else
        printf("Stat. hp: 1\n");
    if(p_pg->stats.mp > 0)
        printf("Stat. mp: %d\n", p_pg->stats.mp);
    else
        printf("Stat. mp: 1\n");
    if(p_pg->stats.atk > 0)
        printf("Stat. atk: %d\n", p_pg->stats.atk);
    else
        printf("Stat. atk: 1\n");
    if(p_pg->stats.def > 0)
        printf("Stat. def: %d\n", p_pg->stats.def);
    else
        printf("Stat. def: 1\n");
    if(p_pg->stats.mag > 0)
        printf("Stat. mag: %d\n", p_pg->stats.mag);
    else
        printf("Stat. mag: 1\n");
    if(p_pg->stats.hp > 0)
        printf("Stat. spr: %d\n", p_pg->stats.spr);
    else
        printf("Stat. spr: 1\n");
    if(equipArray_usingObjs(p_pg->equip)){
        printf("\nEcco gli oggetti equipaggiati a %s:\n\n", p_pg->nome);
        equipArray_printAllObjs(p_pg->equip, inv);
    }
}
char *pg_getCode(pg_t *p_pg){
    return p_pg->codice;
}
void pg_recalcStats(pg_t *p_pg, char *cmd, int i, invArray inv){
    if(strcmp(cmd, "add") == 0){
        p_pg->stats.hp += invArray_getHp(inv, i);
        p_pg->stats.mp += invArray_getMp(inv, i);
        p_pg->stats.atk += invArray_getAtk(inv, i);
        p_pg->stats.def += invArray_getDef(inv, i);
        p_pg->stats.mag += invArray_getMag(inv, i);
        p_pg->stats.spr += invArray_getSpr(inv, i);
    }else if(strcmp(cmd, "remove") == 0){
        p_pg->stats.hp -= invArray_getHp(inv, i);
        p_pg->stats.mp -= invArray_getMp(inv, i);
        p_pg->stats.atk -= invArray_getAtk(inv, i);
        p_pg->stats.def -= invArray_getDef(inv, i);
        p_pg->stats.mag -= invArray_getMag(inv, i);
        p_pg->stats.spr -= invArray_getSpr(inv, i);
    }
}
void pg_addObj(pg_t *p_pg, invArray inv){
    int i;
    if(equipArray_addObj(p_pg->equip, inv, &i))
        pg_recalcStats(p_pg, "add", i, inv);
    if(equipArray_getNumObjs(p_pg->equip) == 0)
        printf("\n%s non sta utilizzando nessun oggetto", p_pg->nome);
    else if(equipArray_getNumObjs(p_pg->equip) == 1)
        printf("\n%s sta utilizzando %d oggeto\n", p_pg->nome, equipArray_getNumObjs(p_pg->equip));
    else if(equipArray_getNumObjs(p_pg->equip) != 8)
        printf("\n%s sta utilizzando %d oggetti\n", p_pg->nome, equipArray_getNumObjs(p_pg->equip));
}
void pg_removeObj(pg_t *p_pg, invArray inv){
    int i;
    if(equipArray_removeObj(p_pg->equip, inv, &i))
        pg_recalcStats(p_pg, "remove", i, inv);
    if(equipArray_getNumObjs(p_pg->equip) == 0)
        printf("\n%s non sta utilizzando nessun oggetto", p_pg->nome);
    else if(equipArray_getNumObjs(p_pg->equip) == 1)
        printf("\n%s sta utilizzando %d oggeto\n", p_pg->nome, equipArray_getNumObjs(p_pg->equip));
    else
        printf("\n%s sta utilizzando %d oggetti\n", p_pg->nome, equipArray_getNumObjs(p_pg->equip));
}
pg_t pg_stdin(){
    pg_t new;

    printf("Inserisci il codice del nuovo personaggio: ");
    scanf("%s", new.codice); printf("\n");
    printf("Inserisci il nome del nuovo personaggio: ");
    scanf("%s", new.nome); printf("\n");
    printf("Inserisci la classe del nuovo personaggio: ");
    scanf("%s", new.classe); printf("\n");
    printf("\nInserimento statistiche:\n\n");
    printf("Stat. hp: ");
    scanf("%d", &new.stats.hp); printf("\n");
    printf("Stat. mp: ");
    scanf("%d", &new.stats.mp); printf("\n");
    printf("Stat. atk: ");
    scanf("%d", &new.stats.atk); printf("\n");
    printf("Stat. def: ");
    scanf("%d", &new.stats.def); printf("\n");
    printf("Stat. mag: ");
    scanf("%d", &new.stats.mag); printf("\n");
    printf("Stat. spr: ");
    scanf("%d", &new.stats.spr); printf("\n");
    new.equip =initEquipArray();

    return new;
}