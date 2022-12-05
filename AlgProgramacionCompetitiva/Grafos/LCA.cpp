/*
    LCA lowest common ancestor (ancestro comun minimo)
        sparce table
*/

#include <vector>
#include <iostream>
#include <math.h>
#define vi vector<int>
#define vvi vector<vi>
#define MAX 500
using namespace std;
// LCA
vvi tree;
vi L(2*MAX),S(2*MAX),A(MAX);
int indx;
// SPARSE TABLE
vvi st(MAX,L);
int n, max_f;

void dfs(int cur, int depth)
{
    A[cur] = indx;      // aparicion
    S[indx] = cur;      // secuencia
    L[indx++] = depth;  // profundidad
    for(auto next : tree[cur])
    {
        dfs(next, depth+1);
        A[indx] = cur;      // regresa (sube)
        L[indx++] = depth; 
    }
}

void ini()
{
    for(int i=0 ; i<n ; ++i)
        st[0][i] = i;
    for(int i=1 ; i<max_f ; ++i)
    {
        for(int j=0 ; j + (1 << i) <= n ; ++j)
        {
            if(L[st[i-1][j]] <= L[st[i-1][j+(1<<(i-1))]])
                st[i][j] = st[i-1][j];
            else
                st[i][j] = st[i-1][j+(1<<(i-1))];
        }
    }
}

int rmq(int l, int r)
{
    cout<<l<<" "<<r<<'\n';
    int j=log2(r-l+1);
    // int minimo = min(L[st[j][l]], L[st[j][r-(1<<j)+1]]);
    if(L[st[j][l]] <= L[st[j][r-(1<<j)+1]])         // menor nivel de las primeras apariciones entre l y r
        return st[j][l];
    return st[j][r-(1<<j)+1];
}


int LCA(int u, int v)
{
    if(v < u)  
        return S[rmq(A[v], A[u])];          // entre la primera aparicion de u y v
    return S[rmq(A[u], A[v])];
}

int main()
{
    tree = {
                {1, 7},     // 0
                {2, 3, 6},  // 1
                {},         // 2
                {4,5},      // 3
                {},         // 4
                {},         // 5
                {},         // 6
                {8, 9},     // 7
                {},         // 8
                {}          // 9
            };
    // construye L, E y H
    indx = 0;
    dfs(0,0);
    // cosntruye SPARSE TABLE
    n = indx;
    max_f = log2(n);
    ini();
    cout<<"LCA "<<LCA(4,6);
}
