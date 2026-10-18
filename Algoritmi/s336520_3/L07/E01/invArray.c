#include "invArray.h"

/* Struttura interna ADT */
struct invArray_s {
    inv_t *vettInv;
    int nInv;
};

/* Creazione ADT */
invArray_t invArray_init() {
    invArray_t invArray = (invArray_t)malloc(sizeof(struct invArray_s));
    if (invArray == NULL) return NULL;
    
    invArray->vettInv = NULL;
    invArray->nInv = 0;
    return invArray;
}

/* Distruzione ADT */
void invArray_free(invArray_t invArray) {
    if (invArray == NULL) return;
    if (invArray->vettInv != NULL) {
        free(invArray->vettInv);
    }
    free(invArray);
}

/* Lettura da file */
void invArray_read(FILE *fp, invArray_t invArray) {
    if (invArray == NULL || fp == NULL) return;
    
    fscanf(fp, "%d", &invArray->nInv);
    invArray->vettInv = (inv_t *)malloc(invArray->nInv * sizeof(inv_t));
    
    if (invArray->vettInv == NULL) {
        invArray->nInv = 0;
        return;
    }
    
    for (int i = 0; i < invArray->nInv; i++) {
        inv_read(fp, &invArray->vettInv[i]);
    }
}

/* Stampa tutto l'inventario */
void invArray_print(FILE *fp, invArray_t invArray) {
    if (invArray == NULL || fp == NULL) return;
    
    fprintf(fp, "\n=== INVENTARIO (%d oggetti) ===\n", invArray->nInv);
    for (int i = 0; i < invArray->nInv; i++) {
        fprintf(fp, "[%d] ", i);
        inv_print(fp, &invArray->vettInv[i]);
    }
}

/* Stampa oggetto per indice */
void invArray_printByIndex(FILE *fp, invArray_t invArray, int index) {
    if (invArray == NULL || fp == NULL) return;
    if (index < 0 || index >= invArray->nInv) return;
    
    inv_print(fp, &invArray->vettInv[index]);
}

/* Ritorna puntatore a oggetto per indice */
inv_t *invArray_getByIndex(invArray_t invArray, int index) {
    if (invArray == NULL) return NULL;
    if (index < 0 || index >= invArray->nInv) return NULL;
    
    return &invArray->vettInv[index];
}

/* Cerca oggetto per nome, ritorna indice (-1 se non trovato) */
int invArray_searchByName(invArray_t invArray, char *name) {
    if (invArray == NULL || name == NULL) return -1;
    
    for (int i = 0; i < invArray->nInv; i++) {
        if (strcmp(invArray->vettInv[i].nome, name) == 0) {
            return i;
        }
    }
    return -1;
}