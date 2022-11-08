#include <vector>
#include <iostream>
#define ll long long int
#define vll vector<ll>
#define LSOne(i) ((i) & (-(i)))
using namespace std;

vll arr,FT;
ll n,m;

void update(ll i, ll v)
{
    while(i<=n)
    {
        FT[i] += v;
        i += LSOne(i);
    }
}

// void ini()
// {
//     for(ll i=0 ; i<=n ; ++i)
//         FT[i] = 0;
// }

ll rsq(ll i)
{
    ll sum=0;
    while(i)
    {
        sum += FT[i];
        i -= LSOne(i);
    }
    return sum;
}

void solve()
{
    cin>>n>>m;
    arr.resize(n+1,0);
    FT.resize(n+1,0);
    // ini();
    while(m--)
    {
        char op;cin>>op;
        if(op == '+')
        {
            ll a,b;cin>>a>>b;
            update(a+1,b);
        }
        else
        {
            ll a;cin>>a;
            cout<<rsq(a)<<'\n';
        }
    }
}

int main()
{   
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif
    solve();
}