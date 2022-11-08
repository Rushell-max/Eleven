#include <bits/stdc++.h>
#define ll long long int
#define vll vector<ll>
#define vvll vector<vll>
#define vb vector<bool>
#define qll queue<ll>
#define sll stack<ll>
using namespace std;

void dfs(ll i, vb& vis, vvll& adj)
{
    vis[i] = 1;                             // marca primero como visitado
    for(int j=0 ; j<adj[i].size() ; ++j)    // recorre cada adjacente a un indice
    {   
        if(!vis[adj[i][j]])                 // si no ha sido visitado
        {
            cout<<adj[i][j]<<" -> ";
            dfs(adj[i][j], vis, adj);       // busca adjacentes
        }
    }
}

void dfs2(ll i, vvll& adj)
{
    vb vis(adj.size());             // vector con indices visitados
    sll S;                          // pila
    S.push(i);                      // primer indice a buscar
    while(!S.empty())
    {
        i = S.top();
        S.pop();
        vis[i] = 1;                 // indice visitado
        cout<<i<<" -> ";
        for(int j=0 ; j<adj[i].size() ; ++j)
            if(!vis[adj[i][j]])         // si no ha sido visitado
                S.push(adj[i][j]);
    }
} 

void bfs(ll i, vvll& adj)
{
    vb vis(adj.size());         // vector con indices visitados
    qll Q;                      // cola
    Q.push(i);
    while(!Q.empty())
    {
        i = Q.front();
        Q.pop();
        vis[i] = 1;             // indice visitado
        cout<<i<<" -> ";
        for(int j=0 ; j<adj[i].size() ; ++j)
            if(!vis[adj[i][j]])         // si no ha sido visitado
                Q.push(adj[i][j]);
    }
}

void print(vvll adj)
{
    for(int i=0 ; i<adj.size() ; ++i)
    {
        for(int j=0 ; j<adj[i].size() ; ++j)
            cout<<adj[i][j]<<' ';
        cout<<'\n';
    }
}

void solve()
{
   vvll adj =   { 
                    {1, 5},
                    {0, 3, 2},
                    {4, 1},
                    {1},
                    {2, 6, 7},
                    {0},
                    {4},
                    {4}
                };
    vb vis(adj.size());
    for(int i=0 ; i<vis.size() ; ++i)
    {
        if(!vis[i])
        {
            cout<<i<<" -> ";
            dfs(i, vis, adj);
            cout<<'\n';
        }
    }
    // print(adj);
    dfs2(0, adj);
    cout<<'\n';
    bfs(0, adj);
}

int main()
{
    solve();
}