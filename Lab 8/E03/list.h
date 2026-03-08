#ifndef LIST_H
#define LIST_H
#define MAXLEN 21
#include "bst.h"

typedef struct LISTnode *Llink;
typedef struct list *LIST;

LIST LISTinit();
void LISTorder_insert(LIST l, char *tit, Item t, float q);
Llink LISTsearch(LIST l, char *tit);
Llink LISTsetNULL(LIST l);
BST LISTgetBST(Llink x);

#endif