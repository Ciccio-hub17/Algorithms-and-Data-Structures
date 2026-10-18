#include "Item.h"

Item ITEMnew(char *nome, Date nascita, Date morte) {
    Item x;
    x.nome = strdup(nome);
    x.nascita = nascita;
    x.morte = morte;
    return x;
}

int KEYcmp(Item k1, Item k2) {
    int cmp = strcmp(k1.nome, k2.nome);
    if (cmp != 0) return cmp;
    return DATEcmp(k1.nascita, k2.nascita);
}

void ITEMfree(Item k) {
    if (k.nome) free(k.nome);
}