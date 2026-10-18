#ifndef ST_H
#define ST_H

#include "Item.h"

typedef struct symboltable *ST;

ST STinit(int maxN);
void STfree(ST st);
int STcount(ST st);
void STinsert(ST st, Item val);
int STsearch(ST st, Item val); // Ritorna indice o -1
Item STItem(ST st, int index); // Ritorna Item da indice

#endif