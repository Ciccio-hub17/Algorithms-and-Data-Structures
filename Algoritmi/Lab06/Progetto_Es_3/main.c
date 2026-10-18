#include<stdio.h>
#include "pg.h"
#include "inv.h"

#define MAX_S 50

typedef enum {carica_lista_personaggi, carica_elenco_oggetti, nuovo_personaggio, elimina_personaggio, aggiungi_oggetto_eq, rimuovi_oggetto_eq, calcola_statistiche, fine}menu_enum;

void menu (){
    inventory tabInv = create_inventory ();
    link_Pg_t tabPg = create_pgs_list ();

    char filenameInv[MAX_S], filenamePg[MAX_S], code[MAX_S], name[MAX_S];

    int flag = 1, scelta;
    while (flag){
        printf ("Menu\n");
        printf ("0: Caricare i personaggi del file in una lista\n");
        printf ("1: Caricare l'elenco degli oggetti in un vettore\n");
        printf ("2: Aggiungere un nuovo personaggio\n");
        printf ("3: Eliminare un personaggio\n");
        printf ("4: Aggiungere oggetto all'equipaggiamento di un personaggio\n");
        printf ("5: Togliere oggetto dall'equipaggiamento di un personaggio\n");
        printf ("6: Calcola le statistiche di un personaggio considerando le statistiche base e quelle del suo equipaggiamento\n");
        printf ("7: Termina\n");
        scanf ("%d", &scelta);
        switch (scelta){
            case carica_lista_personaggi:
                printf ("Dammi il nome del file dei personaggi\n");
                scanf ("%s", filenamePg);
                getchar ();
                load_pgs_from_file (tabPg, filenamePg);
                break;
            case carica_elenco_oggetti:
                printf ("Dammi il nome del file dell'inventario\n");
                scanf ("%s", filenameInv);
                getchar ();
                inv_read_file (tabInv, filenameInv);
                break;
            case nuovo_personaggio:
                insert_new_pg (tabPg);
                break;
            case elimina_personaggio:
                printf ("Dammi il codice da cercare\n");
                scanf ("%s", code);
                remove_pg (tabPg, code);
                break;
            case aggiungi_oggetto_eq:
                printf ("Dammi il codice del personaggio a cui vuoi aggiungere l'oggetto\n");
                scanf ("%s", code);
                printf ("Dammi il nome dell'oggetto\n");
                scanf ("%s", name);
                add_new_object (code, tabPg, name, tabInv);
                break;
            case rimuovi_oggetto_eq:
                printf ("Dammi il codice del personaggio a cui vuoi togliere  l'oggetto\n");
                scanf ("%s", code);
                printf ("Dammi il nome dell'oggetto\n");
                scanf ("%s", name);
                remove_object (code, tabPg, name);
                break;
            case calcola_statistiche:
                printf ("Dammi il codice del personaggio di cui vuoi calcolare le statistiche\n");
                scanf ("%s", code);
                calculate_statistic (tabPg, code);
                break;
            case fine:
                flag = 0;
                break;
            default:
                printf ("Scelta errata\n");
                break;
        }

    }

    free_Inventory (tabInv);
    free_list_pg (tabPg);
    return;
}

int main(int argc, char* argv[]){
    
    menu();
    
    printf("\n");
    return 0;
}