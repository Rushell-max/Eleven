#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <queue>
#define pii pair<int,int>
#define vi vector<int>
#define vvi vector<vi>
#define vpii vector<pii>
#define vvpii vector<vpii>
#define pqpii priority_queue<pii,vpii,greater<pair<int,int>>>
using namespace std;

vvpii adjacent;
vi taken;
pqpii pq;
int min_cost=0,num_taken=0;
int n;

void process(int u)
{
    taken[u]=1;
    for(auto v:adjacent[u])
        if(!taken[v.first])
            pq.push({v.second,v.first});    // peso, vertice llegada
}

void Prim()
{
    process(0);
    while(!pq.empty() && num_taken!=n-1)        // max num aristas a tomar, max cantidad aristas en un arbol = V-1
    {
        auto a=pq.top(); pq.pop();
        int w=a.first;          // peso
        int v=a.second;         // vertice llegada
        if(taken[v])continue;   
        min_cost+=w;
        process(v);
        num_taken++;
    }
    cout<<"MST cost: "<<min_cost<<'\n';
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
            if(!visitados[u][v.first])
            {
                visitados[u][v.first] = v.second;
                visitados[v.first][u] = v.second;
                f<<u<<" -- "<<v.first<<"[label="<<v.second<<"];\n";
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
                    {{1,2}, {5,3}},     // 0
                    {{0,2}, {3,1}, {2,7}},  // 1
                    {{4,6}, {1,7}},     // 2
                    {{1,3},{4,1}},        // 3
                    {{2,6}, {6,3}, {7,9}, {6,3}},  // 4
                    {{0,3},{7,5}},        // 5
                    {{4,3}},        // 6
                    {{4,9},{5,7}}        // 7
                };
    n=adjacent.size();
    graficar("MST_P.dot");
    taken.resize(n,0);
    Prim();
}