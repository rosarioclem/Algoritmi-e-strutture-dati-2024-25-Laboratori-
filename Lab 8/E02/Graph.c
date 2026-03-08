#include "Graph.h"

typedef struct node *link;
struct node{
    int v, wt;
    link next;
};
struct graph{
    int V, E;
    int **madj;
    link *ladj, z;
    ST tab;
};

static link NEW(int v, int wt, link next){
    link x = malloc(sizeof(*x));
    x->v = v; x->wt = wt; x->next = next;

    return x;
}
Graph GRAPHinit(char *filename){
    int E, i, j;
    Graph G = malloc(sizeof(*G));

    G->tab = STinit(filename, &E);
    G->E = E;
    G->V = STcount(G->tab);
    G->z = NEW(-1, -1, NULL);

    G->madj = malloc(G->V * sizeof(int *));
    for(i = 0; i < G->V; i++)
        G->madj[i] = malloc(G->V * sizeof(int));

    for(i = 0; i < G->V; i++)
        for(j = 0; j < G->V; j++)
            G->madj[i][j] = 0;

    G->ladj = malloc(G->V * sizeof(link));
    for(i = 0; i < G->V; i++)
        G->ladj[i] = G->z;

    return G;
}
void GRAPHload(Graph G, char *filename){
    FILE *fin = fopen(filename, "r");
    Item i1, i2;
    int wt;

    while(fscanf(fin, "%s %s %s %s %d", i1.id_elab, i1.id_rete, i2.id_elab, i2.id_rete, &wt) == 5){
        GRAPHinsertE(G, STsearch(G->tab, &i1), STsearch(G->tab, &i2), wt);
    }

    fclose(fin);
}
void GRAPHinsertE(Graph G, int v, int w, int wt){
    if(G->madj[v][w] == 0){
        G->madj[v][w] = wt;
        G->madj[w][v] = wt;
    }else
        printf("L'arco esiste gia'\n");
}
void GRAPHfree(Graph G){
    int i;
    link x, next;
    for(i = 0; i < G->V; i++)
        free(G->madj[i]);
    free(G->madj);
    for(i = 0; i < G->V; i++) {
        for (x = G->ladj[i]; x != G->z; x = next) {
            next = x->next;
            free(x);
        }
    }
    free(G->ladj);
    STfree(G->tab);
    free(G);
}
int GRAPHgetVertexes(Graph G){
    return G->V;
}
ST GRAPHgetTab(Graph G){
    return G->tab;
}
void GRAPHEdges(Graph G, int v){
    int w, numE = 0;
    for(w = 0; w < G->V; w++){
        if(G->madj[v][w] != 0)
            numE++;
    }
    int *wts = malloc(numE * sizeof(int));
    Item *items = malloc(numE * sizeof(Item));
    numE = 0;
    for(w = 0; w < G->V; w++){
        if(G->madj[v][w] != 0){
            items[numE] = STgetItem(G->tab, w);
            wts[numE] = G->madj[v][w];
            numE++;
        }
    }
    qsort(items, numE, sizeof(Item), ITEMalphCmp);
    for(w = 0; w < numE; w++) {
        printf("Arco: ");
        STprintName(G->tab, v);
        printf("-%s, peso %d\n", items[w].id_elab, wts[w]);
    }

    free(wts);
    free(items);
}
void GRAPHladjFromMadj(Graph G){
    int i, j;
    for(i = 0; i < G->V; i++){
        for(j = 0; j < G->V; j++){
            if(G->madj[i][j] != 0)
                G->ladj[i] = NEW(j, G->madj[i][j], G->ladj[i]);
        }
    }
}
int GRAPHcheckAdjMadj(Graph G, int ind1, int ind2, int ind3){
    if(G->madj[ind1][ind2] != 0 && G->madj[ind1][ind3] != 0 && G->madj[ind2][ind3] != 0)
        return 1;
    return 0;
}
int GRAPHcheckAdjLadj(Graph G, int ind1, int ind2, int ind3){
    link x;
    int cond1_2 = 0, cond1_3 = 0, cond2_3 = 0;
    for(x = G->ladj[ind1]; x != G->z; x = x->next){
        if(x->v == ind2){
            cond1_2 = 1;
            break;
        }
    }
    for(x = G->ladj[ind1]; x != G->z; x = x->next){
        if(x->v == ind3){
            cond1_3 = 1;
            break;
        }
    }
    for(x = G->ladj[ind2]; x != G->z; x = x->next){
        if(x->v == ind3){
            cond2_3 = 1;
            break;
        }
    }

    return cond1_2 && cond1_3 && cond2_3;
}