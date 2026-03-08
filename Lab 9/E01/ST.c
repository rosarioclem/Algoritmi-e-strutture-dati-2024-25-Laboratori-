#include "ST.h"

struct symboltable{
    Item *a;
    int *sp;
    int N;
    int M;
};

static int STsizeSet(int maxN, float alpha){
    int i;
    int primes[16] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31,
                      37, 41, 43, 47, 53};
    if(maxN < primes[15]*alpha){
        for(i = 0; i < 16; i++){
            if(maxN <= primes[i]*alpha)
                return primes[i];
        }
    }else{
        printf("Troppi elementi\n");
        return -1;
    }
}
static int full(ST st, int index){
    return !ITEMcheckNull(st->a[index]);
}

ST STinit(int maxN, float alpha){
    int i;
    ST st = malloc(sizeof(*st));
    st->N = 0;
    st->M = STsizeSet(maxN, alpha);
    if(st->M == -1){
        return NULL;
    }else{
        st->a = malloc(st->M * sizeof(Item));
        st->sp = malloc(st->M * sizeof(int));
        for(i = 0; i < st->M; i++){
            st->a[i] = ITEMsetNull();
            st->sp[i] = -1;
        }
        return st;
    }
}
void STinsert(ST st, Item val){
    int i = hash(val.name, st->M);
    while(full(st, i))
        i = (i+1)%st->M;
    st->a[i] = val;
    st->sp[val.index] = i;
    st->N++;
}
int STsearch(ST st, char *label){
    int i = hash(label, st->M);
    while(full(st, i)){
        if(KEYcmp(st->a[i], label))
            return st->a[i].index;
        i = (i+1)%st->M;
    }
    return ITEMsetNull().index;
}
int hash(char *v, int M){
    int h = 0, base = 127;
    for(; *v != '\0'; v++){
        h = (base * h + *v) % M;
    }
    return h;
}
int STcount(ST st){
    return st->N;
}
void STfree(ST st){
    free(st->a);
    free(st->sp);
    free(st);
}
char *STsearchByIndex(ST st, int i){
    int index = st->sp[i];
    return st->a[index].name;
}