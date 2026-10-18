#include "pgList.h"

/* Nodo della lista */
typedef struct pgNode_s {
    pg_t pg;
    struct pgNode_s *next;
} pgNode_t;

/* Struttura interna ADT */
struct pgList_s {
    pgNode_t *head;
    int nPg;
};

/* Creazione ADT */
pgList_t pgList_init() {
    pgList_t pgList = (pgList_t)malloc(sizeof(struct pgList_s));
    if (pgList == NULL) return NULL;
    
    pgList->head = NULL;
    pgList->nPg = 0;
    return pgList;
}

/* Distruzione ADT */
void pgList_free(pgList_t pgList) {
    if (pgList == NULL) return;
    
    pgNode_t *curr = pgList->head;
    pgNode_t *temp;
    
    while (curr != NULL) {
        temp = curr;
        curr = curr->next;
        pg_clean(&temp->pg);  /* pulisce equipaggiamento */
        free(temp);
    }
    
    free(pgList);
}

/* Lettura da file */
void pgList_read(FILE *fp, pgList_t pgList) {
    if (pgList == NULL || fp == NULL) return;
    
    pg_t pg_temp;
    
    /* Leggi personaggi fino a EOF */
    while (pg_read(fp, &pg_temp)) {
        pgList_insert(pgList, pg_temp);
    }
}

/* Stampa lista personaggi */
void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray) {
    if (pgList == NULL || fp == NULL) return;
    
    fprintf(fp, "\n=== LISTA PERSONAGGI (%d personaggi) ===\n", pgList->nPg);
    
    if (pgList->nPg == 0) {
        fprintf(fp, "(lista vuota)\n");
        return;
    }
    
    pgNode_t *curr = pgList->head;
    int count = 1;
    
    while (curr != NULL) {
        fprintf(fp, "\n--- Personaggio %d ---\n", count++);
        pg_print(fp, &curr->pg, invArray);
        curr = curr->next;
    }
}

/* Inserimento in testa */
void pgList_insert(pgList_t pgList, pg_t pg) {
    if (pgList == NULL) return;
    
    pgNode_t *newNode = (pgNode_t *)malloc(sizeof(pgNode_t));
    if (newNode == NULL) return;
    
    newNode->pg = pg;
    newNode->next = pgList->head;
    pgList->head = newNode;
    pgList->nPg++;
}

/* Rimozione per codice */
void pgList_remove(pgList_t pgList, char *cod) {
    if (pgList == NULL || cod == NULL) return;
    if (pgList->head == NULL) return;
    
    pgNode_t *curr = pgList->head;
    pgNode_t *prev = NULL;
    
    while (curr != NULL) {
        if (strcmp(curr->pg.cod, cod) == 0) {
            /* Trovato, rimuovi */
            if (prev == NULL) {
                /* Primo nodo */
                pgList->head = curr->next;
            } else {
                prev->next = curr->next;
            }
            
            pg_clean(&curr->pg);
            free(curr);
            pgList->nPg--;
            printf("Personaggio %s rimosso con successo.\n", cod);
            return;
        }
        
        prev = curr;
        curr = curr->next;
    }
    
    printf("Personaggio con codice %s non trovato.\n", cod);
}

/* Ricerca per codice */
pg_t *pgList_searchByCode(pgList_t pgList, char *cod) {
    if (pgList == NULL || cod == NULL) return NULL;
    
    pgNode_t *curr = pgList->head;
    
    while (curr != NULL) {
        if (strcmp(curr->pg.cod, cod) == 0) {
            return &curr->pg;
        }
        curr = curr->next;
    }
    
    return NULL;
}