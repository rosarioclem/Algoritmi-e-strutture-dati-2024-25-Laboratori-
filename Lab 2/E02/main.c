#include <stdio.h>
#include <stdlib.h>

int **malloc2dR(int *r, int *c);
void separa(int **mat, int r, int c, int *b, int *n, int *f);

int main(void){

    int nr, nc, *bianco, *nero, flag = 0;
    int **m = malloc2dR(&nr, &nc);
    if (m == NULL) return -1;

    if ((nr * nc) % 2 == 1) {
        bianco = (int *) malloc((((nr * nc)/2) + 1) * sizeof(int));
        nero = (int *) malloc(((nr * nc)/2) * sizeof(int));
        flag = 1;
    }
    else{
        bianco = (int *) malloc((nr * nc)/2 * sizeof(int));
        nero = (int *) malloc((nr * nc)/2 * sizeof(int));
    }

    separa(m, nr, nc, bianco, nero, &flag);

    free(bianco);
    free(nero);
    for(int i = 0; i < nr; i++){
        free(m[i]);
    }
    free(m);

    return 1;

}

int **malloc2dR(int *r, int *c){

    FILE *fin = fopen("../mat.txt", "r");
    if (fin == NULL) return NULL;

    int nr, nc;
    fscanf(fin, "%d %d", &nr, &nc);
    *r = nr; *c = nc;

    int **m = (int **) malloc(nr * sizeof(int *));
    for(int i = 0; i < nc; i++){
        m[i] = (int *) malloc(nc * sizeof(int));
    }

    for(int i = 0; i < nr; i++){
        for(int j = 0; j < nc; j++){
            fscanf(fin, "%d", &m[i][j]);
        }
    }

    return m;
}
void separa(int **mat, int r, int c, int *b, int *n, int *f){
    int i, j, k = 0, t = 0;

    for(i = 0; i < r; i++){
        for(j = 0; j < c; j++){
            if((i + 1 + j + 1) % 2 == 0){
                b[k] = mat[i][j];
                k++;
            }else {
                n[t] = mat[i][j];
                t++;
            }
        }
    }

    if(*f){
        printf("Vettore caselle bianche: ");
        for (i = 0; i < (r * c)/2 + 1; i++) {
            printf("%d ", b[i]);
        }
        printf("\n");
        printf("Vettore caselle nere: ");
        for (i = 0; i < (r*c)/2; i++) {
            printf("%d ", n[i]);
        }
    }else{
        printf("Vettore caselle bianche: ");
        for (i = 0; i < (r * c)/2; i++) {
            printf("%d ", b[i]);
        }
        printf("\n");
        printf("Vettore caselle nere: ");
        for (i = 0; i < (r*c)/2; i++) {
            printf("%d ", n[i]);
        }
    }
}
