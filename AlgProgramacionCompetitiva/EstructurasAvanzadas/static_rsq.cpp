/*
https://www.geeksforgeeks.org/range-sum-queries-without-updates/
*/
#include <bits/stdc++.h>
#define vi vector<int>
using namespace std;

vi arr;
vi sum;
int n,m;

void print(vi& A)
{
    for(int i=0 ; i<A.size() ; ++i)
        cout<<A[i]<<' ';
    cout<<'\n';
}

void ini()
{
    sum[0] = arr[0];
    for(int i=1 ; i<n ; ++i)
        sum[i] = arr[i] + sum[i-1];
}

int rsq(int a)
{
    return sum[a];
}

int rsq(int a, int b)
{
    if(a>0)
        return sum[b] - sum[a-1];
    else
        return rsq(b);
}

void solve()
{
    cin>>n>>m;
    arr.resize(n);
    sum.resize(n);
    for(int i=0 ; i<n ; ++i)
        cin>>arr[i];
    ini();
    while(m--)
    {
        int a,b;cin>>a>>b;
        cout<<"suma "<<rsq(a,b)<<'\n';
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
}