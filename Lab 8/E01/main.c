#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 101

typedef struct{
    char nome[MAXLEN];
    int tipologia;
    int dirIngresso;
    int dirUscita;
    int reqPrec;
    int finale;
    float valore;
    int difficolta;
}elemento;
typedef struct{
    int elementi[5];
    float punteggio;
    int difficoltaTot;
} diagonale;

elemento *leggiFile(int *num_el);
int min(int a, int b);
int compare(const void *a, const void *b);
int compare_diff(elemento *a, elemento *b);
void greedy(elemento *elementi, int num_el, int DD, int DP);

int main(void){
    int n_el;
    int DD, DP;
    printf("Inserisci la difficolta' massima per ogni diagonale: ");
    scanf("%d", &DD); printf("\n");
    printf("Inserisci la difficolta' massima dell'esibizione: ");
    scanf("%d", &DP); printf("\n");
    elemento *elementi = leggiFile(&n_el);

    qsort(elementi, n_el, sizeof(elemento), compare);

    greedy(elementi, n_el, DD, DP);

    free(elementi);
}

elemento *leggiFile(int *num_el){
    FILE *fin = fopen("../elementi.txt", "r");
    if(fin == NULL){
        printf("Il file non esiste\n");
        return NULL;
    }

    fscanf(fin, "%d", num_el);
    elemento *v = malloc((*num_el) * sizeof(elemento));
    for(int i = 0; i < (*num_el); i++){
        fscanf(fin, "%s %d %d %d %d %d %f %d", v[i].nome, &v[i].tipologia, &v[i].dirIngresso, &v[i].dirUscita,
               &v[i].reqPrec, &v[i].finale, &v[i].valore, &v[i].difficolta);
    }

    fclose(fin);
    return v;
}
int min(int a, int b){
    return a <= b ? a:b;
}
int compare(const void *a, const void *b){
    return compare_diff((elemento *)a, (elemento *)b);
}
int compare_diff(elemento *a, elemento *b){
    return(a->difficolta >= b->difficolta);
}
void greedy(elemento *elementi, int num_el, int DD, int DP){
    int i, j;
    int diff_3 = DD;
    int diff_1_2 = (DP - DD) / 2;
    int avanti = 0, indietro = 0, bonus = 0;
    diagonale sol[3];
    float best_score;
    for(i = 0; i < 3; i++){
        for(j = 0; j < 5; j++)
            sol[i].elementi[j] = -1;
        sol[i].difficoltaTot = 0;
        sol[i].punteggio = 0;
    }

    for(i = 0; i < 3; i++){
        best_score = 0;
        if(i == 0){
            for(j = 0; j < num_el && elementi[j].difficolta <= min(diff_1_2, DD); j++){
                if(elementi[j].dirIngresso == 1 && elementi[j].tipologia != 0 && elementi[j].valore >= best_score &&
                elementi[j].reqPrec == 0) {
                    sol[i].elementi[0] = j;
                    if(elementi[j].tipologia == 1)
                        indietro = 1;
                    else
                        avanti = 1;
                    best_score = elementi[j].valore;
                }
            }
        }else if(i == 1){
            for(j = 0; j < num_el && elementi[j].difficolta <= min(diff_1_2, DD)/2; j++){
                if(elementi[j].valore >= best_score && elementi[j].reqPrec == 0 && elementi[j].dirIngresso == 1){
                    sol[i].elementi[0] = j;
                    best_score = elementi[j].valore;
                    if(elementi[j].tipologia == 1)
                        indietro = 1;
                    else if(elementi[j].tipologia == 2)
                        avanti = 1;
                }
            }
            best_score = 0;
            for(j = 0; j < num_el && elementi[j].difficolta <= min(diff_1_2, DD)/2; j++){
                if(indietro && !avanti
                && elementi[j].dirIngresso == elementi[sol[i].elementi[0]].dirUscita && elementi[j].tipologia == 2){
                    sol[i].elementi[1] = j;
                    best_score = elementi[j].valore;
                    avanti = 1;
                }else if(!indietro && avanti &&
                elementi[j].dirIngresso == elementi[sol[i].elementi[0]].dirUscita && elementi[j].tipologia == 1) {
                    sol[i].elementi[1] = j;
                    best_score = elementi[j].valore;
                    indietro = 1;
                }else if(indietro && avanti && elementi[j].valore >= best_score
                && elementi[j].dirIngresso == elementi[sol[i].elementi[0]].dirUscita) {
                    sol[i].elementi[1] = j;
                    best_score = elementi[j].valore;
                }
            }
            best_score = 0;
            if(sol[i].elementi[1] == -1){
                for(j = 0; j < num_el && elementi[j].difficolta <= min(diff_1_2, DD)/2; j++){
                    if(elementi[j].dirIngresso == elementi[sol[i].elementi[0]].dirUscita && elementi[j].valore >= best_score){
                        sol[i].elementi[1] = j;
                        best_score = elementi[j].valore;
                        if(elementi[j].tipologia == 2)
                            avanti = 1;
                        else if(elementi[j].tipologia == 1)
                            indietro = 1;
                    }
                }
            }
        }else{
            if(diff_3 > 8) {
                for (j = 0; j < num_el; j++) {
                    if (elementi[j].difficolta >= 8 && elementi[j].difficolta <= diff_3 - 1 && elementi[j].valore >= best_score) {
                        sol[i].elementi[1] = j;
                        best_score = elementi[j].valore;
                        bonus = 1;
                        if(elementi[j].tipologia == 2)
                            avanti = 1;
                        else if(elementi[j].tipologia == 1)
                            indietro = 1;
                    }
                }
                best_score = 0;
                for (j = 0; j < num_el && elementi[j].difficolta <= diff_3 - elementi[sol[i].elementi[1]].difficolta; j++){
                    if(elementi[j].dirUscita == elementi[sol[i].elementi[1]].dirIngresso && elementi[j].dirIngresso == 1
                       && elementi[j].finale == 0 && elementi[j].valore >= best_score && elementi[j].reqPrec == 0
                       && avanti && indietro){
                        sol[i].elementi[0] = j;
                        best_score = elementi[j].valore;
                    }else if (elementi[j].dirUscita == elementi[sol[i].elementi[1]].dirIngresso && elementi[j].dirIngresso == 1
                        && elementi[j].finale == 0 && elementi[j].valore >= best_score && elementi[j].reqPrec == 0 &&
                        avanti && !indietro && elementi[j].tipologia == 1){
                        sol[i].elementi[0] = j;
                        best_score = elementi[j].valore;
                    }else if(elementi[j].dirUscita == elementi[sol[i].elementi[1]].dirIngresso && elementi[j].dirIngresso == 1
                             && elementi[j].finale == 0 && elementi[j].valore >= best_score && elementi[j].reqPrec == 0 &&
                             indietro && !avanti && elementi[j].tipologia == 2){
                        sol[i].elementi[0] = j;
                        best_score = elementi[j].valore;
                    }
                }
            }else{
                for(j = 0; j < num_el && elementi[j].difficolta <= diff_3; j++){
                    if(avanti && indietro && elementi[j].dirIngresso == 1 && elementi[j].reqPrec == 0 &&
                    elementi[j].valore >= best_score){
                        sol[i].elementi[0] = j;
                        best_score = elementi[j].valore;
                    }else if(avanti && !indietro && elementi[j].dirIngresso == 1 && elementi[j].reqPrec == 0 &&
                             elementi[j].tipologia == 1) {
                        sol[i].elementi[0] = j;
                        best_score = elementi[j].valore;
                    }else if(!avanti && indietro && elementi[j].dirIngresso == 1 && elementi[j].reqPrec == 0 &&
                            elementi[j].tipologia == 2) {
                        sol[i].elementi[0] = j;
                        best_score = elementi[j].valore;
                    }
                }
                if(!indietro){
                    for(j = 0; j < num_el && elementi[j].difficolta <= diff_3 - 1 ; j++){
                        if(elementi[j].tipologia == 1){
                            sol[i].elementi[1] = j;
                            break;
                        }
                    }
                    for(j = 0; j < num_el && elementi[j].difficolta <= diff_3 - elementi[sol[i].elementi[1]].difficolta; j++){
                        if(elementi[i].finale == 0 && elementi[j].dirIngresso == 1 &&
                        elementi[j].dirUscita == elementi[sol[i].elementi[1]].dirIngresso){
                            sol[i].elementi[0] = j;
                        }
                    }
                }else if(!avanti){
                    for(j = 0; j < num_el && elementi[j].difficolta <= diff_3 - 1 ; j++){
                        if(elementi[j].tipologia == 2){
                            sol[i].elementi[1] = j;
                            break;
                        }
                    }
                    for(j = 0; j < num_el && elementi[j].difficolta <= diff_3 - elementi[sol[i].elementi[1]].difficolta; j++){
                        if(elementi[i].finale == 0 && elementi[j].dirIngresso == 1 &&
                           elementi[j].dirUscita == elementi[sol[i].elementi[1]].dirIngresso){
                            sol[i].elementi[0] = j;
                        }
                    }
                }
            }
        }
    }
    for(i = 0; i < 3; i++){
        j = 0;
        while(sol[i].elementi[j] != -1) {
            sol[i].difficoltaTot += elementi[sol[i].elementi[j]].difficolta;
            sol[i].punteggio += elementi[sol[i].elementi[j]].valore;
            j++;
        }
        if(i == 2 && bonus)
            sol[i].punteggio *= 1.5;
        best_score += sol[i].punteggio;
    }

    printf("DD = %d, DP = %d\nTOT = %.3f\n", DD, DP, best_score);
    for(i = 0; i < 3; i++){
        j = 0;
        if(i == 2 && bonus)
            printf("\nDIAG #3 > %.3f * 1.5 (BONUS)\n", sol[i].punteggio);
        else
            printf("\nDIAG #%d > %.3f\n", i+1, sol[i].punteggio);
        while(j < 5) {
            if(sol[i].elementi[j] != -1)
                printf("%s ", elementi[sol[i].elementi[j]].nome);
            j++;
        }
        printf("\n");
    }
}