#include "Graph.h"

typedef enum{
  elenca, adiacenti, generaLista , fine
} comando;

void menu(Graph G);
comando getCmd(char *com);

int main(int argc, char **argv){
    Graph G = GRAPHinit(argv[argc-1]);
    GRAPHload(G, argv[argc-1]);
    menu(G);
    GRAPHfree(G);
}

void menu(Graph G){
    int i, ind1, ind2, ind3;
    comando c;
    char com[MAXLEN];
    char vert1[MAXLEN], vert2[MAXLEN], vert3[MAXLEN];
    int continua = 1, ladjCheck = 0, index;
    Item *ordVertex = malloc(GRAPHgetVertexes(G) * sizeof(Item));
    ITEMcopyArray(ordVertex, STgetItems(GRAPHgetTab(G)), GRAPHgetVertexes(G));
    qsort(ordVertex, GRAPHgetVertexes(G), sizeof(Item), ITEMalphCmp);

    while(continua){
        printf("Cosa vuoi fare?\n\n");
        printf("- Elencare i vertici in ordine alfabetico (elenca)\n");
        printf("- Verificare adiacenza (a coppie) di tre vertici (adiacenza)\n");
        printf("- Generare la lista di adiacenza (generaLista)\n");
        printf("- Fine (fine)\n\n");
        printf("Comando: ");
        scanf("%s", com); printf("\n");
        c = getCmd(com);

        switch(c){
            case fine:
                printf("Terminazione programma\n");
                continua = 0;
                break;
            case elenca:
                printf("Ecco i vertici del grafo e gli archi che insistono su ognuno di essi in ordine alfabetico:\n");
                for(i = 0; i < GRAPHgetVertexes(G); i++) {
                    printf("\nVertice: %s\n\n", ordVertex[i].id_elab);
                    index = STsearch(GRAPHgetTab(G), &ordVertex[i]);
                    GRAPHEdges(G, index);
                }
                break;
            case adiacenti:
                printf("Inserisci i vertici di cui vuoi verificare l'adiacenza (a coppie):");
                scanf("%s %s %s", vert1, vert2, vert3); printf("\n");
                ind1 = STsearchIndex(GRAPHgetTab(G), vert1);
                ind2 = STsearchIndex(GRAPHgetTab(G), vert2);
                ind3 = STsearchIndex(GRAPHgetTab(G), vert3);

                if(ind1 == -1 || ind2 == -1 || ind3 == -1){
                    printf("Uno dei vertici inseriti non esiste\n");
                    break;
                }
                printf("Vuoi controllare con lista o matrice delle adiacenze?");
                scanf("%s", com); printf("\n");
                if(strcmp(com, "lista") == 0){
                    if(ladjCheck) {
                        if (GRAPHcheckAdjLadj(G, ind1, ind2, ind3))
                            printf("I vertici %s, %s e %s sono adiacenti a coppie\n\n", vert1, vert2, vert3);
                        else
                            printf("I vertici %s, %s e %s non sono adiacenti a coppie\n\n", vert1, vert2, vert3);
                    }else
                        printf("Devi prima generare la lista delle adiacenze!\n");
                }else if(strcmp(com, "matrice") == 0){
                    if(GRAPHcheckAdjMadj(G, ind1, ind2, ind3))
                        printf("I vertici %s, %s e %s sono adiacenti a coppie\n\n", vert1, vert2, vert3);
                    else
                        printf("I vertici %s, %s e %s non sono adiacenti a coppie\n\n", vert1, vert2, vert3);
                }else
                    printf("Hai inserito un comando sbagliato\n");
                break;
            case generaLista:
                if(!ladjCheck){
                    ladjCheck = 1;
                    GRAPHladjFromMadj(G);
                    printf("Lista delle adiacenze generata correttamente\n\n");
                }else
                    printf("La lista delle adiacenze e' gia' stata generata\n\n");
                break;
            default:
                printf("Hai inserito un comando sbagliato\n");
                break;
        }
    }

    free(ordVertex);
}
comando getCmd(char *com){
    if(strcmp(com, "fine") == 0)
        return fine;
    else if(strcmp(com, "elenca") == 0)
        return elenca;
    else if(strcmp(com, "adiacenza") == 0)
        return adiacenti;
    else if(strcmp(com, "generaLista") == 0)
        return generaLista;
    else return -1;
}