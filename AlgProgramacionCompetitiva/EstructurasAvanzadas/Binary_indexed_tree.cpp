/*
    https://www.geeksforgeeks.org/binary-indexed-tree-or-fenwick-tree-2/

    range update and point query
    https://www.geeksforgeeks.org/binary-indexed-tree-range-updates-point-queries/
*/

#include <bits/stdc++.h>
#define vi vector<int>
#define LSOne(i) ((i) & (-(i)))
using namespace std;

vi arr;
vi BITree;
int n;

void print(vi& A)
{
    for(int i=0 ; i<A.size() ; ++i)
        cout<<A[i]<<' ';
    cout<<'\n';
}

void updated(int i, int val)    // actualiza una rama
{
    while(i <= n)
    {
        BITree[i] += val;       
        i += LSOne(i);  // sube al padre
    }
}


void ini_BIT()
{
    BITree.resize(n+1);
    for(int i=0 ; i<=n ; ++i)
        BITree[i] = 0;
    for(int i=1 ; i<=n ; ++i)    // actualiza todas las ramas
        updated(i, arr[i]);
}

int rsq(int i)
{
    int suma = 0;
    while(i)
    {
        suma += BITree[i];        
        i -= LSOne(i);      // sube al padre
    }
    return suma;
}

int rsq(int i, int j)
{
    return rsq(j) - rsq(i-1);
}

// range updates and point query
void updated(int i, int j, int val)     // para que funcione, BITree debe comenzar en 0s
{
    updated(i,val);
    updated(j+1,-val);
}

int point_query(int i)          // valor elemento posicion i
{
    return rsq(i);
}

int main()
{
    cin>>n;
    arr.resize(n+1,0);
    for(int i=1; i<=n ; ++i)
        cin>>arr[i];
    ini_BIT();
    // print(arr);
    // print(BITree);
    // cout<<rsq(5)<<'\n'<<rsq(7)<<'\n'<<rsq(9)<<'\n';
    // updated(5,-1);
    // arr[5]-=1;
    // updated(6,-1);
    // arr[6]-=1;
    // cout<<rsq(5)<<'\n'<<rsq(7)<<'\n'<<rsq(9)<<'\n';

    print(arr);
    print(BITree);
    updated(1,6,5);
    // updated(6,10,3);
    print(arr);
    print(BITree);
    cout<<point_query(5)<<'\n';
}  