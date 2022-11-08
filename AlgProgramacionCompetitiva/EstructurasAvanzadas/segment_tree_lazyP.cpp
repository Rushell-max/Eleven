#include <vector>
#include <iostream>
#define vi vector<int>
#define l(i) ((i)<<1)+1
#define r(i) ((i)<<1)+2
using namespace std;

int large=100;
vi st(4*large,0);
vi lazy(4*large,0);
vi arr(large,0);
int n,q;

void print(vi& A)
{
    for(int i=0 ; i<n ; ++i)
        cout<<A[i]<<' ';
    cout<<'\n';
}


void build(int st_i, int a, int b)
{
    if(a==b)
    {
        st[st_i] = arr[a];
        return;
    }
    int m = (a+b)/2;
    build(l(st_i), a, m);
    build(r(st_i), m+1, b);
    st[st_i] = st[l(st_i)] + st[r(st_i)];
}

int rsq(int st_i, int st_l, int st_r, int a, int b)
{
    if(lazy[st_i])
    {
        st[st_i] += (st_r-st_l+1)*lazy[st_i];
        if(st_l!=st_r)  // si no es hoja
        {
            lazy[l(st_i)] += lazy[st_i];
            lazy[r(st_i)] += lazy[st_i];
        }
        lazy[st_i] = 0;
    }
    if(a<=st_l && st_r<=b)
        return st[st_i];
    if(b<st_l || st_r<a)
        return 0;
    int m = (st_l+st_r)/2;
    return rsq(l(st_i), st_l, m, a, b) + rsq(r(st_i), m+1, st_r, a, b);
}

void update(int st_i, int st_l, int st_r, int i, int j, int v)
{
    if(lazy[st_i])
    {
        st[st_i] += (st_r-st_l+1)*lazy[st_i];
        if(st_l != st_r)    // si no es hoja
        {
            lazy[l(st_i)] += lazy[st_i];
            lazy[r(st_i)] += lazy[st_i];
        }
        lazy[st_i] = 0;
    }
    if(j<st_l || st_r<i)
        return;
    if(i<=st_l && st_r<=j)
    {
        st[st_i] += (st_r-st_l+1)*v;
        if(st_l != st_r)
        {
            lazy[l(st_i)] += v;
            lazy[r(st_i)] += v;
        }
        return;
    }
    int m = (st_l+st_r)/2;
    update(l(st_i), st_l, m, i, j, v);
    update(r(st_i), m+1, st_r, i, j, v);
    st[st_i] = st[l(st_i)] + st[r(st_i)];
}

void solve()
{
    cin>>n>>q;
    for(int i=0 ; i<n ; ++i)
        cin>>arr[i];
    build(0,0,n-1);
    while(q--)
    {
        char op;cin>>op;
        if(op=='1')
        {
            int i,j,v;cin>>i>>j>>v;
            update(0,0,n-1,i-1,j-1,v);
            for(; i<=j ; ++i)
                arr[i-1] += v;
            print(arr);
        }
        else
        {
            int i,j;cin>>i>>j;
            cout<<rsq(0,0,n-1,i-1,j-1)<<'\n';
        }
    }
}

int main()
{
    solve();
}