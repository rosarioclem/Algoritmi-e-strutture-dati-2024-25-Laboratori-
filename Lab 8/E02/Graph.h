#ifndef GRAPH_H
#define GRAPH_H

#include "ST.h"

typedef struct graph *Graph;

Graph GRAPHinit(char *filename);
void GRAPHload(Graph G, char *filename);
void GRAPHinsertE(Graph G, int v, int w, int wt);
void GRAPHfree(Graph G);
int GRAPHgetVertexes(Graph G);
ST GRAPHgetTab(Graph G);
void GRAPHEdges(Graph G, int v);
void GRAPHladjFromMadj(Graph G);
int GRAPHcheckAdjMadj(Graph G, int ind1, int ind2, int ind3);
int GRAPHcheckAdjLadj(Graph G, int ind1, int ind2, int ind3);

#endif