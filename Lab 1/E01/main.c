#include <stdio.h>
#include <ctype.h>

#define MAXC 30

char *cercaRegexp(char *src, char *regexp){
    int i = 0, j = 0, k ,t, found = 0, flag;

    while(src[i] != '\0' && !found){
        j = k = 0;
        found = 1;

        while(regexp[j] != '\0' && src[i + k] != '\0' && found){
            if(regexp[j] == '['){
                if(regexp[j+1] != '^'){
                    for(t = j+1; regexp[t] != '\0'; t++){
                        if(src[i+k] == regexp[t]) flag = 1;
                    }
                    if(flag) j = t;
                    else found = 0;
                }
                else{
                    for(t = j+2; regexp[t] != ']'; t++){
                        if(src[i+k] == regexp[t]) flag = 1;
                    }
                    if(flag) found = 0;
                    else j = t;
                }
            }
            else if(regexp[j] == '\\'){
                if(regexp[j+1] == 'a'){
                    if(!islower(src[i+k])) found = 0;
                }
                if(regexp[j+1] == 'A'){
                    if(!isupper(src[i+k])) found = 0;
                }
            }
            else if(regexp[j] != '.'){
                if(regexp[j] != src[i+k]) found = 0;
            }
            j++;
            k++;
        }

        i++;
        if(src[i] == '\0' && regexp[j] != '\0') found = 0;
    }

    if(!found) return NULL;
    else return &src[i-1];
}

int main(void){
    char source[MAXC], reg[MAXC], *ret;

    printf("Inserisci la sequenza di stringe in cui cercare l'espressione regolare: ");
    scanf("%s ", source);
    printf("\nInserisci l'espressione regolare: ");
    scanf("%s", reg);

    ret = cercaRegexp(source, reg);
    printf("%s", ret);
}
