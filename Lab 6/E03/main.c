#include "personaggio.h"

void liberaTutto(tabInv_t *tabInv, tabPg_t *tabPg);

int main(void){
    tabInv_t *tabInv;
    tabInv = initTabInv(tabInv);
    tabPg_t *tabPg;
    tabPg  = initTabPg(tabPg);
    importEq(tabInv);
    importPg(tabPg);

    int index;
    char comando[MAXLEN], namePg[MAXLEN];
    while(1) {
        printf("\nCosa vuoi fare? (aggiungiPg, stampaPg, cancellaPg, modificaEqPg, stampaOgg, fine):");
        scanf("%s", comando);
        if (strcmp(comando, "aggiungiPg") == 0) {
            importFromIn(tabPg);
        }else if(strcmp(comando, "stampaPg") == 0){
            printf("\nInserisci il nome del personaggio di cui vuoi visualizzare i dettagli: ");
            scanf("%s", namePg); printf("\n");
            searchPg(tabPg, namePg, comando, tabInv);
        }else if(strcmp(comando, "cancellaPg") == 0){
            printf("\nInserisci il nome del personaggio che vuoi cancellare: ");
            scanf("%s", namePg); printf("\n");
            searchPg(tabPg, namePg, comando, tabInv);
        }else if(strcmp(comando, "modificaEqPg") == 0){
            printf("\nInserisci il nome del personaggio a cui vuoi modificare l'equipaggiamento: ");
            scanf("%s", namePg); printf("\n");
            printf("\nVuoi aggiungere o rimuovere un oggetto? (aggiungiOggetto, rimuoviOggetto): ");
            scanf("%s", comando); printf("\n");
            if(strcmp(comando, "aggiungiOggetto") == 0){
                searchPg(tabPg, namePg, comando, tabInv);
            }else if(strcmp(comando, "rimuoviOggetto") == 0){
                searchPg(tabPg, namePg, comando, tabInv);
            }else{
                printf("\nHai inserito un comando sbagliato");
            }
        }else if(strcmp(comando, "stampaOgg") == 0){
            index = searchObj(tabInv);
            printObj(tabInv, index);
        }else if(strcmp(comando, "fine") == 0){
            printf("\nTerminazione del programma\n");
            break;
        }
        else{
            printf("\nHai inserito un comando sbagliato\n");
        }
    }

    liberaTutto(tabInv, tabPg);
}

void liberaTutto(tabInv_t *tabInv, tabPg_t *tabPg){
    link x, t;
    free(tabInv->vettInv);
    for(x = tabPg->headPg, t = NULL; x != NULL; t = x, x = x->next){
        free(x->pg.equip.vettEq);
        free(t);
    }
    free(tabInv);
    free(tabPg);
}