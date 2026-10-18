#include <stdio.h>

void countingsort (int A[], int B[], int C[], int N, int k);

int main(void)
{
    int N = 8, k = 6, A[8] = {2, 5, 3, 0, 2, 3, 0, 3}, B[8], C[k];
    countingsort(A, B, C, N, k);
    return 0;
}

void countingsort (int A[], int B[], int C[], int N, int k)
{
    int i = 0, l = 0, r = N-1;
    for (i = l; i < k; i++)
    {
        C[i] = 0;
    }
    for (i = l; i <= r; i++)
    {
        C[A[i]]++;
    }
    for (i = l+1; i < k; i++)
    {
        C[i] = C[i] + C[i-1];
    }
    for (i = r; i >=l; i--)
    {
        B[C[A[i]]-1] = A[i];
        C[A[i]]--;
    }
    for (i = l; i <= r; i++)
    {
        A[i] = B[i];
    }
    for (i = l; i <= r; i++)
    {
        printf (" %d ", A[i]);
    }
}