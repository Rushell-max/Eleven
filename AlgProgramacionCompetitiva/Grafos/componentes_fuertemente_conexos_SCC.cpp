#include <iostream>
#include <stack>
#include <vector>
#define vi vector<int>
#define vvi vector<vi>
#define si stack<int>
using namespace std;

enum{visitado=1, novisitado=0, orig=2, trans=3};

vvi adjacent, adjacent_t;
vi dfs_num, S;
int n, n_SCC=0;

void kosaraju(int u, int pass)
{
    dfs_num[u]=visitado;
    vvi& neighbor = (pass==orig)? adjacent : adjacent_t; // para grafo original o grafo transpuesto
    for(auto v : neighbor[u])
        if(dfs_num[v] == novisitado)
            kosaraju(v,pass);
    S.push_back(u);
}

vi dfs_low, visited;
si st;
int dfsNumberCounter;

void tarjan(int u)
{
    dfs_low[u]=dfs_num[u]=dfsNumberCounter++;
    st.push(u);
    visited[u]=1;
    for(auto v:adjacent[u])
    {
        if(dfs_num[v]==novisitado)
            tarjan(v);
        if(visited[v])
            dfs_low[u] = min(dfs_low[u],dfs_low[v]);
    }
    if(dfs_num[u]==dfs_low[u])      // raiz de un SCC
    {
        ++n_SCC;
        while(1)
        {
            int v=st.top();st.pop();
            cout<<v<<' ';
            visited[v]=0;
            if(u==v)break;
        }
        cout<<'\n';
    }
}

int main()
{
    adjacent =  { 
                {1},     // 0
                {3},  // 1
                {1},     // 2
                {2,4},        // 3
                {5},  // 4
                {7},        // 5
                {4},       // 6
                {6}        // 7
            };
    adjacent_t =  { 
                    {},     // 0
                    {0,2},  // 1
                    {3},     // 2
                    {1},        // 3
                    {3,6},  // 4
                    {4},        // 5
                    {7},       // 6
                    {5}        // 7
                };
    n = adjacent.size();
    // componentes fuertemente conexos con kosaraju
    // dfs_num.resize(n,novisitado);
    // for(int u=0 ; u<n ; ++u)
    //     if(dfs_num[u]==novisitado)
    //         kosaraju(u,orig);
    // dfs_num.assign(n,novisitado);
    // for(int i=n-1 ; i>=0 ; --i)
    //     if(dfs_num[S[i]]==novisitado)
    //         n_SCC++, kosaraju(S[i],trans);
    // cout<<"CSS "<<n_SCC<<'\n';

    // componentes fuertemente conexos con tarjan
    dfs_num.resize(n,novisitado);
    dfs_low.resize(n,0);
    visited.resize(n,0);
    dfsNumberCounter = n_SCC = 0;
    for(int u=0 ; u<n ; ++u)
        if(dfs_num[u]==novisitado)
            tarjan(u);
    cout<<"CSS "<<n_SCC<<'\n';
}