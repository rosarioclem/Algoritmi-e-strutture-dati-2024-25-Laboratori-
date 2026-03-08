#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 21

typedef struct{
    int s, f;
} att;

att* leggiFile(int *N);
void attSel(int N, att *v);
int rec(int pos, att *v, int *val, int *sol, int N, int start, int *b_diff, int c_diff);
int check(int i, att *v, int *val);

int main(void){

    int N;
    att *v;

    v = leggiFile(&N);
    attSel(N, v);

    free(v);
}

att* leggiFile(int *N){


    char *s = malloc(MAXLEN * sizeof(char));
    if(s == NULL) exit(-1);
    printf("Inserisci il nome del file:\n");
    scanf("%s", s);
    FILE *fin = fopen(s, "r");
    if(fin == NULL){
        printf("Il file inserito non esiste\n");
        exit(-1);
    }
    free(s);

    fscanf(fin, "%d", N);
    att *v = (att *) malloc(*N * sizeof(att));
    for(int i = 0; i < *N; i++)
        fscanf(fin, "%d %d", &v[i].s, &v[i].f);


    fclose(fin);
    return v;
}
void attSel(int N, att* v) {

    int b_diff = 0, c_diff = 0;
    int *val = malloc(N * sizeof(int));
    if(val == NULL) exit(-1);
    int *b_sol = malloc(N * sizeof(int));
    if(b_sol == NULL) exit(-1);

    rec(0, v, val, b_sol, N, 0, &b_diff, c_diff);

    printf("La massima somma delle durate vale: %d\n", b_diff);
    printf("Uno dei sottoinsiemi che massimizza la somma delle durate e':\n\n");
    for(int i = 0; i < N; i++){
        if(b_sol[i] == 1){
            printf("( %d, %d )\n", v[i].s, v[i].f);
        }
    }

    free(val);
    free(b_sol);
}
int rec(int pos, att *v, int *val, int *sol, int N, int start, int *b_diff, int c_diff){
    int i;

    if(pos >= N && c_diff > *b_diff){
        *b_diff = c_diff;
        for(int j = 0; j < N; j++){
            sol[j] = val[j];
        }
        return c_diff;
    }

    for(i = start; i < N; i++){

        val[pos] = 1;
        if(check(i, v, val)){
            c_diff += v[i].f - v[i].s;
            c_diff = rec(pos+1, v, val, sol, N, i+1, b_diff, c_diff);
            c_diff -= v[i].f - v[i].s;
        }
        val[pos] = 0;
        c_diff = rec(pos+1, v, val, sol, N, i+1, b_diff, c_diff);
    }
    return c_diff;

}
int check(int i, att *v, int *val){

    att d1, d2;
    d1.s = -1; d1.f = -1; d2.s = -1; d2.f = -1;
    int j, k;

    if(i == 0) return 1;

    for(j = i; j >= 0; j--){
        if(val[j] == 1){
            d1.s = v[j].s;
            d1.f = v[j].f;
            break;
        }
    }
    for(k = j-1; k >= 0; k--){
        if(val[k] == 1){
            d2.s = v[k].s;
            d2.f = v[k].f;
            break;
        }
    }

    if(d1.s == -1 || d1.f == -1 || d2.s == -1 || d2.f == -1) return 1;

    if(d1.s < d2.f) return 0;
    return 1;
}