/*
    tarea: rmq, update
*/

#include <vector>
#include <iostream>
#define vi vector<int>
#define l(n) (n<<1) + 1
#define r(n) (n<<1) + 2 
using namespace std;

vi arr, st;
int n;

void print(vi& A)
{
    for(auto a: A)
        cout<<a<<' ';
    cout<<'\n';
}

void build_st(int st_i, int a, int b)
{
    if(a==b)
    {
        st[st_i] = arr[a];
        return;
    }
    int m = (a+b)/2;
    // cout<<"m "<<m<<'\n';
    build_st(l(st_i), a, m);
    build_st(r(st_i), m+1, b);
    st[st_i] = min(st[l(st_i)], st[r(st_i)]);
}

int rmq(int st_i, int st_l, int st_r, int a, int b)
{
    // cout<<"i "<<st_i<<" st_l "<<st_l<<" st_r "<<st_r<<'\n';
    if( a<=st_l && st_r<=b )
        return st[st_i];
    if( st_r < a || b < st_l )
        return INT_MAX;
    int m = (st_r+st_l)/2;
    // cout<<"m "<<m<<'\n';
    return min( rmq(l(st_i), st_l, m, a, b) , rmq(r(st_i), m+1, st_r, a, b));
}

void update(int st_i, int st_l, int st_r, int i, int value)
{
    if(i<st_l || st_r<i)
        return;
    if(st_l == st_r)
    {
        st[st_i] = value;
        return;
    }
    if(st_l != st_r)
    {
        int m = (st_l+st_r)/2;
        update(l(st_i), st_l, m, i, value);
        update(r(st_i), m+1, st_r, i, value);
        st[st_i] = min(st[l(st_i)], st[r(st_i)]);
    }
}

void solve()
{
    cin>>n;
    arr.resize(n);
    st.resize(4*n,0);
    for(int i=0 ; i<n ; ++i)
        cin>>arr[i];
    build_st(0, 0, n-1);
    print(arr);
    print(st);
    int a,b;cin>>a>>b;
    cout<<rmq(0,0,n-1,a,b)<<'\n';
    int i,value;cin>>i>>value;
    arr[i] = value;
    update(0,0,n-1,i,value);
    print(arr);
    print(st);
    cin>>a>>b;
    cout<<rmq(0,0,n-1,a,b)<<'\n';
}

int main()
{
    solve();
}

