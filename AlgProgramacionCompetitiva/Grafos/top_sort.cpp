#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <queue>
#define vi vector<int>
#define vvi vector<vi>
#define pqi priority_queue<int,vi,greater<int>>
using namespace std;

enum { visitado = 1, novisitado = 0};

vvi adjacent;
vi visited;
vi ts;
vi degree;

void top_sort(int u)
{   
    visited[u] = visitado;
    for(auto v : adjacent[u])
        if(visited[v]==novisitado)
            top_sort(v);
    ts.push_back(u);
}

void top_sort()
{
    for(int i=0 ; i<adjacent.size() ; ++i)
        if(visited[i]==novisitado)
            top_sort(i);
    reverse(ts.begin(), ts.end());
}

void set_degree()
{
    for(int i=0 ; i<adjacent.size() ; ++i)
        for(int j=0 ; j<adjacent[i].size() ; ++j)
            degree[adjacent[i][j]]++;
}

void top_sort_kahn()
{
    pqi pq;
    for(int u=0 ; u<adjacent.size() ; ++u)
        if(degree[u]==0)
            pq.push(u);
    while(!pq.empty())
    {
        int u=pq.top(); pq.pop();
        ts.push_back(u);
        for(auto v:adjacent[u])
        {
            degree[v]--;
            if(degree[v]>0) continue;
            pq.push(v);
        }
    }
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
                    {1},     // 0
                    {3},  // 1
                    {4, 1},     // 2
                    {},        // 3
                    {6, 7},  // 4
                    {0},        // 5
                    {},        // 6
                    {},        // 7
                    {},        // 8
                    {8,10},      // 9
                    {}         // 10
                };
    visited.resize(adjacent.size(),novisitado);
    graficar("digrafo.dot");
    //top sort normal
    // top_sort();
    // for(auto a:ts)
    //     cout<<a<<' ';
    // cout<<'\n';

    //top sort kahn
    // degree.resize(adjacent.size(),0);
    // set_degree();
    // top_sort_kahn();
    // for(auto a:ts)
    //     cout<<a<<' ';
    // cout<<'\n';
}