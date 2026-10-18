#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "inv.h"
#include "pg.h"

#define MAX_S 50
#define NUM_STATS 6
#define NUM_OBJECT 8

#define FILENAME "pg.txt"

typedef struct pg_s pg_t;
typedef struct nodePg_s nodePg_t;
typedef struct tabPg_s tabPg_t;
typedef struct tabEquip_s tabEquip_t;
typedef int stat_t[NUM_STATS];


//struct del personaggio
struct pg_s{
    char code[MAX_S];
    char name[MAX_S];
    char class [MAX_S];
    tabEquip_t *equip;  //puntatore all'equipaggiamento
    stat_t stat; //vettore di interi
}; 

//nodo della lista
struct nodePg_s{
    pg_t data_pg;
    nodePg_t *next;
};

//wrapper della lista dei personaggi
struct tabPg_s {
    nodePg_t *headPg;
    nodePg_t *tailPg;
    int nPg;
};

//equipaggiamento
struct tabEquip_s{
    int inUse;
    p_object vettEq[NUM_OBJECT];
};


//inizializza il wrapper
link_Pg_t create_pgs_list (){
    link_Pg_t wrapPg = malloc (sizeof (tabPg_t));
    wrapPg->headPg = NULL;
    wrapPg->tailPg = NULL;
    wrapPg->nPg = 0;
    return wrapPg;
}

//Nuovo personaggio-> Nuovo nodo, inizializzando testa e coda
nodePg_t* newNode (nodePg_t* head, nodePg_t **tail, pg_t dataPg){
    nodePg_t *t = malloc (sizeof(nodePg_t));
    if (t == NULL){
        return NULL;
    }
    t->data_pg = dataPg;
    t->next = NULL;
    if (head == NULL){
        *tail = t;
        return t;
    }
    else{
        (*tail)->next = t;
        *tail = t;
        return head;
    }
}


//Stampa i dettagli di un personaggio
void print_pg_details (nodePg_t *x){
    p_object object;
    printf ("Dati del personaggio:\n");
    printf ("Codice: %s\n", x->data_pg.code); 
    printf ("Nome: %s\n", x->data_pg.name);
    printf ("Classe: %s\n", x->data_pg.class);
    printf ("Statistiche di base\n");
    for (int i = 0; i < NUM_STATS; i++){
        printf (" %d ", x->data_pg.stat[i]);
    }
    printf ("\n");
    if (x->data_pg.equip != NULL){
        if (x->data_pg.equip->inUse != 0){
            printf ("Dettagli dell'equipaggiamento\n");
            for (int i = 0; i < x->data_pg.equip->inUse; i++){
                object = x->data_pg.equip->vettEq[i];
                printf ("Oggetto %d\n", i+1);
                print_object (object);
            }
        }
    }
}

//carica in una lista i personaggi da file
void load_pgs_from_file (link_Pg_t tabPg, char *filename){
    int j;
    FILE *input;
    if ((input = fopen(filename, "r")) == NULL){
        printf("Errore nell'apertura del file: \"%s\"", filename);
        return;
    }

    pg_t data_pg;
    while (fscanf (input, "%s %s %s", data_pg.code, data_pg.name, data_pg.class) == 3){
        for (j = 0; j < NUM_STATS; j++){
            fscanf (input, "%d", &(data_pg.stat[j]));
        }
        data_pg.equip =  NULL;
        tabPg->headPg = newNode (tabPg->headPg, &(tabPg->tailPg), data_pg);
        print_pg_details (tabPg->tailPg);
        tabPg->nPg += 1;
    }
    
    fclose(input);
    return;
}


//funzione che mi serve per controllare se un codice è nel formato corretto
int controls_code (char *code, nodePg_t *head){
    int flag = 0;
    if (strlen(code) != 6){
        printf ("Formato errato\n");
        return !flag;
    }
    if (code[0] != 'P' || code[1] != 'G'){
        printf ("Formato errato\n");
        return !flag;
    }
    
    for (char *p = &(code[2]); *p != '\0'; p++){
        if (!isdigit(*p)){
            printf ("Formato errato\n");
            return !flag;
        }
    }

    nodePg_t *x;
    for (x = head; x != NULL; x = x->next){
        if (strcmp (code, x->data_pg.code) == 0){
            printf ("Codice già presente nella lista\n");
            return !flag;
        }
    }

    return flag;
}


//Inserire un nuovo personaggio da tastiera
void insert_new_pg (link_Pg_t tabPg){
    pg_t data;
    int i;
    data.equip = NULL;
    printf ("Inserire il codice (univoco)\n");
    scanf ("%s", data.code);
    while (controls_code (data.code, tabPg->headPg)){
        getchar ();
        scanf ("%s", data.code);
    }
    getchar ();
    printf ("Inserire il nome \n");
    scanf ("%s", data.name);
    getchar ();
    printf ("Inserire la classe \n");
    scanf ("%s", data.class);
    getchar ();
    printf ("Inserire le statistiche\n");
    for (i = 0; i < NUM_STATS; i++){
        printf ("Stat %d: ", i+1);
        scanf ("%d", &(data.stat[i]));
        while (data.stat[i] < 0){
            printf ("Riprova\n");
            scanf ("%d", &(data.stat[i]));
        }
    }

    tabPg->headPg = newNode (tabPg->headPg, &(tabPg->tailPg), data);
    print_pg_details (tabPg->tailPg);
    tabPg->nPg += 1;
    return;

}

//funzione di free
void free_node (nodePg_t *x){
    if (x->data_pg.equip != NULL){
        free (x->data_pg.equip);
    }
    free (x);
}

//Fuzione di ricerca ma che ritorna il puntatore al precedente
nodePg_t* search_Pg_code_prev (link_Pg_t tabPg, char *code){
    nodePg_t *x, *prev;
    for (prev = NULL, x = tabPg->headPg; x != NULL;prev = x, x = x->next){
        if (strcmp(x->data_pg.code, code) == 0){
            return prev;
        }
    }
    return NULL;
}

//Lui invece è uguale ma ritorna il nodo corrente (serviva farne due in base alle richieste)
nodePg_t* search_Pg_code (link_Pg_t tabPg, char *code){
    nodePg_t *x, *prev;
    for (prev = NULL, x = tabPg->headPg; x != NULL;prev = x, x = x->next){
        if (strcmp(x->data_pg.code, code) == 0){
            return x;
        }
    }
    return NULL;
}

//procedimento di cancellazione di nodo
void remove_pg (link_Pg_t tabPg, char *code){
    nodePg_t *x_to_remove = NULL, *prev;

    if (tabPg->headPg == NULL){
        printf ("Lista vuota\n");
        return;
    }
    
    prev = search_Pg_code_prev(tabPg, code);

    if (prev == NULL) {
        if (strcmp(tabPg->headPg->data_pg.code, code) == 0) {
            x_to_remove = tabPg->headPg;
            tabPg->headPg = x_to_remove->next; 
            prev = NULL; 
        } else {
            printf("Personaggio non presente\n");
            return;
        }
    } else {
        x_to_remove = prev->next;
        if (x_to_remove == NULL || strcmp(x_to_remove->data_pg.code, code) != 0) {
            printf("Personaggio non presente\n");
            return;
        }
        prev->next = x_to_remove->next; 
    }

    print_pg_details (x_to_remove);
    if (x_to_remove == tabPg->tailPg) {
        tabPg->tailPg = prev; 
    }

    if (tabPg->headPg == NULL) {
        tabPg->tailPg = NULL;
    }

    if (x_to_remove != NULL) {
        free_node(x_to_remove);
        tabPg->nPg--;
        printf("Personaggio %s rimosso con successo.\n", code);
    }
    return;
}


//Aggiunge un oggetto al personaggio
void add_new_object (char *code, link_Pg_t tabPg, char *object_name, inventory tabInv){
    nodePg_t *pg = search_Pg_code (tabPg, code);
    if (pg == NULL){
        printf ("Personaggio non trovato\n");
        return;
    }
    if (pg->data_pg.equip == NULL){
        pg->data_pg.equip = malloc (sizeof (tabEquip_t));
        pg->data_pg.equip->inUse = 0;
    }

    p_object object = search_object_by_name (object_name, tabInv);
    if (object == NULL){
        printf ("Oggetto non trovato\n");
        return;
    }
    if (pg->data_pg.equip->inUse < NUM_OBJECT){
        pg->data_pg.equip->vettEq[pg->data_pg.equip->inUse] = object;
        printf ("Oggetto aggiunto\n");
        print_object (pg->data_pg.equip->vettEq[pg->data_pg.equip->inUse]);
        pg->data_pg.equip->inUse++;
        return;
    }
    else{
        printf ("Non puoi aggiungere altri oggetti a questo personaggio\n");
        return;
    }
}


//toglie un oggetto dal personaggio
void remove_object (char *code, link_Pg_t tabPg, char *object_name){
    char *equip_name;
    nodePg_t *pg = search_Pg_code (tabPg, code);
    if (pg == NULL){
        printf ("Personaggio non trovato\n");
        return;
    }
    int flag = 1, i;
    for (i = 0; i < pg->data_pg.equip->inUse && flag; i++){
        equip_name = extract_object_name (pg->data_pg.equip->vettEq[i]);
        if (strcmp (object_name, equip_name) == 0){
            flag = 0;
            break;
        }
    }
    if (flag){
        printf ("Oggetto non trovato dentro l'equipaggiamento\n");
        return;
    }

    printf ("Oggetto rimosso\n");
    print_object (pg->data_pg.equip->vettEq[i]);


    for (int j = i; j < pg->data_pg.equip->inUse - 1; j++){
        pg->data_pg.equip->vettEq[j] = pg->data_pg.equip->vettEq[j+1];
    }
    pg->data_pg.equip->vettEq[pg->data_pg.equip->inUse-1] = NULL;
    pg->data_pg.equip->inUse--;

    return;
}

//pulisce cio che c'è dentro i nodi
void free_list_pg(link_Pg_t tabPg){
    nodePg_t *x, *t;
    for (x = tabPg->headPg; x != NULL;){
        if (x->data_pg.equip != NULL){
            free (x->data_pg.equip);
        }
        t = x;
        x = x->next;
        free (t);
    }
    free (tabPg);
    return;
}

//vede le statistiche considerando quelle base e l'equipaggiamento
void calculate_statistic (link_Pg_t tabPg, char *code){
    nodePg_t *x = search_Pg_code (tabPg, code);
    if (x == NULL){
        printf ("personaggio non presente\n");
        return;
    }

    int vet[NUM_STATS] = {0}, mod_stat;
    for (int i = 0; i < NUM_STATS; i++){
        vet[i]+= x->data_pg.stat[i];
    }
    if (x->data_pg.equip != NULL){
        for (int j = 0; j < x->data_pg.equip->inUse; j++){
            for (int i = 0; i < NUM_STATS; i++){
                mod_stat = extract_stat (x->data_pg.equip->vettEq[j], i);
                vet[i] += mod_stat;
            }
        }

        printf ("statistiche con tutto l'equipaggiamento\n");
        for (int i = 0; i < NUM_STATS; i++){
            if (vet[i] < 0){
                printf (" %d ", 0);
            }
            else{
                printf (" %d ", vet[i]);
            }
        }
    } else {
        printf ("Manca l'equipaggiamento, quindi ecco le statisctiche base\n");
        for (int i = 0; i < NUM_STATS; i++){
            printf (" %d ", vet[i]);
        }
        printf ("\n");
    }
    printf ("\n");
    return;
}