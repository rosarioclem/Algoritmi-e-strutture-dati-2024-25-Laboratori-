#include "list.h"

typedef struct{
    Item d;
    int valore, numero;
}fileItems;
typedef enum{
    acquisisciFile, ricercaTitolo, ricercaQuot_unaData, ricercaminmaxQuot_intervallo, ricercaminmaxQuot_all, bilanciamento,
    fine
}comando;

void leggiFile(LIST l);
fileItems *initVett(int N);
void insertVett(fileItems *v, fileItems t, int N);
comando getCmd(char *com);
void initMINMAXdate(Item *MINDATA, Item *MAXDATA);

int main(void){
    int i, continua = 1;
    comando c;
    char srcTit[MAXLEN], com[31];
    Llink src = NULL;
    Item srcData, srcInt1, srcInt2;
    Item MINDATA, MAXDATA;
    initMINMAXdate(&MINDATA, &MAXDATA);
    float quot, S;
    LIST l = LISTinit();

    for(i = 0; i < 70; i++)
        printf("*");
    printf("\n\t\t\tSISTEMA GLOBALE BORSE\n");
    for(i = 0; i < 70; i++)
        printf("*");
    printf("\n");

    while(continua){

        printf("\nCosa vuoi fare (insFile, srcTit, srcQuotD, srcQuotI, srcQuotA, bil, fine)?\n");
        printf("Si ricordi che per cercare qualsiasi tipo di quotazioni bisogna prima effettuare una ricerca di titolo,"
               " in quanto sara' utilizzato l'ultimo titolo cercato.\n");
        printf("\nInserisci comando: "); scanf("%s", com); printf("\n");
        c = getCmd(com);

        switch(c){
            case acquisisciFile:
                leggiFile(l);
                break;
            case ricercaTitolo:
                printf("\nInserisci il titolo da cercare: "); scanf("%s", srcTit); printf("\n");
                src = LISTsearch(l, srcTit);
                break;
            case ricercaQuot_unaData:
                if(src == LISTsetNULL(l))
                    printf("\nIl titolo che hai cercato non esiste, impossibile cercare le sue quotazioni.\n");
                else if(src == NULL)
                    printf("\nNon hai cercato alcun titolo fin'ora, impossibile effettuare ricerca.\n");
                else{
                    printf("\nRicerca della quotazione del titolo: %s\n", srcTit);
                    srcData = ITEMgetItem();
                    quot = BSTsearch(LISTgetBST(src), srcData);
                    if(quot == -1)
                        printf("\nNon esiste una quotazione del titolo in quella data.\n");
                    else
                        printf("\nQuotazione del titolo %s in data %d/%.2d/%.2d %.2d:%.2d = %.3f\n", srcTit,
                               srcData.anno, srcData.mese, srcData.giorno, srcData.ora, srcData.minuti,quot);
                }
                break;
            case ricercaminmaxQuot_intervallo:
                if(src == LISTsetNULL(l))
                    printf("\nIl titolo che hai cercato non esiste, impossibile cercare le sue quotazioni.\n");
                else if(src == NULL)
                    printf("\nNon hai cercato alcun titolo fin'ora, impossibile effettuare ricerca.\n");
                else{
                    printf("\nPrima data:\n");
                    srcInt1 = ITEMgetItem();
                    printf("\nSeconda data:\n");
                    srcInt2 = ITEMgetItem();
                    if(ITEMcmp(&srcInt1, &srcInt2) == 1){
                        Item tmp = srcInt1;
                        srcInt1 = srcInt2;
                        srcInt2 = tmp;
                    }
                    BSTvisit(LISTgetBST(src), srcInt1, srcInt2);
                }
                break;
            case ricercaminmaxQuot_all:
                if(src == LISTsetNULL(l))
                    printf("\nIl titolo che hai cercato non esiste, impossibile cercare le sue quotazioni.\n");
                else if(src == NULL)
                    printf("\nNon hai cercato alcun titolo fin'ora, impossibile effettuare ricerca.\n");
                else{
                    BSTvisit(LISTgetBST(src), MINDATA, MAXDATA);
                }
                break;
            case bilanciamento:
                if(src == LISTsetNULL(l))
                    printf("\nIl titolo che hai cercato non esiste, impossibile bilanciare l'albero delle quotazioni.\n");
                else if(src == NULL)
                    printf("\nNon hai cercato alcun titolo fin'ora, impossibile bilanciare l'albero delle quotazioni.\n");
                else{
                    printf("\nInserire la soglia da superare (rapporto tra lungh. cammino piu' lungo e cammino piu' corto)"
                           "per bilanciare l'albero delle quotazioni:");
                    scanf("%f", &S); printf("\n");
                    if(S <= 0)
                        printf("\nSoglia non valida.\n");
                    else{
                        BSTcalcMinMaxPath(LISTgetBST(src), S);
                    }
                }
                break;
            case fine:
                printf("\nChiusura sistema!\n");
                continua = 0;
                break;
            default:
                printf("\nHai inserito un comando sbagliato.\n");
                break;
        }
    }

}

void leggiFile(LIST l){
    int i, j, numTit, numTra;
    char filename[11], tit[MAXLEN];
    fileItems *v, tmp;
    printf("Inserisci il nome del file: "); scanf("%s", filename); printf("\n");
    FILE *fin = fopen(filename, "r");

    fscanf(fin, "%d", &numTit);
    for(i = 0; i < numTit; i++){
        fscanf(fin, "%s %d", tit, &numTra);
        v = initVett(numTra);
        for(j = 0; j < numTra; j++){
            fscanf(fin, "%d/%d/%d %d:%d %d %d", &tmp.d.anno, &tmp.d.mese, &tmp.d.giorno, &tmp.d.ora, &tmp.d.minuti,
                   &tmp.valore, &tmp.numero);
            insertVett(v, tmp, numTra);
        }
        for(j = 0; j < numTra; j++)
            LISTorder_insert(l, tit, v[j].d, (float) v[j].valore / v[j].numero);
        free(v);
    }

    fclose(fin);
    printf("\nFile acquisito correttamente.\n");
}
fileItems *initVett(int N){
    fileItems *v = malloc(N * sizeof(*v));
    for(int i = 0; i < N; i++){
        v[i].valore = 0;
        v[i].numero = 0;
        v[i].d = ITEMsetNull();
    }

    return v;
}
void insertVett(fileItems *v, fileItems t, int N){
    int i;
    for(i = 0; i < N; i++){
        if(v[i].d.anno == 0)
            break;
    }
    v[i].d = t.d;
    if(i != 0) {
        v[i].valore += v[i-1].valore + t.valore * t.numero;
        v[i].numero += v[i-1].numero + t.numero;
    }else{
        v[i].valore = t.valore * t.numero;
        v[i].numero = t.numero;
    }
}
comando getCmd(char *com){
    if(strcmp(com, "insFile") == 0)
        return acquisisciFile;
    else if(strcmp(com, "srcTit") == 0)
        return ricercaTitolo;
    else if(strcmp(com, "srcQuotD") == 0)
        return ricercaQuot_unaData;
    else if(strcmp(com, "srcQuotI") == 0)
        return ricercaminmaxQuot_intervallo;
    else if(strcmp(com, "srcQuotA") == 0)
        return ricercaminmaxQuot_all;
    else if(strcmp(com, "bil") == 0)
        return bilanciamento;
    else if(strcmp(com, "fine") == 0)
        return fine;
    else return -1;
}
void initMINMAXdate(Item *MINDATA, Item *MAXDATA){
    MINDATA->anno = 0;
    MINDATA->mese = 0;
    MINDATA->giorno = 0;
    MINDATA->ora = 0;
    MINDATA->minuti = 0;
    MAXDATA->anno = 9999;
    MAXDATA->mese = 12;
    MAXDATA->giorno = 31;
    MAXDATA->ora = 0;
    MAXDATA->minuti = 0;
}