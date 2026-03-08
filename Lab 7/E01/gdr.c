#include "invArray.h"
#include "pg.h"
#include "pgList.h"

typedef enum{
    end, addPg, removePg, searchByCodePg, printPg, editEquipmentPg, printObj, updateObj, pass
} comandi;

comandi getCmd(char *comando);

int main(void){
    int continua = 1, i;
    char cmd[MAXLEN], codicePg[7];
    comandi c;
    invArray inv = initInvArray();
    pgList L = initPgList();

    for(i = 0; i < 70; i++)
        printf("*");
    printf("\n\t\t\tMENU' PRINCIPALE\n");
    for(i = 0; i < 70; i++)
        printf("*");
    printf("\n");
    while(continua){
        printf("\nCosa vuoi fare (aggiungiPg, rimuoviPg, stampaPg, aggiungi/rimuoviEquipPg, cercaPg, stampaObj,"
               " aggiornaObj, fine)? \n");
        scanf("%s", cmd);
        c = getCmd(cmd);
        switch(c){
            case addPg:
                pgList_addPg(L);
                break;
            case removePg:
                pgList_removePg(L);
                break;
            case searchByCodePg:
                printf("Inserisci il codice del personaggio da cercare: ");
                scanf("%s", codicePg); printf("\n");
                pgList_searchPg(L, codicePg);
                break;
            case printPg:
                pgList_printPg(L, inv);
                break;
            case editEquipmentPg:
                if(strcmp(cmd, "aggiungiEquipPg") == 0)
                    pgList_editEquipment(L, inv, "add");
                else
                    pgList_editEquipment(L, inv, "remove");
                break;
            case printObj:
                invArray_searchObj(inv, "stampaOggetto");
                break;
            case updateObj:
                invArray_searchObj(inv, "modificaStatsOggetto");
                break;
            case pass:
                printf("Hai inserito un comando sbagliato, riprova\n");
                break;
            case end:
                printf("\n");
                for(i = 0; i < 70; i++)
                    printf("*");
                printf("\n\t\t\tGIOCO TERMINATO!\n");
                for(i = 0; i < 70; i++)
                    printf("*");
                printf("\n");
                continua = 0;
                break;
        }
    }

    freeInvArray(inv);
    pgList_freeList(L);
}

comandi getCmd(char *comando){
    if(strcmp("fine", comando) == 0)
        return end;
    else if(strcmp("aggiungiPg", comando) == 0)
        return addPg;
    else if(strcmp("rimuoviPg", comando) == 0)
        return removePg;
    else if(strcmp("stampaPg", comando) == 0)
        return printPg;
    else if(strcmp("aggiungiEquipPg", comando) == 0 || strcmp("rimuoviEquipPg", comando) == 0)
        return editEquipmentPg;
    else if(strcmp("cercaPg", comando) == 0)
        return searchByCodePg;
    else if(strcmp("stampaObj", comando) == 0)
        return printObj;
    else if(strcmp("aggiornaObj", comando) == 0)
        return updateObj;
    else
        return pass;
}