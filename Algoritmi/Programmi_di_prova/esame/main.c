#include <stdio.h>
#include "Graph.h"
#include "Item.h"

int main() {
    printf("--- Inizio Test Albero Genealogico ---\n");

    // Inizializzazione Grafo (Max 10 persone)
    Graph G = GRAPHinit(10);
    Date nullDate = {0,0,0}; // Data morte per i vivi

    // 2. Creazione Persone
    // Mario (Nonno)
    Date d1 = {1, 1, 1940};
    Item nonno = ITEMnew("Rossi Mario", d1, nullDate);

    // Giuseppe (Padre)
    Date d2 = {15, 6, 1970};
    Item padre = ITEMnew("Rossi Giuseppe", d2, nullDate);

    // Luca (Figlio)
    Date d3 = {20, 9, 2000};
    Item figlio = ITEMnew("Rossi Luca", d3, nullDate);

    // Anna (Estranea)
    Date d4 = {5, 5, 1980};
    Item estraneo = ITEMnew("Bianchi Anna", d4, nullDate);

    // Inserimento Nodi nel Grafo (e nella ST)
    GRAPHinsertNode(G, nonno); // ID 0
    GRAPHinsertNode(G, padre); // ID 1
    GRAPHinsertNode(G, figlio); // ID 2
    GRAPHinsertNode(G, estraneo); // ID 3

    // Inserimento Archi (Relazioni Genitore -> Figlio)
    // Mario -> Giuseppe
    GRAPHinsertEdge(G, 0, 1);
    // Giuseppe -> Luca
    GRAPHinsertEdge(G, 1, 2);

    printf("Grafo costruito: Mario -> Giuseppe -> Luca\n\n");

    //(Problema di verifica)
    // Mario e Luca sono parenti entro grado 2? (Dovrebbe essere SI)
    int k = 2;
    printf("Mario e Luca parenti (k=%d)? ", k);
    if (relationshipK(G, "Rossi Mario", d1, "Rossi Luca", d3, k))
        printf("Si\n");
    else
        printf("No\n");

    // Test B: Mario e Luca sono parenti entro grado 1? (Dovrebbe essere NO, dist=2)
    k = 1;
    printf("Mario e Luca parenti (k=%d)? ", k);
    if (relationshipK(G, "Rossi Mario", d1, "Rossi Luca", d3, k))
        printf("Si\n");
    else
        printf("No\n");

    // Mario e Anna (Estranea)
    printf("Mario e Anna parenti? ");
    if (relationshipK(G, "Rossi Mario", d1, "Bianchi Anna", d4, 5))
        printf("Si\n");
    else
        printf("No\n");

    // (Problema di ottimizzazione)
    
    largestLineageK(G, 2);

    // 7. Pulizia memoria
    GRAPHfree(G); // Questo libera anche la ST e gli Item al suo interno
    
    return 0;
}