#include <vector>
#include <iostream>
#include <queue>
#include <sstream>
#include <fstream>
#define vi vector<int>
#define vvi vector<vi>
#define qi queue<int>
using namespace std;

enum {inf=INT_MAX};

vvi adjacent;
vi color;

bool is_bipartite()
{
    int u=0;
    qi q; q.push(u);
    color[u] = 0;
    while(!q.empty())
    {
        int u=q.front(); q.pop();
        for(auto v:adjacent[u])
        {
            if(color[v]==inf)
            {
                color[v] = 1-color[u];
                q.push(v);
            }
            else if(color[u]==color[v])
                return 0;
        }
    }
    return 1;
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
                    {1, 5, 9},     // 0
                    {0, 3, 2},  // 1
                    {4, 1},     // 2
                    {1},        // 3
                    {2, 6, 7},  // 4
                    {0},        // 5
                    {4},        // 6
                    {4},        // 7
                    {9,10},        // 8
                    {8,10,0},      // 9
                    {9,8}         // 10
                };
    color.resize(adjacent.size(),inf);
    graficar("grafo_bipartito.dot");
    if(is_bipartite())
        cout<<"si es bipartito\n";
    else
        cout<<"no es bipartito\n";
}