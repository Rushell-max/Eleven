#include <iostream>
#include <algorithm>
#include <limits>
using namespace std;
int main()
{
    string s="012210";
    do
    {
        cout<<s<<'\n';
    }while(next_permutation(s.begin(),s.end()));
}