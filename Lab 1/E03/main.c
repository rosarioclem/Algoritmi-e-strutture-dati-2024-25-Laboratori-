#include <stdio.h>
#include <string.h>

#define MAXLEN 31
#define MAXR 1000

typedef struct{
    int anno, mese, giorno;
} date;

typedef struct{
    int ora, minuti, secondi;
}orari;

typedef struct{
    char codice[MAXLEN];
    char partenza[MAXLEN];
    char destinazione[MAXLEN];
    date data;
    orari orario_p, orario_a;
    int ritardo;
} corsa;

enum comando {
    stampa, ordina_d, ordina_c, ordina_p, ordina_a, ricerca, fine
};

void leggiFile(FILE *fin, corsa *v);
int confronta(corsa c1, corsa c2);
void printCorsa(corsa c);
enum comando leggiComando(char *s);
void ordinamento(corsa *v, enum comando c, int N, int *f);
void linSearch(corsa *v, int N, char *s);
void diSearch(corsa *v, int l, int r, char *s);

int main(void){

    int continua = 1, n, flag = 0;
    enum comando cmd;
    char com[20];
    FILE *fin = fopen("../corse.txt", "r");
    if(fin == NULL) return -1;

    fscanf(fin, "%d", &n);
    if(n > MAXR){
        printf("Il file e' troppo lungo.\n");
        return -1;
    }
    corsa vCorse[n];
    leggiFile(fin, vCorse);
    fclose(fin);


    while(continua) {

        printf("Cosa vuoi fare? (stampa, ordina data, ordina codice, ordina partenza, ordina arrivo, ricerca, fine)\n");
        gets(com);
        cmd = leggiComando(com);
        if(cmd == -1) return -1;

        switch (cmd) {
            case stampa:
                char s[10], string[MAXLEN];
                printf("Vuoi stampare su file o su schermo?\n");
                gets(s);
                if (strcmp(s, "file") == 0) {
                    FILE *fout = fopen("../print.txt", "w");
                    FILE *fin = fopen("../corse.txt", "r");
                    while (fscanf(fin, "%s ", string) == 1) {
                        fprintf(fout, "%s\n", string);
                    }
                    fclose(fin);
                    fclose(fout);
                } else if (strcmp(s, "schermo") == 0) {
                    for (int i = 0; i < n; i++) {
                        printCorsa(vCorse[i]);
                    }
                }
                break;
            case ordina_d:
                ordinamento(vCorse, ordina_d, n, &flag);
                break;
            case ordina_a:
                ordinamento(vCorse, ordina_a, n, &flag);
                break;
            case ordina_c:
                ordinamento(vCorse, ordina_c, n, &flag);
                break;
            case ordina_p:
                ordinamento(vCorse, ordina_p, n, &flag);
                break;
            case ricerca:
                char stazione[MAXLEN];
                int search;
                printf("Vuoi cercare tutte le corse con una determinata partenza (1) o la prima"
                       "corsa con una determinata partenza? (solo se vettore ordinato) (2):\n");
                scanf("%d", &search);
                if(search == 1) {
                    printf("Inserisci la stazione di partenza (anche una sottostringa della stazione):\n");
                    scanf("%s ", stazione);
                    linSearch(vCorse, n, stazione);
                }else if (search == 2 && flag){
                    printf("Inserisci la stazione di partenza (anche una sottostringa della stazione):\n");
                    scanf("%s ", stazione);
                    diSearch(vCorse, 0, n, stazione);
                }else printf("Hai inserito un comando sbagliato\n");
                break;
            case fine:
                continua = 0;
                break;
        }
    }

}

void leggiFile(FILE *fin, corsa *v){

    char data[MAXLEN], oa[MAXLEN], op[MAXLEN];

    for(int i = 0; fscanf(fin, "%s %s %s %s %s %s %d", v[i].codice, v[i].partenza
                          , v[i].destinazione, data, oa, op, &v[i].ritardo) == 7; i++){
        sscanf(data, "%d/%d/%d", &v[i].data.anno, &v[i].data.mese, &v[i].data.giorno);
        sscanf(oa, "%d:%d:%d", &v[i].orario_p.ora, &v[i].orario_p.minuti, &v[i].orario_p.secondi);
        sscanf(op, "%d:%d:%d", &v[i].orario_a.ora, &v[i].orario_a.minuti, &v[i].orario_a.secondi);
    }

}
void printCorsa(corsa c){

    printf("Corsa:\n%s %s %s %d/%d/%d %.2d:%.2d:%.2d %.2d:%.2d:%.2d %d\n\n", c.codice, c.partenza, c.destinazione,
           c.data.anno, c.data.mese, c.data.giorno, c.orario_p.ora, c.orario_p.minuti, c.orario_p.secondi,
           c.orario_a.ora, c.orario_a.minuti, c.orario_a.secondi, c.ritardo);

}
enum comando leggiComando(char *s){
    if(strcmp("stampa", s) == 0) return stampa;
    else if(strcmp("ordina data", s) == 0) return ordina_d;
    else if(strcmp("ordina codice", s) == 0) return ordina_c;
    else if(strcmp("ordina partenza", s) == 0) return ordina_p;
    else if(strcmp("ordina arrivo", s) == 0) return ordina_a;
    else if(strcmp("ricerca", s) == 0) return ricerca;
    else if(strcmp("fine", s) == 0) return fine;
    else { printf("Hai inserito un comando sbagliato\n"); return -1;}
}
int confronta(corsa c1, corsa c2){

    int a = 0, m = 0, g = 0, o = 0, min = 0, s = 0;

    if(c1.data.anno > c2.data.anno) a = 1;
    else if(c1.data.anno ==  c2.data.anno){
        if(c1.data.mese > c2.data.mese) m = 1;
        else if(c1.data.mese == c2.data.mese){
            if(c1.data.giorno > c2.data.giorno) g = 1;
            else if(c1.data.giorno == c2.data.giorno){
                if(c1.orario_p.ora > c2.orario_p.ora) o = 1;
                else if(c1.orario_p.ora == c2.orario_p.ora){
                    if(c1.orario_p.minuti > c2.orario_p.minuti) min = 1;
                    else if(c1.orario_p.secondi > c2.orario_p.secondi) s = 1;
                }
            }
        }
    }

    if(a || m || g || o || min || s) return 1;
    return 0;
}
void ordinamento(corsa v[], enum comando c, int N, int *flag){

    int i, j;
    corsa temp;

    switch(c){
        case ordina_d:
            int scambio = 0;
            for(i = 0; i < N; i++){
                for(j = i + 1; j < N; j++){
                    scambio = confronta(v[i], v[j]);
                    if(scambio){
                        temp = v[i];
                        v[i] = v[j];
                        v[j] = temp;
                    }
                }
            }
            *flag = 0;
            break;
        case ordina_p:
            for(i = 0; i < N; i++){
                for(j = i + 1; j < N; j++){
                    if(strcmp(v[j].partenza, v[i].partenza) < 0){
                        temp = v[i];
                        v[i] = v[j];
                        v[j] = temp;
                    }
                }
            }
            *flag = 1;
            break;
        case ordina_a:
            for(i = 0; i < N; i++){
                for(j = i + 1; j < N; j++){
                    if(strcmp(v[j].destinazione, v[i].destinazione) < 0){
                        temp = v[i];
                        v[i] = v[j];
                        v[j] = temp;
                    }
                }
            }
            *flag = 0;
            break;
        case ordina_c:
            for(i = 0; i < N; i++){
                for(j = i + 1; j < N; j++){
                    if(strcmp(v[j].codice, v[i].codice) < 0){
                        temp = v[i];
                        v[i] = v[j];
                        v[j] = temp;
                    }
                }
            }
            *flag = 0;
            break;
    }
}
void linSearch(corsa *v, int N, char *s){
    for(int i = 0; i < N; i++){
        if(strncmp(v[i].partenza, s, strlen(s)) == 0){
            printCorsa(v[i]);
        }
    }
}
void diSearch(corsa *v, int l, int r, char *s){
    int m = (l+r)/2;

    if (l > r) return;

    if(strncmp(v[m].partenza, s, strlen(s)) == 0){
        printCorsa(v[m]);
        return;
    }
    if(strncmp(v[m].partenza, s, strlen(s)) > 0) return diSearch(v, l, m, s);

    return diSearch(v, m+1, r, s);
}