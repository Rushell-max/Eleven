/*
    grafo completo:
        cantidad de aristas |E|: |E| = [(|V|)*(|V|-1)]/2
    grafo con componentes conexas:
        max cantidad de aristas E: |E| = [(|V| - CC)*(|V| - CC + 1)]/2
        cantidad de aristas sin ciclos: |E| = |V| - CC
*/

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>
#define vi vector<int>
#define vvi vector<vi>
#define qi queue<int>
using namespace std;

enum{ unvisited = -1, visited = -2, inf = INT_MAX};
vi dfs_num;
vvi adjacent;

void dfs(int u)
{
    dfs_num[u] = visited;
    cout<<u<<" ";
    for(auto v : adjacent[u])
        if(dfs_num[v] == unvisited)
            dfs(v);
}

vi bfs(int i)
{
    qi q;
    vi dist(adjacent.size(), inf);  // acumula niveles de acceso
    dist[i] = 0;                        
    q.push(i);
    while(!q.empty())
    {   
        int u = q.front(); q.pop();
        cout<<u<<" ";
        for(auto v : adjacent[u])
        {
            if(dist[v]!=inf) continue;
            dist[v] = dist[u] + 1;      // añade nivel
            q.push(v);
        }
    }
    cout<<'\n';
    return dist;
}

void graficar(string dir)
{
    vvi visitados(adjacent.size(),vi(adjacent.size(),0));
    ofstream f(dir);
    f<<"graph G{";
    for(int u=0 ; u<adjacent.size() ; ++u)
    {
        for(auto v : adjacent[u])
        {
            if(!visitados[u][v])
            {
                visitados[u][v] = 1;
                visitados[v][u] = 1;
                f<<u<<" -- "<<v<<";\n";
            }
        }
    }  
    f<<"}";
    f.close();
    std::stringstream dir1(dir);
    std::string name, ext, aux;
    std::getline(dir1,aux,'.');
    name = aux;
    std::getline(dir1,aux,'.');
    ext = aux;
    system(&(("dot "+ dir + " -o " + name + ".png -Tpng")[0]));
    system(&((name + ".png")[0]));
    // system("dot grafo.dot -o grafo.png -Tpng");           //dot grafo.dot -o grafo.png -Tpng
    // system("grafo.png");
}

int main()
{
    adjacent =  { 
                    {1, 5},     // 0
                    {0, 3, 2},  // 1
                    {4, 1},     // 2
                    {1},        // 3
                    {2, 6, 7},  // 4
                    {0},        // 5
                    {4},        // 6
                    {4},        // 7
                    {9},        // 8
                    {8,10},      // 9
                    {9}         // 10
                };
    dfs_num.resize(adjacent.size(),unvisited);
    graficar("grafo.dot");
    // prueba dfs
    // for(int u=0 ; u<adjacent.size() ; ++u)
    //     if(dfs_num[u] == unvisited)
    //         dfs(u);

    //prueba bfs
    // vi dist = bfs(0);
    // for(int i=0 ; i<dist.size() ; ++i)
    //     cout<<i<<" dist: "<<dist[i]<<'\n';

    //componentes conexos
    // int numCC = 0;
    // for(int u=0 ; u<adjacent.size() ; ++u)
    // {
    //     if(dfs_num[u] == unvisited)
    //     {
    //         cout<<"CC "<<++numCC<<": ";
    //         dfs(u);
    //         cout<<'\n';
    //     }
    // }
}