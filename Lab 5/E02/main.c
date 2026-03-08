#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char C1[2], C2[2];
    int V1, V2;
    int usato;
}tessera;
typedef struct{
    tessera tess;
    int usato, rot;
} casella;

tessera *leggiTessere();
casella *leggiBoard(int *R, int *C, tessera *v);
void wrapper(tessera *tessere, casella *init, int R, int C);
int disp(int pos, int R, int C, casella *sol, casella *init, tessera *tessere, int b_punt);
int check(casella *board, int R, int C);

int main(void){
    int R, C;
    tessera *tessere = leggiTessere();
    casella *init_board = leggiBoard(&R, &C, tessere);

    wrapper(tessere, init_board, R, C);

    free(tessere);
    free(init_board);
}

tessera *leggiTessere(){
    int num;
    tessera *vett;
    FILE *fin = fopen("../tiles.txt", "r");
    if(fin == NULL){
        printf("Il file delle tessere non esiste\n");
        return NULL;
    }

    fscanf(fin, "%d", &num);
    vett = (tessera *) malloc(num * sizeof(tessera));
    for(int i = 0; i < num; i++){
        fscanf(fin, "%s %d %s %d", vett[i].C1, &vett[i].V1, vett[i].C2, &vett[i].V2);
        vett[i].usato = 0;
    }
    fclose(fin);
    return vett;
}
casella *leggiBoard(int *R, int *C, tessera *v){
    int n, o;
    casella *vett;
    FILE *fin = fopen("../board.txt", "r");
    if(fin == NULL){
        printf("Il file della scacchiera non esiste\n");
        return NULL;
    }

    fscanf(fin, "%d %d", R, C);
    vett = (casella *) malloc((*R) * (*C) * sizeof(casella));
    for(int i = 0; i < (*R) * (*C); i++){
        fscanf(fin, "%d/%d ", &n, &o);
        if(n == -1 && o == -1){
            vett[i].usato = 0;
        }else if(o == 0){
            vett[i].usato = 1;
            v[n].usato = 1;
            strcpy(vett[i].tess.C1, v[n].C1);
            strcpy(vett[i].tess.C2, v[n].C2);
            vett[i].tess.V1 = v[n].V1;
            vett[i].tess.V2 = v[n].V2;
        }else if(o == 1){
            vett[i].usato = 1;
            v[n].usato = 1;
            strcpy(vett[i].tess.C1, v[n].C2);
            strcpy(vett[i].tess.C2, v[n].C1);
            vett[i].tess.V1 = v[n].V2;
            vett[i].tess.V2 = v[n].V1;
        }
    }
    fclose(fin);
    return vett;
}
void wrapper(tessera *tessere, casella *init, int R, int C){
    int b_punt = 0;
    casella *sol = malloc(R * C * sizeof(casella));

    b_punt = disp(0, R, C, sol, init, tessere, b_punt);

    printf("Il punteggio migliore ottenibile dalla configurazione iniziale e': %d\n\n", b_punt);
    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            if(sol[i*R + j].rot == 0){
                printf("%s %d %s %d   ", sol[i*R + j].tess.C1, sol[i*R + j].tess.V1, sol[i*R + j].tess.C2,
                       sol[i*R + j].tess.V2);
            }else{
                printf("%s %d %s %d   ", sol[i*R + j].tess.C2, sol[i*R + j].tess.V2, sol[i*R + j].tess.C1,
                       sol[i*R + j].tess.V1);
            }
        }
        printf("\n");
    }
    free(sol);
}
int disp(int pos, int R, int C, casella *sol, casella *init, tessera *tessere, int b_punt){
    int c_punt;
    if(pos >= R*C){
        c_punt = check(init, R, C);
        if(c_punt > b_punt){
            b_punt = c_punt;
            for(int i = 0; i < R*C; i++){
                sol[i].tess = init[i].tess;
                sol[i].rot = init[i].rot;
                sol[i].usato = init[i].usato;
            }
        }
        return b_punt;
    }

    if(init[pos].usato == 1){
        b_punt = disp(pos+1, R, C, sol, init, tessere, b_punt);
        return b_punt;
    }
    for(int i = 0; i < R*C; i++){
        if(tessere[i].usato == 0){
            tessere[i].usato = 1;
            init[pos].usato = 1;
            init[pos].tess = tessere[i];

            init[pos].rot = 0;
            b_punt = disp(pos+1, R, C, sol, init, tessere, b_punt);
            init[pos].rot = 1;
            b_punt = disp(pos+1, R, C, sol, init, tessere, b_punt);
            tessere[i].usato = 0;
            init[pos].usato = 0;
        }
    }
    return b_punt;
}
int check(casella *board, int R, int C){
    int i, j;
    int orizzontale, verticale, tot_o = 0, tot_v = 0, flag;
    char colore[2];

    for(i = 0; i < R; i++){
        orizzontale = 0;
        flag = 1;
        if(board[i*R].rot == 0) strcpy(colore, board[i*R].tess.C1);
        else strcpy(colore, board[i*R].tess.C2);
        for(j = 0; j < C; j++) {
            if (board[i * R + j].rot == 0 && strcmp(board[i * R + j].tess.C1, colore) == 0 && flag)
                orizzontale += board[i*R + j].tess.V1;
            else if(board[i * R + j].rot == 1 && strcmp(board[i * R + j].tess.C2, colore) == 0 && flag)
                orizzontale += board[i*R + j].tess.V2;
            else{
                flag = 0;
                orizzontale = 0;
            }
        }
        tot_o += orizzontale;
    }
    for(i = 0; i < C; i++){
        verticale = 0;
        flag = 1;
        if(board[i].rot == 0) strcpy(colore, board[i].tess.C2);
        else strcpy(colore, board[i].tess.C1);
        for(j = 0; j < R; j++) {
            if (board[i + j * C].rot == 0 && strcmp(board[i + j * C].tess.C2, colore) == 0 && flag)
                verticale += board[i + j * C].tess.V2;
            else if(board[i + j * C].rot == 1 && strcmp(board[i + j * C].tess.C1, colore) == 0 && flag)
                verticale += board[i + j * C].tess.V1;
            else{
                flag = 0;
                verticale = 0;
            }
        }
        tot_v += verticale;
    }

    return (tot_o + tot_v);
}