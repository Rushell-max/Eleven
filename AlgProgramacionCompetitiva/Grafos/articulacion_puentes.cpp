#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <fstream>
#define vi vector<int>
#define pii pair<int,int>
#define vpii vector<pii>
#define vvi vector<vi>
using namespace std;
enum{visitado=1, novisitado=0};
vvi adjacent;
vi articulaciones;
vpii puentes;
vi dfs_num, dfs_low;
vi parent;
int counter=0, root, rootChild;

void articulacion_puente(int u)
{
    dfs_num[u] = counter++;
    dfs_low[u] = dfs_num[u];
    for(auto v:adjacent[u])
    {
        if(dfs_num[v]==novisitado)
        {
            parent[v] = u;
            if(u == root) ++rootChild;
            articulacion_puente(v);
            if(dfs_low[v]>=dfs_num[u]) articulaciones[u]=1;
            if(dfs_low[v]>dfs_num[u]) puentes.push_back({u,v});
            dfs_low[v]=min(dfs_low[u], dfs_low[v]);
        }
        else if(v!=parent[u])
            dfs_low[u]=min(dfs_low[u],dfs_num[v]);
    }
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
                    {4}        // 7
                };
    int n=adjacent.size();
    dfs_num.resize(n,novisitado);
    dfs_low.resize(n,0);
    parent.resize(n,-1);
    articulaciones.resize(n,0);
    graficar("articulaciones_puentes.dot");

    for(int u=0 ; u<n ; ++u)
    {
        if(dfs_num[u]==novisitado)
        {
            root=u; rootChild=0;
            articulacion_puente(u);
            articulaciones[root] = (rootChild > 1);
        }
    }
    cout<<"ARTICULACIONES\n";
    for(int u=0 ; u<n ; ++u)
        if(articulaciones[u])
            cout<<u<<' ';
    cout<<'\n';
    cout<<"PUENTES\n";
    for(auto a:puentes)
        cout<<a.first<<" "<<a.second<<'\n';
}
