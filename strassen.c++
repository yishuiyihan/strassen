#include <stdio.h>
#include <algorithm>

using namespace std;

const int N = 4;
int A[N][N],B[N][N],C[N][N];

void input(int A[][N],int n)
{
    for(int i = 0;i<n;i++)
    {
        for(int j = 0;j<n;j++)
        {
            scanf("%d",&A[i][j]);
        }
    }
    return;
}

void output(int C[][N],int n)
{
    for(int i = 0;i<n;i++)
    {
        for(int j = 0;j<n;j++)
        {
            printf("%d  ",C[i][j]);
        }
        printf("\n");
    }
    return;
}

void matrix_mult(int A[][N],int B[][N],int C[][N])
{
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<2;j++)
        {
            C[i][j] = 0;
            for(int k=0;k<2;k++)
            {
                C[i][j] = C[i][j]+A[i][k]*B[k][j];
            }
        }
    }
    return;
}

void matrx_add(int n,int A[][N],int B[][N],int C[][N])
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            C[i][j] = A[i][j]+B[i][j];
        }
    }
    return;
}

void matrx_sub(int n,int A[][N],int B[][N],int C[][N])
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            C[i][j] = A[i][j]-B[i][j];
        }
    }
    return;
}

void strassen(int n,int A[][N],int B[][N],int C[][N])
{
    int A11[N][N],A12[N][N],A21[N][N],A22[N][N];
    int B11[N][N],B12[N][N],B21[N][N],B22[N][N];
    int C11[N][N],C12[N][N],C21[N][N],C22[N][N];
    int M1[N][N],M2[N][N],M3[N][N],M4[N][N],M5[N][N],M6[N][N],M7[N][N];

    int AA[N][N], BB[N][N], MM1[N][N], MM2[N][N];
    if(n == 2)
    {
        matrix_mult(A,B,C);
    }
    else
    {
        for(int i=0;i<n/2;i++)
        {
            for(int j=0;j<n/2;j++)
            {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j+n/2];
                A21[i][j] = A[i+n/2][j];
                A22[i][j] = A[i+n/2][j+n/2];
                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j+n/2];
                B21[i][j] = B[i+n/2][j];
                B22[i][j] = B[i+n/2][j+n/2];
            }
        }
        matrx_sub(n/2,B12,B22,BB);
        strassen(n/2,A11,BB,M1);

        matrx_add(n/2,A11,A12,AA);
        strassen(n/2,AA,B22,M2);

        matrx_add(n/2,A21,A22,AA);
        strassen(n/2,AA,B11,M3);

        matrx_sub(n/2,B21,B11,BB);
        strassen(n/2,A22,BB,M4);

        matrx_add(n/2,A11,A22,AA);
        matrx_add(n/2,B11,B22,BB);
        strassen(n/2,AA,BB,M5);

        matrx_sub(n/2,A12,A22,AA);
        matrx_add(n/2,B21,B22,BB);
        strassen(n/2,AA,BB,M6);

        matrx_sub(n/2,A11,A21,AA);
        matrx_add(n/2,B11,B12,BB);
        strassen(n/2,AA,BB,M7);

        matrx_add(n/2,M5,M4,MM1);
        matrx_sub(n/2,M2,M6,MM2);
        matrx_sub(n/2,MM1,MM2,C11);
        matrx_add(n/2,M2,M1,C12);
        matrx_add(n/2,M3,M4,C21);

        matrx_add(n/2,M5,M1,MM1);
        matrx_add(n/2,M3,M7,MM2);
        matrx_sub(n/2,MM1,MM2,C22);

        for(int i=0;i<n/2;i++)
        {
            for(int j=0;j<n/2;j++)
            {

                C[i][j] = C11[i][j];
                C[i][j+n/2] = C12[i][j];
                C[i+n/2][j] = C21[i][j];
                C[i+n/2][j+n/2] = C22[i][j];
            }
        }        

    }


}


int main()
{
    input(A,N);
    input(B,N);
    strassen(N,A,B,C);
    output(A,N);
    output(B,N);
    printf("\n");
    output(C,N);

    return 0;
}
