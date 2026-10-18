#include<stdio.h>
#include<math.h>

long prod (int *x, int lx, int rx, int *y, int ly, int ry, int n);

int main (){
    int x[] = {1, 3, 5, 6};
    int y[] = {2, 4, 1, 0};
    long result = prod (x, 0, 3, y, 0, 3, 4);
    printf ("%d", result);
    return 0;
}

long prod (int *x, int lx, int rx, int *y, int ly, int ry, int n){
    long t1, t2, t3;
    if (n == 1){
        return x[lx]*y[ly];
    }
    t1 = prod (x, lx, (lx+rx)/2, y, ly, (ly+ry)/2, n/2);
    t2 = prod (x, lx, (lx+rx)/2, y, (ly+ry)/2+1, ry, n/2) + prod (x, (lx+rx)/2+1, rx, y, ly, (ly+ry)/2, n/2);
    t3 = prod (x, (lx+rx)/2+1, rx, y, (ly+ry)/2+1, ry, n/2);

    return pow(10,n)*t1 + pow(10,n/2)*t2 + t3;
}