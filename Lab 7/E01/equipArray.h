#ifndef EQUIPARRAYH
#define EQUIPARRAYH

#include "invArray.h"

typedef struct equipArray_t *equipArray;

equipArray initEquipArray();
int equipArray_addObj(equipArray equip, invArray v, int *index);
int equipArray_removeObj(equipArray equip, invArray v, int *index);
int equipArray_usingObjs(equipArray equip);
void equipArray_printAllObjs(equipArray equip, invArray inv);
void equipArray_free(equipArray equip);
int equipArray_getNumObjs(equipArray equip);

#endif