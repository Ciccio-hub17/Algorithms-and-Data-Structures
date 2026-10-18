#include<stdio.h>
#include "grafo.h"

#define MAX_S 30

#define stampa_ordine_alfabetico 0
#define sotto_grafo 1
#define lista_di_adiacenza 2
#define fine 3

void menu (Graph G){
    int scelta, flag = 1, flag_lista = 0, mat_list = 0;
    char label1[MAX_S], label2[MAX_S], label3[MAX_S];
    while (flag){
        printf ("Premere 0 per stampare i vertici e gli archi per ogni vertice in ordine alfabetico\nPremere 1 per vedere se, dati 3 vertici, essi formano un sottografo completo\nPremere 2 per generare la lista di adiacenza\nPremere 3 per terminare\n");
        scanf ("%d", &scelta);
        getchar ();
        switch (scelta){
            case stampa_ordine_alfabetico:
                print_order (G);
                break;
            case sotto_grafo:
                printf ("Dammi i nomi dei 3 vertici, separati da spazi\n");
                scanf ("%s %s %s", label1, label2, label3);
                getchar ();
                printf ("Scegli se usare la matrice o la lista (0 o 1)\n");
                scanf ("%d", &mat_list);
                if (mat_list == 0){
                    search_sotto_grafo_mat (G, label1, label2, label3);
                }
                else{
                    search_sotto_grafo_lista (G, label1, label2, label3);
                }

                break;
            case lista_di_adiacenza:
                if (!flag_lista){
                    flag_lista = 1;
                    genera_lista (G);
                }
                else{
                    printf ("Lista già generata\n");
                }
                break;
            case fine:
                flag = 0;
                break;
            default:
                printf ("Opzione errata\n");
                break;
        }
    }
}

int main(int argc, char* argv[]){

    if (argc != 2){
        printf ("Il numero di argomenti non corrisponde, uscita del programma\n");
        return -1;
    }

    Graph G = read_file (argv[1]);

    menu (G);

    GFree (G);
    
    printf("\n");
    return 0;
}