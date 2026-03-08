#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int **mat, N, E;
}graph;

void leggiFile(graph *G);
int powerset(int pos, int *val, int *sol, int n, int start, int cnt, graph *G);
int check(int *s, graph *G, int pos);
int in(int x, int *v, int n); //controlla se v contiene x

int main(void){

    int *vert, *sol, cnt = 0;
    graph G;
    leggiFile(&G);
    vert = (int *) malloc(G.N *sizeof(int));
    for(int i = 0; i < G.N; i++)
        vert[i] = i;
    sol = (int *) malloc(G.N *sizeof(int));

    cnt = powerset(0, vert, sol, G.N, 0, cnt, &G);
    printf("Ci sono %d vertex cover\n", cnt);

    for(int i = 0; i < G.N; i++){
        free(G.mat[i]);
    }
    free(G.mat);
    free(vert);
    free(sol);
}

void leggiFile(graph *G){

    int i;
    FILE *fin = fopen("../grafo.txt", "r");
    if(fin == NULL) exit(-1);

    fscanf(fin, "%d %d", &G->N, &G->E);
    G->mat = (int **) malloc(G->N * sizeof(int *));
    for(i = 0; i < G->N; i++){
        G->mat[i] = (int *) malloc(2 * sizeof(int)); /* rappresento il grafo come sequenza di archi , quindi come
        matrice con E righe e due colonne, che rappresentano i vertici connessi per ogni arco*/
    }

    for(i = 0; i < G->E; i++)
        fscanf(fin, "%d %d", &G->mat[i][0], &G->mat[i][1]);

    fclose(fin);

}

int powerset(int pos, int *val, int *sol, int n, int start, int cnt, graph *G){

    int i;
    if(start >= n){
        if(check(sol, G, pos)){
            printf("{ ");
            for(i = 0; i < pos; i++)
                printf("%d ", sol[i]);
            printf("}\n");
            return cnt+1;
        } else return cnt;
    }

    for(i = start; i < n; i++){
        sol[pos] = val[i];
        cnt = powerset(pos+1, val, sol, n, i+1, cnt, G);
    }

    cnt = powerset(pos, val, sol, n, n, cnt, G);
    return cnt;

}

int check(int *s, graph *G, int pos) {

    for (int i = 0; i < G->E; i++) {
        if (in(G->mat[i][0], s, pos) || in(G->mat[i][1], s, pos));
        else return 0;
    }

    return 1;
}

int in(int x, int *v, int n){
    for(int i = 0; i < n; i++){
        if(x == v[i]) return 1;
    }

    return 0;
}