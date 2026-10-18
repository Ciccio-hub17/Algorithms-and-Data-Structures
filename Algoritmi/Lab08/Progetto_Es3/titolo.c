#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "titolo.h"
#include "quotazione.h"
#include "info_tempo.h"

#define MAX_S 21
#define DIM_DATA 11
#define DIM_ORA 6

typedef struct nodo* link_nodo;

typedef struct titolo_s {
    char nome [MAX_S];
    BST quotazioni_titolo;  //tanti BST quanti sono i titoli, tutti i BST ordinati per data
}titolo_t;

typedef struct nodo {
    titolo_t val;
    link_nodo next;
}node_t;

struct wrapperLista_s{
    link_nodo head;
    int num_nodi;
};

Lista_titoli titoli_init (){
    Lista_titoli p = malloc (sizeof (struct wrapperLista_s));
    if (p == NULL){
        return NULL;
    }
    p->head = NULL;
    p->num_nodi = 0;
    return p;
}

void freeTitoli (Lista_titoli titoli){
    link_nodo x;
    for (x = titoli->head; x != NULL; x = x->next){
        BSTFree (x->val.quotazioni_titolo);
        free (x);
    }
    free (titoli);
}

link_nodo newNode (char nome[], link_nodo next, link_nodo prev, BST bst_titolo){
    link_nodo p = malloc (sizeof (node_t));
    if (p == NULL){
        return NULL;
    }
    strcpy (p->val.nome, nome);
    p->val.quotazioni_titolo = bst_titolo;
    p->next = next;
    if (prev != NULL){
        prev->next = p;
    }
    return p;
}

void titoli_print(Lista_titoli titoli){
    link_nodo x;
    for (x = titoli->head; x != NULL; x = x->next){
        printf ("Informazioni del titolo azionario con codice %s\n", x->val.nome);
        BSTPrint (x->val.quotazioni_titolo);
    }
}

void SearchTitolo (Lista_titoli titoli, char codice[]){
    link_nodo x;
    if (titoli->head == NULL){
        printf ("Lista vuota\n");
        return;
    }
    for (x = titoli->head; x != NULL; x = x->next){
        if (strcmp (codice, x->val.nome) == 0){
            printf ("Titolo trovato, ecco le sue informazioni\n");
            BSTPrint (x->val.quotazioni_titolo);
            return;
        }
    }
    printf ("Titolo non trovato\n");
} 

void SearchTitoloData (Lista_titoli titoli, data_t data, char nome[]){
    link_nodo x;
    if (titoli->head == NULL){
        printf ("Lista vuota\n");
        return;
    }
    for (x = titoli->head; x != NULL; x = x->next){
        if (strcmp (nome, x->val.nome) == 0){
            printf ("Titolo trovato\n");
            SearchData (x->val.quotazioni_titolo, data);
            return;
        }
    }
    printf ("Titolo non trovato\n");
} 

void SearchTitoloData1Data2 (Lista_titoli titoli, data_t data1, data_t data2, char nome[]){
    link_nodo x;
    for (x = titoli->head; x != NULL; x = x->next){
        if (strcmp (nome, x->val.nome) == 0){
            printf ("Titolo trovato\n");
            SearchQuot_max_min_date (x->val.quotazioni_titolo, data1, data2);
            return;
        }
    }
    printf ("Titolo non trovato\n");
} 

void SearchTitoloMaxMin (Lista_titoli titoli, char nome[]){
    link_nodo x;
    if (titoli->head == NULL){
        printf ("Lista vuota\n");
        return;
    }
    for (x = titoli->head; x != NULL; x = x->next){
        if (strcmp (nome, x->val.nome) == 0){
            printf ("Titolo trovato\n");
            SearchQuot_max_min_date (x->val.quotazioni_titolo, searchMin(x->val.quotazioni_titolo), searchMax (x->val.quotazioni_titolo));
            return;
        }
    }
    printf ("Titolo non trovato\n");
} 

void bilanciamentoTitolo (Lista_titoli titoli, char codice[], int soglia){
    link_nodo x;
    if (titoli->head == NULL){
        printf ("Lista vuota\n");
        return;
    }
    for (x = titoli->head; x != NULL; x = x->next){
        if (strcmp (codice, x->val.nome) == 0){
            int max = prof_max (x->val.quotazioni_titolo);
            int min = prof_min (x->val.quotazioni_titolo);
            int rapporto = max/min;
            printf ("Rapporto: %d\n", rapporto);
            if (rapporto > soglia){
                BSTbalance (x->val.quotazioni_titolo);
                printf ("Albero bilanciato\n");
                BSTPrint (x->val.quotazioni_titolo);
            }
            else{
                printf ("Bilanciamento non necessario\n");
            }
            return;
        }
    }
    printf ("Titolo non trovato\n");
} 

void leggi_file (Lista_titoli titoli, char filename[]){
    FILE *input;
    if ((input = fopen(filename, "r")) == NULL){
        printf("Errore nell'apertura del file: \"%s\"", filename);
        exit(-1);
    }
    
    int num_titoli, i, j, num_transazioni, n_tit_scamb, n_tit_scamb_tot;
    char cod_titolo[MAX_S], old_data[DIM_DATA], new_data[DIM_DATA];
    float valore, tot_quot, quotazione_giornaliera;

    link_nodo x, p;
    quotazione_t quot_struct;   //Item del BST (é un quasi ADT)
    data_t data_struct;

    fscanf (input, "%d", &num_titoli);
    titoli->num_nodi = num_titoli;  //Aggorno il numero di nodi

    for (i = 0; i < num_titoli; i++){
        BST bst = BSTinit();    //Leggo un nuovo titolo, creo un nuovo BST

        fscanf (input, "%s %d", cod_titolo, &num_transazioni);
        if (titoli->head == NULL || strcmp (cod_titolo, titoli->head->val.nome) < 0){
            titoli->head = newNode (cod_titolo, titoli->head, NULL, bst);
        }
        else{
            for (x = titoli->head->next, p = titoli->head; x != NULL && strcmp (cod_titolo, x->val.nome) > 0; p = x, x = x->next);    //Cerco dove inserire il nome
            link_nodo nuovo = newNode (cod_titolo, x, p, bst); //creo il nuovo nodo in lista
        }
        if (num_transazioni != 0){
            fscanf (input, "%s %*s %f %d", old_data, &tot_quot, &n_tit_scamb_tot);
            for (j = 1; j < num_transazioni; j++){
                fscanf (input, "%s", new_data);
                if (strcmp(new_data, old_data) != 0){
                    //Crea il nodo nel bst appena hai trovato una data nuova
                    quotazione_giornaliera = tot_quot / (float) n_tit_scamb_tot;
                    data_struct = split_date (old_data);
                    quot_struct.quotazione = quotazione_giornaliera;
                    quot_struct.data = data_struct;
                    InsertInBST (bst, quot_struct);

                    //leggi i dati nuovi
                    fscanf (input, "%*s %f %d", &tot_quot, &n_tit_scamb_tot);
                    //salva la nuova data come vecchia
                    strcpy (old_data, new_data);
                }
                else{
                    fscanf (input, "%*s %f %d", &valore, &n_tit_scamb);
                    tot_quot += valore*(float)n_tit_scamb;
                    n_tit_scamb_tot += n_tit_scamb;
                }   
            }
            quotazione_giornaliera = tot_quot / (float)n_tit_scamb_tot;
            data_struct = split_date(old_data);
            quot_struct.quotazione = quotazione_giornaliera;
            quot_struct.data = data_struct;
            InsertInBST(bst, quot_struct);
        }
    }

    fclose(input);
    printf ("Caricamento avvenuto con successo, si procede a visualizzare tutti i titoli caricati\n\n");
    titoli_print (titoli);
}









