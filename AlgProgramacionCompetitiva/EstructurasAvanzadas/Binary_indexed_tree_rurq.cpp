/*
    https://www.geeksforgeeks.org/binary-indexed-tree-or-fenwick-tree-2/

    range update and range query
    https://www.geeksforgeeks.org/binary-indexed-tree-range-update-range-queries/
*/

#include <bits/stdc++.h>
#define vi vector<int>
#define LSOne(i) ((i) & (-(i)))
using namespace std;

vi arr;
vi BITree;
vi BITree2;
int n;

void print(vi& A)
{
    for(int i=0 ; i<A.size() ; ++i)
        cout<<A[i]<<' ';
    cout<<'\n';
}

void updated(vi& A, int i, int val)    // actualiza una rama
{
    while(i <= n)
    {
        A[i] += val;       
        i += LSOne(i);  // sube al padre
    }
}

void ini_BIT(vi& A)
{
    A.resize(n+1);
    for(int i=0 ; i<=n ; ++i)
        A[i] = 0;
    for(int i=1 ; i<=n ; ++i)    // actualiza todas las ramas
        updated(A, i, arr[i]);
}

int rsq(vi& A, int i)
{
    int suma = 0;
    while(i)
    {
        suma += A[i];        
        i -= LSOne(i);      // sube al padre
    }
    return suma;
}

int rsq(vi& A, int i, int j)
{
    return rsq(A,j) - rsq(A,i-1);
}

int rsq(int k, vi& A, vi& B)
{
    return (rsq(A,k)*k) - rsq(B,k);
}

void updated(vi& A, vi& B, int i, int j, int v)
{
    updated(A,i,v);
    updated(A,j+1,-v);

    updated(B,i,v*(i-1));
    updated(B,j+1,-v*j);
}  

int range_rsq(int i, int j, vi& A, vi& B)
{
    return rsq(j, A, B) - rsq(i-1, A, B);
}

void solve()
{
    cin>>n;
    arr.resize(n+1,0);
    for(int i=1; i<=n ; ++i)
        cin>>arr[i];
    ini_BIT(BITree);
    ini_BIT(BITree2);
    updated(BITree,BITree2,4,8,5);
    cout<<range_rsq(1,5,BITree,BITree2)<<'\n';
    updated(BITree,BITree2,1,4,3);
    cout<<range_rsq(1,4,BITree,BITree2);
}

int main()
{
    solve();
}