#include "Date.h"

// 0 se uguali, <0 se d1 < d2, >0 se d1 > d2
int DATEcmp(Date d1, Date d2) {
    if (d1.a != d2.a) return d1.a - d2.a;
    if (d1.m != d2.m) return d1.m - d2.m;
    return d1.g - d2.g;
}