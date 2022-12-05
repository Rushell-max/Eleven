#include <iostream>
#include <map>
using namespace std;
int main()
{
    multimap<int,multimap<int,int>> m;
    multimap<int,int> a;
    multimap<int,int> b;
    a.insert(make_pair(0,1));
    a.insert(make_pair(1,1));
    b.insert(make_pair(0,1));
    m.insert(make_pair(0,a));
    m.insert(make_pair(1,b));
    m.insert(make_pair(0,b));
    cout<<m.size();
}