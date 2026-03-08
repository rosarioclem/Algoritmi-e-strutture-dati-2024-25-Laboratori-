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
void wrapper(int num_el, int DD, int DP, elemento *v_el);
int generaDiagonali(diagonale **diag, int cnt, int pos, elemento *v_el, int num_el, int k, int *indici, int DD, int *num);
int filtraDiag(int *indici, elemento *v_el, int DD);
int checkDiag(int DD, diagonale *diag, elemento *v_el);
void reallocaDiag(int *num, diagonale **diag);
void find_sol(diagonale *diag, elemento *v_el, int cnt, int DD, int DP);
void powerset(int pos, int DP, diagonale *best_sol, diagonale *sol, elemento *v_el, diagonale *diag, int cnt, float *best_score);
int checkExec(diagonale *sol, elemento *v_el, int DP, float *curr, float best_score);
float calc_val(diagonale *sol, elemento *v_el);
int see_elements(int *indici, elemento *v_el, int pos);

int main(void){
    int num_el;
    int DD, DP;
    elemento *v_el = leggiFile(&num_el);
    printf("Inserisci la difficolta' massima per ogni diagonale (DD): \n");
    scanf("%d", &DD);
    printf("Inserisci la difficolta' massima complessiva (DP):\n");
    scanf("%d", &DP);

    wrapper(num_el, DD, DP, v_el);

    free(v_el);
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
void wrapper(int num_el, int DD, int DP, elemento *v_el){
    int i, cnt = 0, k = 3;
    int indici[5];
    diagonale *diag = malloc(k* sizeof(diagonale));
    for(i = 0; i < k; i++) {
        diag[i].punteggio = 0;
        diag[i].difficoltaTot = 0;
    }

    for(i = 1; i <= 5; i++) {
        for(int j = 0; j < 5; j++)
            indici[j] = -1;
        cnt = generaDiagonali(&diag, cnt, 0, v_el, num_el, i, indici, DD, &k);
    }
    printf("\nDiagonali trovate: %d\nDiagonali allocate: %d\n", cnt, k);

    find_sol(diag, v_el, cnt, DD, DP);
    free(diag);
}
int generaDiagonali(diagonale **diag, int cnt, int pos, elemento *v_el, int num_el, int k, int *indici, int DD, int *num){
    int i, j;

    if(pos >= k){
        if(filtraDiag(indici, v_el, DD) && see_elements(indici, v_el, pos)){
            if(cnt == *num - 1) {
                reallocaDiag(num, diag);
                for(int t = *num/2; t < *num; t++) {
                    for(int z = 0; z < 5; z++)
                        (*diag)[t].elementi[z] = 0;
                    (*diag)[t].difficoltaTot = 0;
                    (*diag)[t].punteggio = 0;
                }
            }
            for(j = 0; j < 5; j++) {
                (*diag)[cnt].elementi[j] = indici[j];
                if(indici[j] != -1){
                    (*diag)[cnt].punteggio += v_el[indici[j]].valore;
                    (*diag)[cnt].difficoltaTot += v_el[indici[j]].difficolta;
                }
            }
            return ++cnt;
        }
        return cnt;
    }

    for(i = 0; i < num_el; i++){
        indici[pos] = i;
        cnt = generaDiagonali(diag, cnt, pos+1, v_el, num_el, k, indici, DD, num);
    }
    return cnt;
}
int filtraDiag(int *indici, elemento *v_el, int DD){
    int i;
    diagonale *diag = malloc(sizeof(diagonale));
    diag->difficoltaTot = 0; diag->punteggio = 0.0;
    for(i = 0; i < 5; i++) {
        diag->elementi[i] = indici[i];
        if(indici[i] != -1) {
            diag->difficoltaTot += v_el[indici[i]].difficolta;
            diag->punteggio += v_el[indici[i]].valore;
        }
    }

    if(checkDiag(DD, diag, v_el)) {
        free(diag);
        return 1;
    }
    free(diag);
    return 0;
}
int see_elements(int *indici, elemento *v_el, int pos){
    for(int i = 0; i < pos; i++){
        if(v_el[indici[i]].tipologia == 2 || v_el[indici[i]].tipologia == 1)
            return 1;
    }
    return 0;
}
int checkDiag(int DD, diagonale *diag, elemento *v_el){
    if(diag->difficoltaTot > DD)
        return 0;
    for(int i = 0; i < 5 && diag->elementi[i] != -1; i++){
        if(i == 0 && v_el[diag->elementi[i]].dirIngresso != 1)
            return 0;
        if(i == 0 && (v_el[diag->elementi[i]].finale == 1 && diag->elementi[i+1] != -1))
            return 0;
        if(i == 0 && v_el[diag->elementi[i]].reqPrec == 1)
            return 0;
        if(i > 0 && (v_el[diag->elementi[i]].dirIngresso != v_el[diag->elementi[i-1]].dirUscita))
            return 0;
        if((i > 0 && i < 4) && (v_el[diag->elementi[i]].finale == 1 && diag->elementi[i+1] != -1))
            return 0;
    }
    return 1;
}
void reallocaDiag(int *num, diagonale **diag){
    *diag = (diagonale *) realloc(*diag,  *num * 2 * sizeof(diagonale));
    *num *= 2;
}
void find_sol(diagonale *diag, elemento *v_el, int cnt, int DD, int DP) {
    diagonale best_sol[3], sol[3];
    float best_score = 0;
    int last;

    powerset(0, DP, best_sol, sol, v_el, diag, cnt, &best_score);

    printf("\nMiglior esecuzione per DD = %d, DP = %d\n", DD, DP);
    printf("TOT = %.3f\n\n", best_score);
    for (int i = 0; i < 3; i++) {
        for(last = 0; best_sol[i].elementi[last] != -1; last++);
        if(i == 2 && v_el[best_sol[i].elementi[last-1]].difficolta >= 8)
            printf("DIAG #%d > %.3f * 1.5 (BONUS)\n", i + 1, best_sol[i].punteggio);
        else
            printf("DIAG #%d > %.3f\n", i + 1, best_sol[i].punteggio);
        for (int j = 0; j < 5 && best_sol[i].elementi[j] != -1; j++)
            printf("%s ", v_el[best_sol[i].elementi[j]].nome);
        printf("\n");
    }
}
void powerset(int pos, int DP, diagonale *best_sol, diagonale *sol, elemento *v_el, diagonale *diag, int cnt, float *best_score){
    int i;
    float curr_score = 0;

    if(pos >= 3){
        if(checkExec(sol, v_el, DP, &curr_score, *best_score)){
            curr_score = calc_val(sol, v_el);
            if(curr_score > *best_score){
                for (int j = 0; j < 3; j++)
                    best_sol[j] = sol[j];
                printf("BEST: %f\n", curr_score);
                *best_score = curr_score;
            }
        }
        return;
    }

    for(i = 0; i < cnt; i++){
        sol[pos] = diag[i];
        powerset(pos + 1, DP, best_sol, sol, v_el, diag, cnt, best_score);
    }
}
int checkExec(diagonale *sol, elemento *v_el, int DP, float *curr, float best_score){
    int i, j;
    int seq = 0, avanti = 0, indietro = 0;
    int diff = 0;

    for(i = 0; i < 3; i++)
        diff += sol[i].difficoltaTot;
    if(diff > DP)
        return 0;

    for(i = 0; i < 3; i++){
        for(j = 0; j < 5 && sol[i].elementi[j] != -1; j++){
            if(v_el[sol[i].elementi[j]].tipologia != 0){
                if(!avanti && v_el[sol[i].elementi[j]].tipologia == 2)
                    avanti = 1;
                else if(!indietro)
                    indietro = 1;
            }
            if(j < 4 && v_el[sol[i].elementi[j+1]].tipologia != 0 && !seq)
                seq = 1;
            if(seq && avanti && indietro)
                return 1;
        }
    }

    return 0;
}
float calc_val(diagonale *sol, elemento *v_el){
    int i;
    float a = 0;
    for(i = 0; i < 2; i++)
        a += sol[i].punteggio;
    for(i = 0; sol[2].elementi[i] != -1; i++);
    if(v_el[sol[2].elementi[i-1]].difficolta >= 8)
        a = a + sol[2].punteggio * 1.5;
    else
        a += sol[2].punteggio;
    return a;
}