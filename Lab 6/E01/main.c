#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 21

typedef struct{
    int s, f, durata;
} att;

att *leggiFile(int *n);
int comparator(const void *a1, const void *a2);
void predecessore(int *v, att *attivita, int N);
int max(int n1, int n2);
void attDP(int N, att *vett);

int main(void){
    int N, x;
    att *vettAtt = leggiFile(&N);
    qsort(vettAtt, N, sizeof(att), comparator);

    attDP(N, vettAtt);
    free(vettAtt);
}

att *leggiFile(int *n){
    char s[MAXLEN];
    printf("Inserisci il nome del file:\n");
    scanf("%s", s);
    FILE *fin = fopen(s, "r");
    if(fin == NULL){
        printf("Il file inserito non esiste\n");
        return NULL;
    }

    fscanf(fin, "%d", n);
    att *v = malloc(((*n) + 1) * sizeof(att));
    for(int i = 0; i < (*n); i++){
        fscanf(fin, "%d %d", &v[i].s, &v[i].f);
        v[i].durata = v[i].f - v[i].s;
    }
    v[0].f = 0; v[0].s = 0; v[0].durata = 0;
    fclose(fin);

    return v;
}
int comparator(const void *a1, const void *a2){
    att *a_1 = (att *) a1;
    att *a_2 = (att *) a2;
    return (a_1->f)>=(a_2->f);
}
void predecessore(int *v, att *attivita, int N){
    int i, j;
    v[0] = 0;
    for(i = 1; i < N; i++){
        j = i-1;
        while(j > 0 && attivita[i].s < attivita[j].f) j--;
        v[i] = j;
    }
}
int max(int n1, int n2){
    if(n1 > n2) return n1;
    else return n2;
}
void attDP(int N, att *vett){
    int *pred, *dp, *res;
    pred = malloc(N * sizeof(int));
    dp = malloc(N * sizeof(int));
    res = malloc(N * sizeof(int));
    int i, k;
    predecessore(pred, vett, N);

    for(i = 0; i < N; i++){
        dp[0] = 0;
        for(i = 1; i <= N; i++) dp[i] = max(dp[i-1], dp[pred[i]] + vett[i].durata);
        k = 0;
        for(i = N; i > 0;){
            if(vett[i].durata + dp[pred[i]] >= dp[i-1]){
                res[k] = i;
                k++;
                i = pred[i];
            }else i--;
        }
    }
    for(i = k; i >= 0; i--){
    if(vett[res[i]].s != 0 && vett[res[i]].f != 0) printf("%d %d\n", vett[res[i]].s, vett[res[i]].f);
    }


    free(pred); free(dp); free(res);
}
