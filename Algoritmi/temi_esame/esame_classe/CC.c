#include "CC.h"
#include "Graph.h"
#include "ST.h"
#include "UF.h"

struct comp {
    int N;
    int **mat;
    //La riga è la componente connessa e le colonne sono i vertici di appartenenza
};

CC CCgen (Graph g){
    CC componenti;
    //CCinit;

    dfsCC (g, componenti);

    return;
}