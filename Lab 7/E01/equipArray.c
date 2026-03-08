#include "equipArray.h"

struct equipArray_t{
    int indici[8];
    int usedObjs;
};
equipArray initEquipArray(){
    equipArray v = malloc(sizeof(*v));
    for(int i = 0; i < 8; i++)
        v->indici[i] = -1;
    v->usedObjs = 0;

    return v;
}
int equipArray_addObj(equipArray equip, invArray v, int *index){
    int i;
    if(equip->usedObjs == 8){
        printf("Il personaggio selezionato sta gia' utilizzando il numero massimo di oggetti disponibili\n");
        return 0;
    }
    *index = invArray_searchIndexObj(v);
    if(*index == -1){
        printf("Impossibile aggiungere l'oggetto richiesto\n");
        return 0;
    }
    for(i = 0; i < 8; i++){
        if(equip->indici[i] == *index){
            printf("L'oggetto che vuoi inserire e' gia' presente nell'equipaggiamento del personaggio selezionato\n");
            return 0;
        }
    }
    for(i = 0; i < 8; i++){
        if(equip->indici[i] == -1) {
            equip->indici[i] = *index;
            equip->usedObjs++;
            printf("Oggetto aggiunto correttamente\n");
            return 1;
        }
    }
}
int equipArray_removeObj(equipArray equip, invArray v, int *index){
    int i;
    if(equip->usedObjs == 0){
        printf("Il personaggio selezionato non e' equipaggiato con nessun oggetto");
        return 0;
    }
    *index = invArray_searchIndexObj(v);
    if(*index == -1){
        printf("Impossibile rimuovere l'oggetto richiesto\n");
        return 0;
    }
    for(i = 0; i < 8; i++){
        if(equip->indici[i] == *index){
            printf("L'oggetto richiesto e' stato rimosso correttamente\n");
            equip->indici[i] = -1;
            equip->usedObjs--;
            return 1;
        }
    }
}
void equipArray_printAllObjs(equipArray equip, invArray inv){
    for(int i = 0; i < 8; i++){
        if(equip->indici[i] != -1){
            invArray_printFromIndex(equip->indici[i], inv);
        }
    }
}
int equipArray_usingObjs(equipArray equip){
    return equip->usedObjs > 0 ? 1:0;
}
void equipArray_free(equipArray equip){
    free(equip);
}
int equipArray_getNumObjs(equipArray equip){
    return equip->usedObjs;
}