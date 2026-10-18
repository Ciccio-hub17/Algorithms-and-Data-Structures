#include <stdio.h>

void bottom_up_merge_sort (int A[], int B[], int n);

void merge (int A[], int B[], int l, int m, int q, int r);

int main(void)
{
    int A[8] = {12, 6, 4, 5, 9, 2, 3, 1}, N = 8, B[8];

    bottom_up_merge_sort(A, B, N);

    for (int i = 0; i < N; i++)
    {
        printf (" %d ", A[i]);
    }
    return 0;
}

void bottom_up_merge_sort (int A[], int B[], int n)
{
    int i = 0, l = 0, r = n-1, m = 1, q = 0;
    for (m = 1; m <= r-l; m = m + m)
    {
        for (i = l; i <= r - m; i = i + m + m)
        {
            q = i + m - 1;
            merge(A, B, i, m, q, r);
        }
    }
}

void merge (int A[], int B[], int l, int m, int q, int r)
{
    int i = 0, j = 0, k = l;
    i = l;
    j = q+1;
    for (k = l; k <= r; k++)
    {
        if (i > q)
        {
            B[k] = A[j];
            j++;
        }
        else if (j > q+m)
        {
            B[k] = A[i];
            i++;
        }
        else if (A[i] < A[j] || A[i] == A[j])
        {
            B[k] = A[i];
            i++;
        }
        else
        {
            B[k] = A[j];
            j++;
        }
    }
    for (k = l; k <= r; k++)
    {
        A[k] = B[k];
    }
}