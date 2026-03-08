#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 50

typedef struct{
    int anno, mese, giorno;
} data;
typedef struct{
    char codice[MAXLEN], nome[MAXLEN], cognome[MAXLEN], via[MAXLEN], citta[MAXLEN], cap[MAXLEN];
    data nascita;
} Item;
typedef struct node{
    Item val;
    struct node *next;
} node_t, *link;

link initHead();
link newNode(link next, Item val);
link insOrd(link head, Item *val);
link searchAndDeleteC(link head, char *code);
link searchAndDeleteD(link head, data prima, data dopo);
link search(link head, char *code);
void printNode(link n);
int confrontaDate(data d1, data d2);
void printListFile(link head);
void funzioni(link head);

int main(void){

    link head, tmp;
    head = initHead();

    funzioni(head);

    while(head != NULL){
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

void funzioni(link head){

    char s[MAXLEN], nomeFile[MAXLEN];
    Item t;
    FILE *fin;
    data d1, d2, temp;
    link extracted, *tmp;

    while(1){
        printf("Cosa vuoi fare? (acquisizione, ricerca, cancellazione, stampa, fine)\n");
        scanf("%s", s);
        if(strcmp(s, "fine") == 0)
            return;
        else if(strcmp(s, "acquisizione") == 0){
            printf("Vuoi acquisire da tastiera o da file?\n");
            scanf("%s", s);
            if(strcmp(s, "tastiera") == 0){
                printf("Inserisci l'anagrafica:\n");
                if(scanf("%s %s %s %d/%d/%d %s %s %s", t.codice, t.nome, t.cognome,
                &t.nascita.giorno, &t.nascita.mese, &t.nascita.anno, t.via, t.citta, t.cap) !=  9){
                    printf("Hai inserito male i dati\n");
                    return;
                }

                head = insOrd(head, &t);

            }else if(strcmp(s, "file") == 0){
                printf("Inserisci il nome del file:\n");
                scanf("%s", nomeFile);
                fin = fopen(nomeFile, "r");
                if(fin == NULL){
                    printf("Il file inserito non esiste\n");
                    return;
                }

                while(fscanf(fin, "%s %s %s %d/%d/%d %s %s %s", t.codice, t.nome, t.cognome,
                            &t.nascita.giorno, &t.nascita.mese, &t.nascita.anno, t.via, t.citta, t.cap) ==  9){
                    head = insOrd(head, &t);
                }
                fclose(fin);
            }else{
                printf("Hai inserito un comando sbagliato\n");
                return;
            }
        }
        else if(strcmp(s, "ricerca") == 0){
            printf("Inserisci il codice dell'anagrafica da stampare:\n");
            scanf("%s", s);

            extracted = search(head, s);
            printNode(extracted);

        }
        else if(strcmp(s, "cancellazione") == 0){

            printf("Vuoi cancellare per codice o tutte le anagrafiche tra due date? (codice, date)\n");
            scanf("%s", s);

            if(strcmp(s, "codice") == 0){
                printf("Inserisci il codice dell'anagrafica da cancellare:\n");
                scanf("%s", s);

               extracted  = searchAndDeleteC(head, s);
               printNode(extracted);
               free(extracted);

            }else if(strcmp(s, "date") == 0){

                printf("Inserisci la prima data:\n");
                scanf("%d/%d/%d", &d1.giorno, &d1.mese, &d1.anno);
                printf("Inserisci la seconda data:\n");
                scanf("%d/%d/%d", &d2.giorno, &d2.mese, &d2.anno);

                if(confrontaDate(d1, d2) > 0){
                    temp = d1; d1 = d2; d2 = temp;
                }

                do{
                    extracted = searchAndDeleteD(head, d1, d2);
                    if(extracted == NULL) break;
                    printNode(extracted);
                    free(extracted);
                }while(extracted != NULL);

            }else{
                printf("Hai inserito un comando sbagliato\n");
                return;
            }
        }
        else if(strcmp(s, "stampa") == 0){
            printListFile(head);
        }
        else{
            printf("Hai inserito un comando sbagliato\n");
            return;
        }
    }
}
link initHead(){
    link x = malloc(sizeof(*x));
    x->next = NULL;
    strcpy(x->val.codice, "\0");
    strcpy(x->val.citta, "\0");
    strcpy(x->val.nome, "\0");
    strcpy(x->val.cognome, "\0");
    strcpy(x->val.via, "\0");
    strcpy(x->val.cap, "\0");
    x->val.nascita.anno = 0;
    x->val.nascita.mese = 0;
    x->val.nascita.giorno = 0;

    return x;
}
link newNode(link next, Item val){

    link x = malloc(sizeof(*x));
    if(x == NULL) return NULL;
    else{
        x->val = val;
        x->next = next;
    }

    return x;
}
link insOrd(link head, Item *val){

    int flag = 0;
    link x, t, p = NULL;
    t = newNode(NULL, *val);
    if(head->next == NULL){
        head->next = t;
    }
    else {
        for (x = head; x != NULL; p = x,  x = x->next){
            if(confrontaDate(t->val.nascita, x->val.nascita) <= 0){
                p->next = t;
                t->next = x;
                flag = 1;
                break;
            }
        }
        if(flag == 0){
            p->next = t;
        }
    }

    return head;

}
link searchAndDeleteC(link head, char *code){

    link x, p;
    for(x = head; x != NULL; p = x, x = x->next) {
        if(strcmp(x->val.codice, code) == 0) {
            p->next = x->next;
            x->next = NULL;
            break;
        }
    }
    return x;

}
link searchAndDeleteD(link head, data prima, data dopo){

    link x, p;
    for(x = head; x != NULL; p = x, x = x->next){
        if(confrontaDate(x->val.nascita, prima) >= 0 && confrontaDate(x->val.nascita, dopo) <= 0){
            p->next = x->next;
            x->next = NULL;
            break;
        }
    }

    return x;

}
link search(link head, char *code){

    link x;
    for(x = head; x != NULL; x = x->next)
        if(strcmp(x->val.codice, code) == 0) return x;

}
void printNode(link n){

    if(n == NULL){
        printf("La lista e' vuota\n");
        return;
    }

    printf("%s %s %s %d/%d/%d %s %s %s\n", n->val.codice, n->val.nome, n->val.cognome,
            n->val.nascita.giorno, n->val.nascita.mese, n->val.nascita.anno, n->val.via, n->val.citta, n->val.cap);
}
int confrontaDate(data d1, data d2){

    if(d1.anno > d2.anno) return 1;
    else if (d1.anno < d2.anno) return -1;
    else{
        if(d1.mese > d2.mese) return 1;
        else if(d1.mese < d2.mese) return -1;
        else{
            if(d1.giorno > d2.giorno) return 1;
            else if(d1.giorno < d2.giorno) return -1;
            return 0;
        }
    }
}
void printListFile(link head){

    if(head == NULL){
        printf("La lista e' vuota\n");
        return;
    }

    link x;
    FILE *fout = fopen("../output.txt", "w");

    for(x = head->next; x != NULL; x = x->next){
        fprintf(fout, "%s %s %s %d/%d/%d %s %s %s\n", x->val.codice, x->val.nome, x->val.cognome,
                x->val.nascita.giorno, x->val.nascita.mese, x->val.nascita.anno, x->val.via, x->val.citta, x->val.cap);
    }

    fclose(fout);
}