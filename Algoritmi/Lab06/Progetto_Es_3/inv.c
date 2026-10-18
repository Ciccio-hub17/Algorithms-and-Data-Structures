#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "inv.h"

#define MAX_S 50
#define NUM_STATS 6

typedef struct inv_s inv_t;
typedef struct tblInv_s tblInv_t;
typedef int mod_stat_t[NUM_STATS];

//oggetto nell'inventario
struct inv_s{
    char name[MAX_S];
    char type[MAX_S];
    mod_stat_t stat;
};

//wrapper per l'inventario
struct tblInv_s {
    inv_t *vettInv;
    int nInv;
    int maxInv;
};

//Inizializzo l'inventario
inventory create_inventory (){
    inventory inv = (inventory) malloc (sizeof (tblInv_t));
    inv->vettInv = NULL;
    inv->nInv = 0;
    inv->maxInv = 0;
    return inv;
}

//legge il file
void inv_read_file (inventory tabInv, char* filename){
    FILE *input;
    if ((input = fopen(filename, "r")) == NULL){
        printf("Errore nell'apertura del file: \"%s\"", filename);
        return;
    }

    int n_object, i, j;

    fscanf (input, "%d", &n_object);

    tabInv->nInv = n_object;

    tabInv->vettInv = (inv_t*)malloc (n_object*sizeof (inv_t));

    inv_t *vet_temp = tabInv->vettInv;
    for (i = 0; i < n_object; i++){
        fscanf (input, "%s %s", vet_temp[i].name, vet_temp[i].type);
        for (j = 0; j < NUM_STATS; j++){
            fscanf (input, "%d", &(vet_temp[i].stat[j]));
        }
        print_object (&vet_temp[i]);
    }
    
    fclose(input);
}

//cerca un oggetto dato il nome
p_object search_object_by_name (char *name_to_search, inventory tabInv){
    int i, n_object = tabInv->nInv;
    inv_t *vet_temp = tabInv->vettInv;

    for (i = 0; i < n_object; i++){
        if (!strcmp(name_to_search, vet_temp[i].name)){
            return &(vet_temp[i]);
        }
    }
    return NULL;
}

//visualizza i dettagli
void print_object (p_object object){

    printf ("Nome: %s\n", object->name);
    printf ("Tipo: %s\n", object->type);
    printf ("Modificatori di statistiche di un player: \n");
    for (int i = 0; i < NUM_STATS; i++){
        printf (" %d ", object->stat[i]);
    }
    printf ("\n");
    return;
}

//libera il wrapper
void free_Inventory (inventory tabInv){
    if (tabInv->vettInv != NULL){
        free (tabInv->vettInv);
    }
    free (tabInv);
    return;
}

char *extract_object_name (p_object p){
    return p->name;
}

int extract_stat (p_object p, int index){
    return p->stat[index];
}