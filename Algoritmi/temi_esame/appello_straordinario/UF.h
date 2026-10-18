#ifndef UF_H
#define UF_H

typedef int *UF;

void  UFinit(int N);
int   UFfind(int p, int q);
void  UFunion(int p, int q);
void  UFfree(void);
void UFbacktrack(void);

#endif

