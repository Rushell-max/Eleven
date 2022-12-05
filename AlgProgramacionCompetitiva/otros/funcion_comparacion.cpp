#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

bool fn(int& a, int& b)
{
    return a>b;
}

void print(vector<int>& A)
{
    for(int i=0 ; i<A.size() ; ++i)
        cout<<A[i]<<' ';
    cout<<'\n';
}

using namespace std;
int main()
{
    // vector<int> a = {1,2,3,4,5};
    // print(a);
    // sort(a.begin(), a.end(), fn);
    // print(a);
    priority_queue<int,vector<int>,greater<int>> pq; // less=max heap(default), greater=min heap
    pq.push(1);
    pq.push(23);
    pq.push(15);
    pq.push(4);
    pq.push(9);
    pq.push(3);
    while(!pq.empty())
    {
        cout<<pq.top()<<" ";
        pq.pop();
    }
}