#include "GRAPH.h"
#include <limits.h>
#define minWt INT_MIN

typedef struct node *link;
struct node{
    int v;
    int wt;
    link next;
};

struct graph{
    int V;
    int E;
    int **madj;
    link *ladj;
    link z;
    ST tab;
};

static link NEW(int v, int wt, link next){
    link x = malloc(sizeof(*x));
    x->v = v;
    x->wt = wt;
    x->next = next;
    return x;
}
static int **MATRIXint(int r, int c, int val){
    int i, j;
    int **t = malloc(r * sizeof(int *));
    for(i = 0; i < r; i++)
        t[i] = malloc(c * sizeof(int));
    for(i = 0; i < r; i++)
        for(j = 0; j < c; j++)
            t[i][j] = val;

    return t;
}
static Edge EDGEcreate(int v, int w, int wt){
    Edge e;
    e.v = v;
    e.w = w;
    e.wt = wt;
    return e;
}
static void insertE(Graph G, Edge e){
    if(G->madj[e.v][e.w] == 0)
        G->E++;
    G->madj[e.v][e.w] = e.wt;
    G->ladj[e.v] = NEW(e.w, e.wt, G->ladj[e.v]);
}
static void removeE(Graph G, Edge e){
    int v = e.v, w = e.w;
    link x, p;
    if(G->madj[v][w] != 0)
        G->E--;
    G->madj[v][w] = 0;
    for(x = G->ladj[v], p = NULL; x != G->z; p = x, x = x->next){
        if(x->v == w){
            if(x == G->ladj[v])
                G->ladj[v] = x->next;
            else
                p->next = x->next;
            break;
        }
    }
}
static void dfsR(int *pre, int *post, int *time, Graph G, Edge e, int *c){
    link t;
    int v, w = e.w;
    pre[w] = (*time)++;
    for(t = G->ladj[w]; t != G->z; t = t->next){
        if(pre[t->v] == -1)
            dfsR(pre, post, time, G, EDGEcreate(w, t->v, 1), c);
        else{
            v = t->v;
            if(post[v] == -1)
                *c = 1;
        }
    }
    post[w] = (*time)++;
}
static void TSdfsR(int *time, int *pre, int *ts, int v, Graph D){
    int w;
    pre[v] = 0;
    for(w = 0; w < D->V; w++){
        if(D->madj[w][v] != -1)
            if(pre[w] == -1)
                TSdfsR(time, pre, ts, w, D);
    }
    ts[(*time)++] = v;
}

Graph GRAPHinit(int V){
    Graph G = malloc(sizeof(*G));
    G->V = V;
    G->E = 0;
    G->z = NEW(-1, -1, NULL);
    G->madj = MATRIXint(V, V, 0);
    G->ladj = malloc(V * sizeof(link));
    for(int i = 0; i < V; i++)
        G->ladj[i] = G->z;
    G->tab = STinit(V, (float) 1/3);

    return G;
}
ST GRAPHgetTab(Graph G){
    return G->tab;
}
void GRAPHinsertE(Graph G, int v, int w, int wt){
    insertE(G, EDGEcreate(v, w, wt));
}
int GRAPHgetIndex(Graph G, char *label){
    int id;
    id = STsearch(G->tab, label);
    if(id == -1){
        id = STcount(G->tab);
        STinsert(G->tab, ITEMcreate(label, id));
    }

    return id;
}
int GRAPHnumEdges(Graph G){
    return G->E;
}
void GRAPHedges(Graph G, Edge *v){
    int i, j, E = 0;
    for(i = 0; i < G->V; i++)
       for(j = 0; j < G->V; j++)
           if(G->madj[i][j] != 0)
               v[E++] = EDGEcreate(i, j, G->madj[i][j]);
}
void GRAPHfree(Graph G){
    int i;
    link x, next;
    for(i = 0; i < G->V; i++)
        free(G->madj[i]);
    free(G->madj);
    for(i = 0; i < G->V; i++)
        for(x = G->ladj[i]; x != G->z; x = next){
            next = x->next;
            free(x);
        }

    STfree(G->tab);
    free(G);
}
void GRAPHremoveE(Graph G, Edge e){
    removeE(G, e);
}
void GRAPHdfs(Graph G, int v, int w, int *c){
    int i, time = 0;
    link x;
    int *pre = malloc(G->V * sizeof(int));
    int *post = malloc(G->V * sizeof(int));
    for(i = 0; i < G->V; i++) {
        pre[i] = -1; post[i] = -1;
    }

    dfsR(pre, post, &time, G, EDGEcreate(v, w, 1), c);

    for(x = G->ladj[w]; x != G->z; x = x->next){
        if(pre[x->v] == -1)
            dfsR(pre, post, &time, G, EDGEcreate(v, w, 1), c);
    }
}
int GRAPHvertex(Graph G){
    return G->V;
}
char *GRAPHdispVertex(Graph G, int i){
    return STsearchByIndex(G->tab, i);
}
void GRAPHts(Graph D){
    int v, time = 0, *pre, *ts;
    ts = malloc(D->V * sizeof(int));
    pre = malloc(D->V * sizeof(int));
    for(v = 0; v < D->V; v++){
        ts[v] = -1; pre[v] = -1;
    }

    for(v = 0; v < D->V; v++)
        if(pre[v] == -1)
            TSdfsR(&time, pre, ts, v, D);

    for(v = 0; v < D->V; v++)
        GRAPHmaxDist(D, ts, v);

    free(ts);
    free(pre);
}
void GRAPHmaxDist(Graph D, int *ts, int v){
    int i, w, *d;
    link t;

    w = ts[v];
    d = malloc(D->V * sizeof(int));
    for(i = 0; i < D->V; i++)
        d[i] = minWt;

    d[w] = 0;
    for(i = v; i < D->V; i++){
        w = ts[i];
        for(t = D->ladj[w]; t != D->z; t = t->next){
            if(d[t->v] < d[w] + t->wt)
                d[t->v] = d[w] + t->wt;
        }
    }

    printf("Distanze massime da %s:\n", STsearchByIndex(D->tab, ts[v]));
    for(i = 0; i < D->V; i++){
        if(d[ts[i]] == minWt || d[ts[i]] < 0)
            printf("Non esiste un percorso da %s a %s\n", STsearchByIndex(D->tab, ts[v]),
            STsearchByIndex(D->tab, ts[i]));
        else if(d[ts[i]] != minWt && d[ts[i]] != 0)
            printf("%s: %d\n", STsearchByIndex(D->tab, ts[i]), d[ts[i]]);
    }

    printf("\n");
    free(d);
}