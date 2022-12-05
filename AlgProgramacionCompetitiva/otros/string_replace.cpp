#include <bits/stdc++.h>
using namespace std;
int main()
{
    string a = "porcion a cambiar";
    int i,k;
    i = 2;
    k = 6;
    cout<<a<<'\n';
    char tmp = a[i+k-1];
    a.replace(i+1, k-i+1, a, i, k-i+1);
    a[i] = tmp;
    cout<<a;
}