#ifndef ITEM_H
#define ITEM_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Date.h"

typedef struct {
    char *nome;     // Cognome-Nome
    Date nascita;
    Date morte;     // 0/0/0 se in vita
} Item;

// Crea un Item
Item ITEMnew(char *nome, Date nascita, Date morte);
// Confronta due Item (per la ST)
int KEYcmp(Item k1, Item k2);
// Libera memoria stringa
void ITEMfree(Item k);

#endif