#include "list.h"

struct LISTnode{
    char titolo[MAXLEN];
    Llink next;
    BST bst;
};
struct list{
    Llink head;
    Llink z;
};

static int codeCmp(char *code1, char *code2){
    return strcmp(code1, code2);
}
static Llink NEW(char *tit, Llink next){
    Llink x = malloc(sizeof(*x));
    strcpy(x->titolo, tit);
    x->next = next;
    x->bst = BSTinit();

    return x;
}
static LIST insert(LIST l, char *tit, Item t, float q){
    if(l->head == l->z){
        l->head = NEW(tit, l->z);
        BSTinsert_leaf(l->head->bst, t, q);
    }else{
        Llink x, p;
        for(x = l->head; x != l->z && codeCmp(tit, x->titolo) > 0; p = x, x = x->next);
        if(codeCmp(tit, x->titolo) == 0)
            BSTinsert_leaf(x->bst, t, q);
        else {
            p->next = NEW(tit, x);
            BSTinsert_leaf(p->next->bst, t, q);
        }
    }
    return l;
}
LIST LISTinit(){
    LIST l = malloc(sizeof(*l));
    l->z = NEW("", NULL);
    l->head = l->z;

    return l;
}
void LISTorder_insert(LIST l, char *tit, Item t, float q){
    l = insert(l, tit, t, q);
}
Llink LISTsearch(LIST l, char *tit){
    Llink x;
    for(x = l->head; x != l->z; x = x->next){
        if(codeCmp(tit, x->titolo) == 0)
            break;
    }
    if(x != l->z)
        printf("\nTitolo trovato.\n");
    else
        printf("\nTitolo non esistente.\n");

    return x;
}
Llink LISTsetNULL(LIST l){
    return l->z;
}
BST LISTgetBST(Llink x){
    return x->bst;
}