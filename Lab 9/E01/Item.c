#include "Item.h"

Item ITEMsetNull(){
    Item a;
    a.index = -1;
    strcpy(a.name, "");
    return a;
}
Item ITEMcreate(char *name, int index){
    Item a;
    a.index = index;
    strcpy(a.name, name);
    return a;
}
int ITEMcheckNull(Item a){
    return a.index == -1 && strcmp(a.name, "") == 0;
}
int KEYcmp(Item a, char *label){
    return strcmp(a.name, label) == 0;
}