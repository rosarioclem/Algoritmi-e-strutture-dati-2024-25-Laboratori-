#include <stdio.h>
#include <stdlib.h>

int majority(int *a, int N);

int main(void){

    int n, maj;
    printf("Quanti numeri vuoi inserire?\n");
    scanf("%d", &n);

    int *vet = (int *) malloc(n * sizeof(int));

    for(int i = 0; i < n; i++){
        printf("Inserisci il %do numero: ", i + 1);
        scanf("%d", vet + i);
        printf("\n");
    }

    maj = majority(vet, n);
    free(vet);

    if(maj != -1) printf("Il numero maggioritario e' %d\n", maj);
    else printf("Non esiste un numero maggioriario\n");
}

int majority(int *a, int N){

    int magg, m1, m2, c1 = 0, c2 = 0, cm;

    if(N == 1) return a[0];

    if(N % 2  == 1){

        m1 = majority(a, N/2);
        m2 = majority(a + N/2, N/2 + 1);

        for(int i = 0; i < N; i++){
            if(a[i] == m1) c1++;
            else if(a[i] == m2) c2++;
        }

        if(c1 >= c2){
            magg = m1; cm = c1;
        }else if(c2 > c1){
            magg = m2; cm = c2;
        }

    }else{

        m1 = majority(a, N/2);
        m2 = majority(a + N/2, N/2);

        for(int i = 0; i < N; i++){
            if(a[i] == m1) c1++;
            else if(a[i] == m2) c2++;
        }

        if(c1 >= c2){
            magg = m1; cm = c1;
        }else if(c2 > c1){
            magg = m2; cm = c2;
        }
    }
    if(cm > N/2) return magg;
    else return -1;
}