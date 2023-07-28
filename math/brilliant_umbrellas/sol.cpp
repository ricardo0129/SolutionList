#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define ll long long
#define pll pair<ll,ll>
#define pii pair<int,int>
#define vi vector<int> 
#define vll vector<ll>
#define FOR(i,n) for(int i=0;i<n;i++)
#define sz(A) (int)(A).size()
#define pb push_back
#define f first
#define s second

void solve() {
    ll n; cin>>n;
    ll x = ceil(2.0*sqrt(n)/3.0);
    cout<<x<<endl;
    ll prev = 1;
    ll curr = 1;
    int k = 0;
    vll vals;
    FOR(i,x) {
        cout<<prev*curr<<" ";
        vals.pb(prev*curr);
        prev = curr;
        if(k%4<=1) curr+=1;
        else curr+=2;
        k++;
    }
}

int main()
{
	int tc=1; 
	//cin>>tc; //remove this for single tc
	while(tc--) {
		solve();
	}
	return 0;
}

