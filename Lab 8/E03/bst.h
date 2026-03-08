#ifndef BST_H
#define BST_H
#include "Item.h"
#include <stdlib.h>
#include <string.h>

typedef struct BSTnode *Blink;
struct BSTnode{
    Item item;
    float quot;
    Blink p, r, l;
    int N;
};
typedef struct binarysearchtree *BST;

BST BSTinit();
void BSTinsert_leaf(BST bst, Item item, float q);
float BSTsearch(BST bst, Item data);
void BSTvisit(BST bst, Item d1, Item d2);
void BSTcalcMinMaxPath(BST bst, float S);
void BSTbalance(BST bst);

#endif