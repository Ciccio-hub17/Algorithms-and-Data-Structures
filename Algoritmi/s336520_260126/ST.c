#include "ST.h"

struct symboltable {
    Item *a;
    int maxN;
    int size;
};

ST STinit(int maxN) {
    ST st = malloc(sizeof(*st));
    st->a = malloc(maxN * sizeof(Item));
    st->maxN = maxN;
    st->size = 0;
    return st;
}

void STfree(ST st) {
    for (int i = 0; i < st->size; i++) {
        ITEMfree(st->a[i]);
    }
    free(st->a);
    free(st);
}

int STcount(ST st) {
    return st->size;
}

void STinsert(ST st, Item val) {
    if (st->size >= st->maxN) return;
    st->a[st->size++] = val;
}

int STsearch(ST st, Item val) {
    for (int i = 0; i < st->size; i++) {
        if (KEYcmp(st->a[i], val) == 0) return i;
    }
    return -1;
}

Item STItem(ST st, int index) {
    return st->a[index];
}