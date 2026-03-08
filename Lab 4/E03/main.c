#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 51

typedef struct{
  int z, r, t, s;
  int pietre_tot;
} pietre;

pietre* leggiFile(int *n);
void wrapper(pietre *v, int n);
void disp_r(int pos, int *val, int *sol, int max, int curr_l, int *best, int *b_sol);
int checkChain(int *sol, int l);
int checkRemaining(int *val, int *sol, int pos);
void printSol(int *sol, pietre c, int l);
void initVal(int *val, pietre p);
void initSol(int *sol, int n);

int main(void){
    int N;
    pietre *v  = leggiFile(&N);
    wrapper(v, N);

    free(v);
}

pietre* leggiFile(int *n){
    pietre *v;
    char s[MAXLEN];

    printf("Inserisci il nome del file:\n");
    scanf("%s", s);
    FILE *fin = fopen(s, "r");
    if(fin == NULL){
        printf("Il file non esiste");
        exit(-1);
    }

    fscanf(fin, "%d\n", n);
    v = (pietre *) malloc(*n * sizeof(pietre));
    for(int i = 0; i < *n; i++){
        fscanf(fin, "%d %d %d %d", &v[i].z, &v[i].r, &v[i].t, &v[i].s);
        v[i].pietre_tot = v[i].z + v[i].r + v[i].t + v[i].s;
    }
    fclose(fin);
    return v;
}
void wrapper(pietre *v, int n){
    int lungh = 0;
    int *val = malloc(4 * sizeof(int));
    for(int i = 0; i < n; i++){
        int *sol = malloc(v[i].pietre_tot * sizeof(int));
        int *b_sol = malloc(v[i].pietre_tot * sizeof(int));
        initVal(val, v[i]);
        initSol(sol, v[i].pietre_tot);

        disp_r(0, val, sol, v[i].pietre_tot, 0, &lungh, b_sol);

        printSol(b_sol, v[i], lungh);
        lungh = 0;
        free(sol);
        free(b_sol);
    }
    free(val);
}
void disp_r(int pos, int *val, int *sol, int max, int curr_l, int *best, int *b_sol){
    int i;
    if(pos >= max || checkRemaining(val, sol, pos) == 0){
        if(checkChain(sol, curr_l) && curr_l > *best){
            *best = curr_l;
            for(int j = 0; j < pos; j++){
                b_sol[j] = sol[j];
            }
            return;
        }
    }

    for(i = 0; i < 4; i++){
        if(checkChain(sol, curr_l) && val[i] > 0){
            sol[pos] = i;
            val[i]--; curr_l++;
            disp_r(pos+1, val, sol, max, curr_l, best, b_sol);
            val[i]++; curr_l--;
        }

    }
}
int checkChain(int *sol, int l){
    for(int i = 0; i < l - 1; i++){
        if(sol[i] == 0 && (sol[i+1] != 0 && sol[i+1] != 1)) return 0;
        else if(sol[i] == 1 && (sol[i+1] != 2 && sol[i+1] != 3)) return 0;
        else if(sol[i] == 2 && (sol[i+1] != 0 && sol[i+1] != 1)) return 0;
        else if(sol[i] == 3 && (sol[i+1] != 2 && sol[i+1] != 3)) return 0;
    }
    return 1;
}
int checkRemaining(int *val, int *sol, int pos){
    if(pos == 0) return 1;
    if(sol[pos-1] == 0 && (val[0] <= 0 && val[1] <= 0)) return 0;
    else if(sol[pos-1] == 1 && (val[2] <= 0 && val[3] <= 0)) return 0;
    else if(sol[pos-1] == 2 && (val[0] <= 0 && val[1] <= 0)) return 0;
    else if(sol[pos-1] == 3 && (val[2] <= 0 && val[3] <= 0)) return 0;

    return 1;
}
void initVal(int *val, pietre p){
    val[0] = p.z;
    val[1] = p.r;
    val[2] = p.t;
    val[3] = p.s;
}
void initSol(int *sol, int n){
    for(int i = 0; i < n; i++)
        sol[i] = -1;
}
void printSol(int *sol, pietre c, int l){

    printf("zaffiro = %d, rubino = %d, topazio = %d, smeraldo = %d, TOT = %d\n", c.z, c.r, c.t, c.s, c.pietre_tot);
    printf("Collana di massima di lunghezza %d\n", l);

    for(int i = 0; i < l; i++){
        if(sol[i] == 0) printf("z ");
        else if(sol[i] == 1) printf("r ");
        else if(sol[i] == 2) printf("t ");
        else if(sol[i] == 3) printf("s ");
        if((i+1)%4 == 0) printf("\n");
    }
    printf("\n\n");
}
