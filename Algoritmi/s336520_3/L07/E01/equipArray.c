#include "equipArray.h"

/* Struttura interna ADT */
struct equipArray_s {
    int vettEq[EQUIP_SLOT];  /* indici degli oggetti in inventario */
    int nEq;                  /* numero slot occupati */
};

/* Creazione ADT */
equipArray_t equipArray_init() {
    equipArray_t equipArray = (equipArray_t)malloc(sizeof(struct equipArray_s));
    if (equipArray == NULL) return NULL;
    
    equipArray->nEq = 0;
    for (int i = 0; i < EQUIP_SLOT; i++) {
        equipArray->vettEq[i] = -1;  /* -1 = slot vuoto */
    }
    return equipArray;
}

/* Distruzione ADT */
void equipArray_free(equipArray_t equipArray) {
    if (equipArray != NULL) {
        free(equipArray);
    }
}

/* Quanti equipaggiamenti in uso */
int equipArray_inUse(equipArray_t equipArray) {
    if (equipArray == NULL) return 0;
    return equipArray->nEq;
}

/* Stampa equipaggiamento */
void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray) {
    if (equipArray == NULL || fp == NULL || invArray == NULL) return;
    
    fprintf(fp, "  Equipaggiamento (%d/%d slot):\n", equipArray->nEq, EQUIP_SLOT);
    if (equipArray->nEq == 0) {
        fprintf(fp, "    (nessun equipaggiamento)\n");
        return;
    }
    
    for (int i = 0; i < EQUIP_SLOT; i++) {
        if (equipArray->vettEq[i] != -1) {
            fprintf(fp, "    [%d] ", i);
            invArray_printByIndex(fp, invArray, equipArray->vettEq[i]);
        }
    }
}

/* Modifica equipaggiamento */
void equipArray_update(equipArray_t equipArray, invArray_t invArray) {
    if (equipArray == NULL || invArray == NULL) return;
    
    int scelta, indiceInv, slotEq;
    
    printf("\n1. Aggiungi oggetto\n2. Rimuovi oggetto\nScelta: ");
    scanf("%d", &scelta);
    
    if (scelta == 1) {
        /* Aggiungi oggetto */
        if (equipArray->nEq >= EQUIP_SLOT) {
            printf("Equipaggiamento pieno!\n");
            return;
        }
        
        printf("Inserisci indice oggetto da inventario: ");
        scanf("%d", &indiceInv);
        
        /* Verifica indice valido */
        inv_t *obj = invArray_getByIndex(invArray, indiceInv);
        if (obj == NULL) {
            printf("Indice non valido!\n");
            return;
        }
        
        /* Trova primo slot libero */
        for (int i = 0; i < EQUIP_SLOT; i++) {
            if (equipArray->vettEq[i] == -1) {
                equipArray->vettEq[i] = indiceInv;
                equipArray->nEq++;
                printf("Oggetto aggiunto allo slot %d\n", i);
                return;
            }
        }
    } else if (scelta == 2) {
        /* Rimuovi oggetto */
        if (equipArray->nEq == 0) {
            printf("Equipaggiamento vuoto!\n");
            return;
        }
        
        printf("Inserisci slot da liberare (0-%d): ", EQUIP_SLOT - 1);
        scanf("%d", &slotEq);
        
        if (slotEq < 0 || slotEq >= EQUIP_SLOT) {
            printf("Slot non valido!\n");
            return;
        }
        
        if (equipArray->vettEq[slotEq] == -1) {
            printf("Slot già vuoto!\n");
            return;
        }
        
        equipArray->vettEq[slotEq] = -1;
        equipArray->nEq--;
        printf("Oggetto rimosso dallo slot %d\n", slotEq);
    }
}

/* Ritorna indice oggetto in posizione index dell'equipaggiamento */
int equipArray_getEquipByIndex(equipArray_t equipArray, int index) {
    if (equipArray == NULL) return -1;
    if (index < 0 || index >= EQUIP_SLOT) return -1;
    
    return equipArray->vettEq[index];
}