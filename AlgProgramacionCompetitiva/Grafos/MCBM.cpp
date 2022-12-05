/*
    Topic: emparejamiento bipartito de cardinalidad maxima MCBM (MVC maximun vertex cover)

    maximum independet set (MIS)
    maximum vertex cover (MVC) -> algoritmo de aumento de camino
    MIX = V - MVC
*/
#include <iostream>
#include <vector>
#define vi vector<int>
#define vvi vector<vi>
using namespace std;

vvi adjacent;
vi visited;
vi match;

int AUG(int L)
{
    if(visited[L]) return 0;
    visited[L] = 1;
    for(int R : adjacent[L])
    {
        if(match[R]==-1 || AUG(match[R]))
        {
            match[R] = L;
            return 1;
        }
    }
    return 0;
}

int main()
{
    // adjacent = {
    //             {2,3},  // 0
    //             {2},    // 1
    //             {0,1},  // 2
    //             {0}     // 3
    //             };
    adjacent = {
                {3},        // 0
                {3,4},      // 1
                {4,5},      // 2
                {0,1},      // 3
                {1,2},      // 4
                {2}         // 5
                };
    int n = adjacent.size();
    int Vleft = n/2;
    match.assign(n,-1);
    int MCBM = 0;
    for(int i=0 ; i<Vleft ; ++i)
    {
        visited.assign(Vleft,0);
        MCBM += AUG(i);
    }
    cout<<"matchings "<<MCBM<<'\n';
}