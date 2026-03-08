#ifndef GRAPH_H
#define GRAPH_H
#include "ST.h"

typedef struct edge {int v; int w; int wt;} Edge;
typedef struct graph *Graph;

Graph GRAPHinit(int V);
ST GRAPHgetTab(Graph G);
void GRAPHinsertE(Graph G, int v, int w, int wt);
int GRAPHgetIndex(Graph G, char *label);
int GRAPHnumEdges(Graph G);
void GRAPHedges(Graph G, Edge *v);
void GRAPHfree(Graph G);
void GRAPHremoveE(Graph G, Edge e);
void GRAPHdfs(Graph G, int v, int w, int *c);
int GRAPHvertex(Graph G);
char *GRAPHdispVertex(Graph G, int i);
void GRAPHts(Graph D);
void GRAPHmaxDist(Graph D, int *ts, int v);

#endif