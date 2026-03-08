#include "bst.h"

struct binarysearchtree{
    Blink root;
    Blink z;
};

static Blink NEW(Item item, float q, Blink p, Blink l, Blink r, int N){
    Blink x = malloc(sizeof(*x));
    x->item = item;
    x->quot = q;
    x->p = p; x->l = l; x->r = r; x->N = N;

    return x;
}
static Blink insertR(Blink h, Item item, float q, Blink z){
    if(h == z)
        return NEW(item, q, z, z, z, 1);
    if(ITEMcmp(&item, &h->item) < 0) {
        h->l = insertR(h->l, item, q, z);
        h->l->p = h;
    }else{
        h->r = insertR(h->r, item, q, z);
        h->r->p = h;
    }
    (h->N)++;

    return h;
}
static float searchR(Blink node, Blink z, Item data){
    int cmp;
    if(node == z)
        return -1;
    cmp = ITEMcmp(&data, &node->item);
    if(cmp == 0)
        return node->quot;
    if(cmp == -1)
        return searchR(node->l, z, data);
    return searchR(node->r, z, data);
}
static void treeVisit(Blink h, Blink z, Item d1, Item d2, float *min, float *max, Item *dmin, Item *dmax){
    if(h == z){
        return;
    }
    if(ITEMcmp(&d1, &h->item) == -1 && ITEMcmp(&d2, &h->item) == 1){
        if(h->quot > *max) {
            *max = h->quot;
            *dmax = h->item;
        }
        if(h->quot < *min){
            *min = h->quot;
            *dmin = h->item;
        }
    }
    treeVisit(h->l, z, d1, d2, min, max, dmin, dmax);
    treeVisit(h->r, z, d1, d2, min, max, dmin, dmax);
}
static void calcPaths(Blink h, Blink z, int *min, int *max, int curr_len){
    if(h->l == z && h->r == z){
        if(curr_len > *max)
            *max = curr_len;
        if(curr_len < *min)
            *min = curr_len;
        return;
    }
    if(h->l != z)
        calcPaths(h->l, z, min, max, curr_len+1);
    if(h->r != z)
        calcPaths(h->r, z, min, max, curr_len+1);
}
static Blink rotR(Blink h){
    Blink x = h->l;
    h->l = x->r;
    x->r->p = h;
    x->r = h;
    h->p = x;
    x->N = h->N;
    h->N = 1;
    h->N += h->l ? h->l->N : 0;
    h->N += h->r ? h->r->N : 0;
    return x;
}
static Blink rotL(Blink h){
    Blink x = h->r;
    h->r = x->l;
    x->l->p = h;
    x->l = h;
    h->p = x;
    x->N = h->N;
    h->N = 1;
    h->N += h->l ? h->l->N : 0;
    h->N += h->r ? h->r->N : 0;
    return x;
}
static Blink partR(Blink h, int r){
    int t = h->l->N;
    if(t > r){
        h->l = partR(h->l, r);
        h = rotR(h);
    }
    if(t < r){
        h->r = partR(h->r, r-t-1);
        h = rotL(h);
    }
    return h;
}
static Blink balanceR(Blink h, Blink z){
    int r;
    if(h == z)
        return z;
    r = (h->N+1)/2-1;
    h = partR(h, r);
    h->l = balanceR(h->l, z);
    h->r = balanceR(h->r, z);
    return h;
}
BST BSTinit(){
    BST bst = malloc(sizeof(*bst));
    bst->z = NEW(ITEMsetNull(), -1, NULL, NULL, NULL, 0);
    bst->root = bst->z;

    return bst;
}
void BSTinsert_leaf(BST bst, Item item, float q){
    bst->root = insertR(bst->root, item, q, bst->z);
}
float BSTsearch(BST bst, Item data){
    return searchR(bst->root, bst->z, data);
}
void BSTvisit(BST bst, Item d1, Item d2){
    float min = 10000000000, max = -1;
    Item dmin, dmax;
    treeVisit(bst->root, bst->z, d1, d2, &min, &max, &dmin, &dmax);
    if(d1.anno != 0)
        printf("\nQuotazioni minima e massima nell'intervallo [%d/%.2d/%.2d %.2d:%.2d, %d/%.2d/%.2d %.2d:%.2d]:\n",
               d1.anno, d1.mese, d1.giorno, d1.ora, d1.minuti, d2.anno, d2.mese, d2.giorno, d2.ora, d2.minuti);
    else
        printf("\nQuotazioni minima e massima in tutto l'intervallo registrato:\n");
    printf("\nQuotazione minima = %.3f, riscontrata il %d/%.2d/%.2d alle %.2d:%.2d", min, dmin.anno, dmin.mese
    , dmin.giorno, dmin.ora, dmin.minuti);
    printf("\nQuotazione massima = %.3f, riscontrata il %d/%.2d/%.2d alle %.2d:%.2d", max, dmax.anno, dmax.mese
            , dmax.giorno, dmax.ora, dmax.minuti);
}
void BSTcalcMinMaxPath(BST bst, float S){
    int min = 1000000, max = -1;
    calcPaths(bst->root, bst->z, &min, &max, 0);
    if((float) max/min > S){
        printf("\nL'albero verra' bilanciato.\n");
        BSTbalance(bst);
        printf("\nAlbero bilanciato correttamente!\n");
    }
}
void BSTbalance(BST bst){
    bst->root = balanceR(bst->root, bst->z);
}