#include "Item.h"

Item ITEMsetNull(){
    Item tmp;
    tmp.anno = 0;
    tmp.mese = 0;
    tmp.giorno = 0;
    tmp.ora = 0;
    tmp.minuti = 0;

    return tmp;
}
int ITEMcmp(Item *i1, Item *i2){
    if(i1->anno > i2->anno)
        return 1;
    else if(i1->anno < i2->anno)
        return -1;
    else{
        if(i1->mese > i2->mese)
            return 1;
        else if(i1->mese < i2->mese)
            return -1;
        else{
            if(i1->giorno > i2->giorno)
                return 1;
            else if(i1->giorno < i2->giorno)
                return -1;
            else{
                if(i1->ora > i2->ora)
                    return 1;
                else if(i1->ora < i2->ora)
                    return -1;
                else{
                    if(i1->minuti > i2->minuti)
                        return 1;
                    else if(i1->minuti < i2->minuti)
                        return -1;
                    else
                        return 0;
                }
            }
        }
    }
}
Item ITEMgetItem(){
    Item i;
    printf("\nInserisci la data (formato: aaaa/mm/gg hh:mm):");
    scanf("%d/%d/%d %d:%d", &i.anno, &i.mese, &i.giorno, &i.ora, &i.minuti); printf("\n");

    return i;
}