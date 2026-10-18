#include "info_tempo.h"
#include <stdlib.h>

int cmpData (data_t data1, data_t data2){
    if (data1.anno != data2.anno){
        if (data1.anno < data2.anno){
            return -1;
        }
        return 1;
    }
    else{
        if (data1.mese != data2.mese){
            if (data1.mese < data2.mese){
                return -1;
            }
            return 1;
        }
        else{
            if (data1.giorno < data2.giorno){
                return -1;
            }
            else if (data1.giorno > data2.giorno){
                return 1;
            }
            return 0;
        }
    }
}

data_t split_date (char data[]){
    data_t data_struct;
    int i, k = 0;
    char tmp[5];
    for (i = 0; i < 5; i++){
        tmp[i] = data[i];
    }
    tmp[4] = '\0';
    data_struct.anno = atoi (tmp);
    for (i = 5; i < 7; i++){
        tmp[k++] = data[i];
    }
    tmp[k++] = '\0';
    data_struct.mese = atoi(tmp);
    k = 0;
    for (i = 8; i < 10; i++){
        tmp[k++] = data[i];
    }
    tmp[k++] = '\0';
    data_struct.giorno = atoi(tmp);

    return data_struct;
}

void swapData (data_t* data1, data_t* data2){
    data_t tmp = *data1;
    *data1 = *data2;
    *data2 = tmp;
}

int valid_date (data_t data){
    if (data.anno < 1 || data.mese < 1 || data.giorno < 1){
        return 0;
    }
    if (data.mese > 12){
        return 0;
    }
    if (data.mese == 2 && data.giorno > 28){
        return 0;
    }
    if ((data.mese == 11 || data.mese == 4 || data.mese == 6 || data.mese == 9) && data.giorno > 30){
        return 0;
    }
    if (data.giorno > 31){
        return 0;
    }
    return 1;
}