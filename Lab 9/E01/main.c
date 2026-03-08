#include "GRAPH.h"
#define MAXC 51

typedef enum{
    leggiFILE, indDAG, creaDAG, maxDIST, fine
}comando;

Graph leggiFile();
void createSet(Edge *v, Edge *sol, Edge *maxWt, Graph G, int *max);
Edge *initEdges(int E);
void powerset(int pos, int n, int k, int start, Edge *val, Edge *sol, Edge *wt, Graph G, int *found, int *maxWt);
comando leggiComando(char *c);

int main(void){
    int continua = 1, max = 0, checkDAG = 0, i, checkCreateDAG = 0, checkAlrRead = 0;
    char cmd[MAXC];
    comando c;
    Graph G;
    Edge *v, *sol, *maxWt;

    while(continua){
        printf("Cosa vuoi fare? (leggiFILE, indDAG, creaDAG, maxDIST, fine)\n");
        scanf("%s", cmd);
        c = leggiComando(cmd);
        switch(c){
            case leggiFILE:
                if(checkAlrRead){
                    GRAPHfree(G);
                    free(v);
                    free(sol);
                    free(maxWt);
                    checkCreateDAG = 0;
                    checkDAG = 0;
                }
                G = leggiFile();
                v = malloc(GRAPHnumEdges(G) * sizeof(Edge));
                GRAPHedges(G,v);
                sol = initEdges(GRAPHnumEdges(G)-1);
                maxWt = initEdges(GRAPHnumEdges(G)-1);
                checkAlrRead = 1;
                break;
            case indDAG:
                checkDAG = 1;
                printf("Si individuano gli insiemi di archi di cardinalita' minima per trasforamre il grafo in un DAG\n\n");
                createSet(v, sol, maxWt, G, &max);
                break;
            case creaDAG:
                if(checkDAG){
                    printf("Verranno rimossi gli archi:\n");
                    for(i = 0; maxWt[i].v != -1; i++){
                        printf("%s - %s\n", GRAPHdispVertex(G, maxWt[i].v), GRAPHdispVertex(G, maxWt[i].w));
                        GRAPHremoveE(G, maxWt[i]);
                    }
                    printf("\nCon un peso di %d\n", max);
                    checkCreateDAG = 1;
                }else
                    printf("Non si sono ancora individuati gli insiemi di archi per costruire un DAG\n");
                break;
            case maxDIST:
                if(checkCreateDAG){
                    GRAPHts(G);
                }else
                    printf("Non si e' ancora costruito il DAG\n");
                break;
            case fine:
                printf("Il programma termina\n");
                continua = 0;
                break;
            default:
                printf("Hai inserito un comando sbagliato\n");
                break;

        }
    }

    GRAPHfree(G);
    free(v);
    free(sol);
    free(maxWt);
}

Graph leggiFile(){
    Graph G;
    int V, i, wt;
    char filename[MAXC], vertex1[MAXLEN], vertex2[MAXLEN];

    printf("Inserisci il nome del file: "); scanf("%s", filename); printf("\n");
    FILE *fin = fopen(filename, "r");
    if(fin == NULL) {
        printf("Il file inserito non esiste\n");
        return NULL;
    }

    fscanf(fin, "%d", &V);
    G = GRAPHinit(V);
    for(i = 0; i < V; i++){
        fscanf(fin, "%s", vertex1);
        STinsert(GRAPHgetTab(G), ITEMcreate(vertex1, i));
    }
    while(fscanf(fin, "%s %s %d", vertex1, vertex2, &wt) == 3)
        GRAPHinsertE(G, GRAPHgetIndex(G, vertex1), GRAPHgetIndex(G, vertex2), wt);

    fclose(fin);
    return G;
}
Edge *initEdges(int E){
    Edge *e = malloc(E*sizeof(Edge));
    for(int i = 0; i < E; i++) {
        e[i].v = -1;
        e[i].w = -1;
        e[i].w = 0;
    }

    return e;
}
void createSet(Edge *v, Edge *sol, Edge *maxWt, Graph G, int *max){
    int E = GRAPHnumEdges(G), i;
    int found = 0, firstCheck = 0;

    GRAPHdfs(G, 0, 0, &firstCheck);
    if(firstCheck == 0){
        printf("Il grafo originale e' gia' un DAG, non vengono rimossi archi\n");
        return;
    }

    for(i = 1; i < E-1 && !found; i++){
        powerset(0, E, i, 0, v, sol, maxWt, G, &found, max);
    }

    printf("Cardinalita' minima di archi rimossi per avere un DAG: %d\n", i-1);
}
void powerset(int pos, int n, int k, int start, Edge *val, Edge *sol, Edge *wt, Graph G, int *found, int *maxWt){
    int i, j, checkC = 0, totWt = 0;
    if(pos >= k){
        for(j = 0; j < pos; j++)
            GRAPHremoveE(G, sol[j]);
        GRAPHdfs(G, 0, 0, &checkC);
        for(j = 0; j < pos; j++)
            GRAPHinsertE(G, sol[j].v, sol[j].w, sol[j].wt);

        if(!checkC){
            printf("La rimozione di questi archi rende il grafo un DAG:\n");
            for(j = 0; j < pos; j++){
                printf("%s - %s\n", GRAPHdispVertex(G, sol[j].v), GRAPHdispVertex(G, sol[j].w));
                totWt += sol[j].wt;
            }
            printf("\n");
            *found = 1;
            if(totWt >= *maxWt){
                for(j = 0; j < pos; j++)
                    wt[j] = sol[j];
                *maxWt = totWt;
            }
        }
        return;
    }

    for(i = start; i < n; i++){
        sol[pos] = val[i];
        powerset(pos+1, n, k, i+1, val, sol, wt, G, found, maxWt);
    }
}
comando leggiComando(char *c){
    if(strcmp(c, "leggiFILE") == 0)
        return leggiFILE;
    else if(strcmp(c, "indDAG") == 0)
        return indDAG;
    else if(strcmp(c, "creaDAG") == 0)
        return creaDAG;
    else if(strcmp(c, "maxDIST") == 0)
        return maxDIST;
    else if(strcmp(c, "fine") == 0)
        return fine;
    else
        return -1;
}