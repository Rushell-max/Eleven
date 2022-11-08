#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#define vi vector<int>
#define vvi vector<vi>
using namespace std;
enum{visitado=0, novisitado=1, explorado=2};

vvi adjacent;
vi parent;
vi visited;
bool ac=1;

void cycle_check(int u)
{
    visited[u]=explorado;
    for(auto v:adjacent[u])
    {
        if(visited[v]==novisitado)  // explorado no visitado
        {
            cout<<u<<" "<<v<<" arista de arbol\n";
            parent[v]=u;
            cycle_check(v);
        }
        else if(visited[v]==explorado)  // explorado explorado
        {
            if(parent[u]==v)    
                cout<<u<<" "<<v<<" arista bidireccional/trivial\n";
            else
                cout<<u<<" "<<v<<" arista atras/no trivial\n";
            ac=0;
        }
        else if(visited[v]==visitado)       // explorado visitado (caso raro)
            cout<<u<<" "<<v<<" arista adelante/cruzada\n";
    }
    visited[u]=visitado;
}

void cycle_check()
{
    for(int u=0 ; u<adjacent.size() ; ++u)
        if(visited[u]==novisitado)
            cycle_check(u);
}

void graficar(string dir)
{
    vi visited(adjacent.size(),0);
    ofstream f(dir);
    f<<"digraph G{";
    for(int u=0 ; u<adjacent.size() ; ++u)
        for(auto v : adjacent[u])
                f<<u<<" -> "<<v<<";\n";
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
                    {1,5},     // 0
                    {3},  // 1
                    {4, 1},     // 2
                    {},        // 3
                    {6, 7},  // 4
                    {0},        // 5
                    {},        // 6
                    {},        // 7
                    {9},        // 8
                    {10},      // 9
                    {8}         // 10
                };
    // adjacent =  { 
    //                 {1},     // 0
    //                 {3},  // 1
    //                 {4, 1},     // 2
    //                 {},        // 3
    //                 {6, 7},  // 4
    //                 {0},        // 5
    //                 {},        // 6
    //                 {},        // 7
    //                 {},        // 8
    //                 {8,10},      // 9
    //                 {}         // 10
    //             };
    parent.resize(adjacent.size());
    visited.resize(adjacent.size(),novisitado);
    graficar("digrafo_ciclo.dot");
    cycle_check();
    if(ac)
        cout<<"no tiene ciclos\n";
    else
        cout<<"tiene ciclos\n";
}