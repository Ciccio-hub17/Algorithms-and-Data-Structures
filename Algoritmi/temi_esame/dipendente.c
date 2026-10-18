#include<stdio.h>
#include <stdlib.h>
#include "dipendente.h"

dipendente_t ricerca_dipendente (dipendente_t* dip, int N, int matricola){
    int i;

    for (i = 0; i < N; i++){
        if (dip->matricola == matricola){
            return dip[i];
        }
    }
}