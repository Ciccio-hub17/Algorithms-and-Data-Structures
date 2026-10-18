#ifndef INFO_TEMPO_H
#define INFO_TEMPO_H

typedef struct data_s {
    int anno;
    int mese;
    int giorno;
}data_t;

typedef struct ora_s {
    int ora;
    int minuto;
}ora_t;

int cmpData (data_t data1, data_t data2);   //Fa il confronto tra due date
data_t split_date (char data[]);    //dalla stringa di una data crea la struct contenente dati interi
void swapData (data_t* data1, data_t* data2);   //swappa due date
int valid_date (data_t data);   //controlla se una data è sensata 

#endif