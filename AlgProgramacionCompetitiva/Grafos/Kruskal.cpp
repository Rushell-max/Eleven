#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <sstream>
#include <fstream>
#define tiii tuple<int,int,int>
#define pii pair<int,int>
#define vtiii vector<tiii>
#define vpii vector<pii>
#define vvpii vector<vpii>
#define vi vector<int>
#define vvi vector<vi>
using namespace std;

vvpii adjacent;
vvpii MST;
vtiii edges;
int min_cost=0;
int num_taken=0;
int n;

vi parent;

void ini()
{
    for(int i=0 ; i<n ; ++i)
        parent[i]=i;
}

int par(int a)
{
    while(a!=parent[a])
    {
        parent[a] = parent[parent[a]];
        a=parent[a];
    }
    return a;
}

void Union(int a, int b)
{
    a=par(a);
    b=par(b);
    if(a==b)return;
    parent[b]=a;
}

bool same_set(int a, int b)
{
    a=par(a);
    b=par(b);
    if(a==b) return 1;
    return 0;
}

void Kruskal()
{
    sort(edges.begin(), edges.end());
    ini();
    for(int i=0 ; num_taken!=n-1 ; ++i)
    {
        int w=get<0>(edges[i]);
        int u=get<1>(edges[i]);
        int v=get<2>(edges[i]);
        // cout<<"arista "<<u<<" "<<v<<" "<<w<<'\n';
        if(same_set(u,v))continue;
        min_cost+=w;
        num_taken++;
        // cout<<"n "<<n<<" "<<" taken "<<num_taken<<'\n';
        Union(u,v);
        MST[u].push_back({v,w});
        MST[v].push_back({u,w});
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
            if(!visitados[u][v.first])
            {
                visitados[u][v.first] = 1;
                visitados[v.first][u] = 1;
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

void ini_edge_list()
{
    vvi visitados(adjacent.size(),vi(adjacent.size(),0));
    for(int u=0 ; u<adjacent.size() ; ++u)
    {
        for(auto v : adjacent[u])
        {
            if(!visitados[u][v.first])
            {
                visitados[u][v.first] = v.second;
                visitados[v.first][u] = v.second;
                edges.push_back({v.second,u,v.first});
                // cout<<"insertando "<<u<<" "<<v.first<<" "<<v.second<<'\n';
            }
        }
    }  
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
    graficar("MST_K.dot");
    MST.resize(n);
    parent.resize(n);
    ini_edge_list();
    Kruskal();
    cout<<"MST cost: "<<min_cost<<'\n';
    for(int i=0 ; i<n ; ++i)
    {
        cout<<i<<": ";
        for(int j=0 ; j<MST[i].size() ; ++j)
            cout<<MST[i][j].first<<"("<<MST[i][j].second<<") ";
        cout<<'\n';
    }
}
