#include <iostream>
#include <queue>
#include <vector>
#define vi vector<int>
#define vvi vector<vi>
#define pii pair<int,int>
#define vpii vector<pii>
#define vvpii vector<vpii>
#define pqpii priority_queue<pii,vpii,greater<pii>>
using namespace std;
enum{inf=INT_MAX};
vvpii adjacent;             
vi dist;
pqpii pq;
int n;

void dijkstra(int org)
{
    dist[org]=0;
    pq.push({0,org});
    while(!pq.empty())
    {
        auto e = pq.top();      // peso, vertice
        pq.pop();
        int u=e.second;
        int w=e.first;
        if(w>dist[u]) continue;
        for(auto a:adjacent[u])      // vertice, peso
        {
            int v=a.first;
            int d=a.second;
            if(dist[v] <= dist[u] + d) continue;
            dist[v] = dist[u] + d;
            pq.push({dist[v], v});
        }
    }
}

int main()
{
    adjacent =  { 
                    {{1,2},{3,7},{2,6}},     // 0
                    {{4,9},{3,3}},  // 1
                    {{4,1}},     // 2
                    {{4,5}},        // 3
                    {}  // 4
                };
    n = adjacent.size();
    dist.resize(n,inf);
    int org=0;
    dijkstra(org);
    cout<<"distancia de "<<org<<" a todos los vertices:\n";
    for(int i=0 ; i<n ; ++i)
        cout<<"a "<<i<<" -> "<<dist[i]<<'\n';
}