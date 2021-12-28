#include <iostream>
#include <queue>
#include <map>

using namespace std;
int main()
{
    priority_queue<pair<int,string>,vector<pair<int,string>>,greater<pair<int,string>>> vertices;
    // priority_queue<pair<int,string>> vertices;
    vertices.push(make_pair(INT_MAX,"lima"));
    vertices.push(make_pair(INT_MAX,"puno"));
    vertices.push(make_pair(INT_MAX,"tacna"));
    vertices.push(make_pair(INT_MAX,"ica"));
    vertices.push(make_pair(0,"arequipa"));

    cout<<vertices.top().second<<'\n';
    

    // while( !vertices.empty() )
    // {
    //     cout<<vertices.top().second<<' ';
    //     vertices.pop();
    // }

    // multimap<int,string> vertices;
    // // priority_queue<pair<int,string>> vertices;
    // vertices.insert(make_pair(INT_MAX,"lima"));
    // vertices.insert(make_pair(INT_MAX,"puno"));
    // vertices.insert(make_pair(INT_MAX,"tacna"));
    // vertices.insert(make_pair(INT_MAX,"ica"));
    // vertices.insert(make_pair(0,"arequipa"));

    // for( multimap<int,string>::iterator it=vertices.begin() ; it!=vertices.end() ; ++it  )
    // {
    //     cout<<it->first<<' '<<it->second<<'\n';
    // }
}