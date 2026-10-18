#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void shellsort (int A [], int n){

    int i = 0, l = 0, r = n-1, h = 1, x = 0, j = 0;

    while (h <= n/3){
        h = 3*h + 1;
    }

    while (h >= 1){
        for (i = l; i <= r; i++){
            x = A[i];


            j = i-h;
            while (j >= l && A[j] > x){
                A[j+h] = A[j];
                j = j-h;
            }
            A[j+h] = x;
        }
        h = h/3;
    }

    for (i = 0; i <= r; i++)
    {
        printf (" %d ", A[i]);
    }

}

int main ()
{
    int A [] = {10,9,8,7,6,5,4,3,2,1};
    shellsort(A, 10);
    return 0;
}