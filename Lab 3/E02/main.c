#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 50

typedef struct{
    char **titoli;
    int num;
}amico;

void leggiFile();
int printSol(amico *vet, char **sol, int cnt, int pos, int N);

int main(void){
    leggiFile();
}

void leggiFile(){
    int i, j, n, nSol = 0, pos = 0;
    amico *v;
    char **soluzioni;
    FILE *fin = fopen("../brani.txt", "r");
    if(fin == NULL){
        printf("File non esistente\n");
        exit(-1);
    }


    fscanf(fin, "%d", &n);
    v = (amico *) malloc(n * sizeof(amico));
    soluzioni = (char **) malloc(n * sizeof(char *));
    for(i = 0; i < n; i++){
        soluzioni[i] = (char *) malloc(MAXLEN * sizeof(char));
    }

    for(i = 0; i < n; i++){
        fscanf(fin, "%d", &v[i].num);
        v[i].titoli = (char **) malloc(v[i].num * sizeof(char *));
        for(j = 0; j < v[i].num; j++){
            v[i].titoli[j] = (char *) malloc(MAXLEN*sizeof(char));
            fscanf(fin, "%s", v[i].titoli[j]);
        }
    }

    nSol = printSol(v, soluzioni, nSol, pos, n);

    printf("Numero di playlist possibili: %d", nSol);

    for(i = 0; i < n; i++){
        free(soluzioni[i]);
    }
    free(soluzioni);
    free(v->titoli);
    free(v);
    fclose(fin);

}

int printSol(amico *vet, char **sol, int cnt, int pos, int N){
    int i, j;

    if(pos >= N){
        printf("Playlist numero %d:\n\n", cnt+1);
        for(j = 0; j < N; j++){
            printf("%s\n", sol[j]);
        }
        printf("\n");
        return cnt + 1;
    }

    for(i = 0; i < vet[pos].num; i++){
        strcpy(sol[pos], vet[pos].titoli[i]);
        cnt = printSol(vet, sol, cnt, pos + 1, N);
    }

    return cnt;
}