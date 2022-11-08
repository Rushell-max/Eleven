/*
    https://cp-algorithms.com/data_structures/sparse-table.html#range-minimum-queries-rmq
    https://www.geeksforgeeks.org/sparse-table/
*/

#include <vector>
#include <iostream>
#include <math.h>
#define vi vector<int>
#define vvi vector<vi>
#define MAX 500
using namespace std;

// vi lg(MAX+1);            // vector para calcular logaritmos
vi arr(MAX);
vvi st(MAX, arr);
int n, max_f;           // tamanio arreglo, max cant filas : log2(n)

void print(vi& A)
{
    for(int i=0 ; i<n ; ++i)
        cout<<A[i]<<' ';
    cout<<'\n';
}

void print(vvi& M)
{
    for(int i=0 ; i<=max_f ; ++i)
    {
        for(int j=0 ; j<n ; ++j)
            cout<<M[i][j]<<' ';
        cout<<'\n';
    }
    cout<<'\n';
}

void ini()
{
    // lg[0] = lg[1] = 0;
    // for(int i=2 ; i<=n ; ++i)
    //     lg[i] = lg[i/2] + 1 ;
    for(int i=0 ; i<n ; ++i)                            // primera fila
        st[0][i] = i;
    for(int i=1 ; i<=max_f ; ++i)                       // recorre filas      
    {                 
        for(int j=0 ; j + ( 1 << i) <=n ; ++j)          // j + potencia de 2, evita salir rango
        {   // compara fila anterior columna j con fila anterior columna j + 2^(i-1)
            if( arr[st[i-1][j]] <= arr[st[i-1][j + ( 1 << (i-1) )]] )       
                st[i][j] = st[i-1][j];
            else
                st[i][j] = st[i-1][j + ( 1 << (i-1))];
            // st[i][j] = min( st[i-1][j] , st[i-1][j + ( 1 << (i-1) )] );
        }
    }
}

int rmq(int L, int R)
{
    // int j=lg[R-L+1];
    int j = log2(R-L+1);                                // mayor potencia de dos
    int minimo = min( arr[st[j][L]] , arr[st[j][ R - ( 1 << j ) + 1 ]] );
    return minimo;
}

void solve()
{
    cin>>n;
    max_f = log2(n);            // max tamanio matriz
    for(int i=0 ; i<n ; ++i)
        cin>>arr[i];
    ini();
    // print(lg);
    // cout<<'\n';
    print(arr);
    cout<<'\n';
    print(st);
    cout<<'\n';
    cout<<rmq(4,9);
}

int main()
{
    solve();
}