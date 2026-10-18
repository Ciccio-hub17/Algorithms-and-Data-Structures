#ifndef DATE_H
#define DATE_H

typedef struct {
    int g;
    int m;
    int a;
} Date;

// 0 se uguali, <0 se d1 < d2, >0 se d1 > d2
int DATEcmp(Date d1, Date d2);

#endif