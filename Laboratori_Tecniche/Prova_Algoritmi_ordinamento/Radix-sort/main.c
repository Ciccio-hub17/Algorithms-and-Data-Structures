#include <stdio.h>

int getMax (int A[], int n);


void radixsort (int A[], int n, int B[], int C[], int D[]);

void countingsort (int A[], int B[], int C[], int D[], int n, int step);

int main(void)
{
    int A[8] = {170, 4, 2375, 90, 802, 24, 2, 66}, N = 8, B[8], C[10], D[8];

    radixsort(A, N, B, C, D);

    for (int i = 0; i < N; i++)
    {
        printf (" %d ", A[i]);
    }

    return 0;
}

void radixsort (int A[], int n, int B[], int C[], int D[])
{
    int max = 0, i = 0, d = 1;
    max = getMax(A, n);

    while (max/10 > 0)
    {
        d++;
        max = max / 10;
    }
    for (i = 0; i < d; i++)
    {
        countingsort(A, B, C, D, n, i);
    }
}

int getMax (int A[], int n)
{
    int max = A[0];
    for (int i = 1; i < n; i++)
    {
        if (A[i] >= max)
        {
            max = A[i];
        }
    }
    return max;
}

void countingsort (int A[], int B[], int C[], int D[], int n, int step)
{
    int weight = 1, i = 0, l = 0, r = n-1, k = 10;

    for (i = 0; i < step; i++)
    {
        weight = weight * 10;
    }

    for (i = l; i < k; i++)
    {
        C[i] = 0;
    }

    for (i = l; i <= r; i++)
    {
        D[i] = (A[i] / weight) % 10;
    }

    for (i = l; i <= r; i++)
    {
        C[D[i]]++;
    }

    for (i = l+1; i <k; i++)
    {
        C[i] = C[i] + C[i-1];
    }

    for (i = r; i >= l; i--)
    {
        B[C[D[i]]-1] = A[i];
        C[D[i]]--;
    }

    for (i = l; i <= r; i++)
    {
        A[i] = B[i];
    }

}