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

enum comando{
    r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine
};

enum comando leggiComando(char *s);
void leggiFile(FILE *fin, corsa *v);
void selezionaDati(corsa *v, int N, enum comando c);
int confrontaDate(date min, date magg);
void printCorsa(corsa c);

int main(void){

    FILE *fin = fopen("../corse.txt", "r");
    if(fin == NULL) return -1;

    char com[20];
    int continua = 1, n;
    enum comando cmd;

    fscanf(fin, "%d", &n);
    if(n > MAXR){
        printf("Il file e' troppo lungo.\n");
        return -1;
    }
    corsa vCorse[n];
    leggiFile(fin, vCorse);
    fclose(fin);

    while(continua){

        printf("Inserisci un comando (date, partenza, capolinea, ritardo, ritardo_tot, fine)\n");
        gets(com);

        cmd = leggiComando(com);

        switch(cmd){
            case r_date:
                selezionaDati(vCorse, n, r_date);
                break;
            case r_partenza:
                selezionaDati(vCorse, n, r_partenza);
                break;
            case r_capolinea:
                selezionaDati(vCorse, n, r_capolinea);
                break;
            case r_ritardo:
                selezionaDati(vCorse, n, r_ritardo);
                break;
            case r_ritardo_tot:
                selezionaDati(vCorse, n, r_ritardo_tot);
                break;
            case r_fine:
                printf("Conclusione del programma\n");
                continua = 0;
                break;
            default:
                printf("Hai inserito un comando sbagliato\n");
                return 0;
        }
    }
}

enum comando leggiComando(char *s){

    enum comando c  = r_date;
    char comandi[r_fine + 1][15] = {"date", "partenza", "capolinea", "ritardo",
        "ritardo_tot", "fine"};

    while(c < r_fine + 1 && strcmp(s, comandi[c]) != 0) c++;

    if(c > r_fine) return -1;
    return c;
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
int confrontaDate(date min, date magg){

    if(magg.anno > min.anno) return magg.anno - min.anno;
    else if(magg.mese > min.mese) return magg.mese - min.mese;
    else if(magg.giorno > min.giorno) return magg.giorno - min.giorno;

    return 0;

}
void printCorsa(corsa c){

    printf("Corsa:\n%s %s %s %d/%d/%d %d:%d:%d %d:%d:%d %d\n\n", c.codice, c.partenza, c.destinazione,
           c.data.anno, c.data.mese, c.data.giorno, c.orario_p.ora, c.orario_p.minuti, c.orario_p.secondi,
           c.orario_a.ora, c.orario_a.minuti, c.orario_a.secondi, c.ritardo);

}
void selezionaDati(corsa *v, int N, enum comando c){

    date datai, dataf;
    char fermata[MAXLEN], codice[MAXLEN];
    int rt = 0;

    switch(c){
        case r_date:
            printf("Inserisci la data di inizio (formato aa/mm/gg):\n");
            scanf("%d/%d/%d", &datai.anno, &datai.mese, &datai.giorno);
            printf("Inserisci la data di fine (formato aa/mm/gg):\n");
            scanf("%d/%d/%d", &dataf.anno, &dataf.mese, &dataf.giorno);

            for(int i = 0; i < N && confrontaDate(datai, v[i].data) >= 0 && confrontaDate(v[i].data, dataf) >=0; i++){
                printCorsa(v[i]);
            }
            break;
        case r_partenza:
            printf("Inserisci la fermata di partenza:\n");
            scanf("%s ", fermata);
            for(int i = 0; i < N; i++){
                if(strcmp(fermata, v[i].partenza) == 0) printCorsa(v[i]);
            }
            break;
        case r_capolinea:
            printf("Inserisci la fermata di capolinea:\n");
            scanf("%s ", fermata);
            for(int i = 0; i < N; i++){
                if(strcmp(fermata, v[i].destinazione) == 0) printCorsa(v[i]);
            }
            break;
        case r_ritardo:
            printf("Inserisci la data di inizio (formato aa/mm/gg):\n");
            scanf("%d/%d/%d", &datai.anno, &datai.mese, &datai.giorno);
            printf("Inserisci la data di fine (formato aa/mm/gg):\n");
            scanf("%d/%d/%d", &dataf.anno, &dataf.mese, &dataf.giorno);

            for(int i = 0; i < N && v[i].ritardo > 0 && confrontaDate(datai, v[i].data) >= 0 && confrontaDate(v[i].data, dataf) >=0; i++){
                printCorsa(v[i]);
            }
            break;
        case r_ritardo_tot:
            printf("Inserisci il codice della tratta:\n");
            scanf("%s ", codice);

            for(int i = 0; i < N; i++){
                if(strcmp(codice, v[i].codice) == 0){
                    printCorsa(v[i]); rt += v[i].ritardo;
                }
            }

            printf("Il ritardo complessivo di quelle corse e': %d\n", rt);

    }
}