/*
    dsu o union-find algorithm
    https://www.youtube.com/watch?v=ayW5B2W9hfo
    https://www.geeksforgeeks.org/union-find/
    https://es.wikipedia.org/wiki/Estructura_de_datos_para_conjuntos_disjuntos
*/


#include <bits/stdc++.h>
#define vi vector<int>
#define vvi vector<vector<int>>
#define vpi vector<pair<int,int>>
using namespace std;

vi graph;           // grafo
vvi adjacente;      // lista adjacencia
vpi aristas;        // vector con todas las aristas
int v,e;            // n vertices, n aristas

vi parent;          // arreglo de padres (representantes)
vi range;           // arreglo de alturas por cada raiz

void insert(int v1, int v2);        // inserta lista adyacencia
void print_g(vvi& A);         
void print_g(vi& A);         

int par(int a);                     // devuelve el padre
void Union(int v1, int v2);         // une dos vertices
void Union2(int v1, int v2);        // une dos vertices (optimizado)
bool isConnected(int v1, int v2);   // verifica si dos vertices estan conectados

bool isCycle(vpi& G);               // verifica si el grafo tiene ciclo
            
int main()
{
    cin>>v>>e;
    adjacente.resize(v);
    parent.resize(v);
    range.resize(v);
    for(int i=0 ; i<parent.size() ; ++i)
    {
        parent[i] = i;
        range[i]=1;
    }
    while(e--)
    {
        int a,b;cin>>a>>b;
        insert(a,b);
        // Union2(a,b);
        aristas.push_back(make_pair(a,b));
    }
    print_g(adjacente);
    // int v1,v2;
    // int c;
    // cout<<"vertices a buscar? ";cin>>c;
    // while(c)
    // {
    //     cin>>v1>>v2;
    //     cout<<isConnected(v1,v2)<<'\n';
    //     cout<<"vertices a buscar? ";cin>>c;
    // }
    // cout<<"lista de alturas\n";
    // print_g(range);
    // cout<<'\n';
    // cout<<"lista de padres (raices)\n";
    // print_g(parent);
    // cout<<'\n';
    if(isCycle(aristas))
        cout<<"contiene ciclo\n";
    else
        cout<<"no contiene ciclo\n";
}

void insert(int v1, int v2)
{
    adjacente[v1].push_back(v2);
    adjacente[v2].push_back(v1);
}

void print_g(vvi& A)
{
    for(int i=0 ; i<A.size() ; ++i)
    {
        cout<<i<<" : ";
        for(int j=0 ; j<A[i].size() ; ++j)
            cout<<A[i][j]<<" -> ";
        cout<<'\n';
    }
}

void print_g(vi& A)
{
    for(int i=0 ; i<A.size() ; ++i)
        cout<<A[i]<<" ";
    cout<<'\n';
}

int par(int a)
{
    while(parent[a] != a)
        a = parent[a];
    return a;
}

void Union(int v1, int v2)      // version no optimizada
{
    int a = par(v1);
    int b = par(v2);
    parent[b] = a;
}

void Union2(int v1, int v2)  // version optimizada
{
    int a = par(v1);
    int b = par(v2);
    if(a == b) return;
    if(range[a] < range[b])         // si la altura de a menor a la del b
        parent[a] = b;              // nueva rama
    else if(range[b] < range[a])    // si la altura de b menor a la del a
        parent[b] = a;              // nueva rama
    else                            // alturas similares
    {
        parent[b] = a;              // nueva rama mas grande en 1
        range[a]++;
    }
}

bool isConnected(int v1, int v2)
{
    int a = par(v1);
    int b = par(v2);
    if(a == b) return 1;
    return 0;
}

bool isCycle(vpi& G)
{
    for(int i=0 ; i<G.size() ; ++i)
    {
        int a=par(G[i].first);
        int b=par(G[i].second);
        if(a == b) return 1;
        Union2(a, b);
    }
    return 0;
}


