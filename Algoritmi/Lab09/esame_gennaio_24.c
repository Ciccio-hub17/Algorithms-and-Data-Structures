#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "ST.h"
#include "grafo.h"
//Si assuma il grafo caricato con matrice di adiacenza (non pesata) e che il peso dei singoli vertici sia memorizzato in un vettore 
//di interi int *pesi allocato dinamicamente (dato che conosciamo il numero di vertici)
//Ovviamente nel grafo dovrà essere presente la tabella di simboli (dove la tabella è un vettore di stringhe) perche altrimenti non è possibile fare
//Corrispondenza biunivoca tra nome e indice di ogni singolo vertice

int checkString (char *stringa, Graph G){
    char *p = &stringa[0];
    int prev = -1, new = -1;
    while (*p != '\0'){
        prev = new;
        new = search_table (p);
        if (new == -1){
            return 0;
        }
        if (p != &stringa[0] && G->madj[prev][new] != 1){
            return 0;
        }
        p += strlen (index_to_label (new));
    }

    printf ("La proposta è effettivamente un cammino\n");
    return 1;
}

int check (char *stringa, int index, int *used, int M){
    char *label = index_to_label (index);
    if (stringa == NULL || strchr ("aeiou", stringa[strlen(stringa)-1]) == strchr ("aeiou", label[strlen(label)-1])){
        return 0;
    }

    if (used[search_label_used(index_to_label(index))] > M){
        return 0;
    }
    return 1;
}

void bestPath (char* p, Graph G, int M, int *used, int *max, int curr_val, char* stringa_sol, int curr_len, char* best_str, int v){
    int j;
    if (curr_len > *max){
        *max = curr_len;
        strcpy (best_str, stringa_sol);
        return;
    }

    for (j = 0; j < G->V; j++){
        if (G->madj[v][j] == 1){
            if (check (p, j, used, M)){

                char *prov_str = index_to_label (j);
                strcat (p, prov_str);
                curr_len += strlen (prov_str);
                curr_val += G->pesi[j];
                used[search_label_used (index_to_label(j))]++;

                if (p == NULL){
                    bestPath (p = stringa_sol[0], G, M, used, max, curr_val, stringa_sol, curr_len, best_str, j);
                }
                else{
                    bestPath (p + strlen (prov_str), G, M, used, max, curr_val, stringa_sol, curr_len, best_str, j);
                }

                if (stringa_sol[0] != '\0'){
                    p -= strlen (prov_str); *p = '\0';
                }
                else{
                    p = NULL;
                }
                curr_len -= strlen (prov_str);
                curr_val -= G->pesi[j];
                used[search_label_used (index_to_label(j))]--;
            }
        }
    }


    return;
}

//La funzione wrapper allochera (e liberera la memoria successivamente) le risorse necessarie e impostera il puntatore p a null, inoltre lancera la funzione su ogni vertice
//Stampera anche la soluzione trovata
void wrapper (Graph G, int M){
    int max = 0, *used = calloc (G->V, sizeof (int));
    char *p = NULL, *stringa = malloc (20*G->V*sizeof (char)), *best_stringa = malloc (20*G->V*sizeof (char));

    for (int i = 0; i < G->V; i++){
        bestPath (p, G, M, used, &max, 0, stringa, 0, best_stringa, i);
    }

    printf ("%s; peso: %d", best_stringa, max);

    free (used); free (stringa), free (best_stringa);

    return;
}


/*PER LEGGERE IL GRAFO DA FILE*/
/*Si usera una graphLoad leggermente modificata in quanto, sulla prima riga
oltre al numero di vertici è presente anche il numero di archi (quindi anche nella graph init si può anche usare direttamente quello)
e, oltre a leggere i vertici, si devono anche leggere gli archi*/

int main(int argc, char* argv[]){
    
    printf("\n");
    return 0;
}