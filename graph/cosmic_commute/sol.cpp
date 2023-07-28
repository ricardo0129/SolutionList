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

const int N = 2e5+1;
vi G[N];
int n,m,k;
vi dist(int start) {
    vi dist(n+1, -1);
    dist[start] = 0;
    queue<int> q;
    q.push(start);
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int v: G[u]) {
            if(dist[v]==-1) {
                dist[v] = dist[u]+1;
                q.push(v);
            }
        }
    }
    return dist;
}
void solve() {
    scanf("%d%d%d", &n, &m, &k);
    vi worm(k);
    FOR(i,k) cin>>worm[i];
    FOR(i,m) {
        int u,v;
        scanf("%d%d", &u, &v);
        G[u].pb(v);
        G[v].pb(u);
    }
    vi source = dist(1);
    vi sink = dist(n);
    vector<pll> ans;
    ll total = 0;
    FOR(i,k) {
        total += sink[worm[i]];
    }
    ans.pb(make_pair(source[n],1));
    FOR(i,k) {
       ll d1 = source[worm[i]]; 
       ll d2 = total - sink[worm[i]];
       ans.pb(make_pair(d1*(k-1) + d2, (ll)k-1));
    }
    sort(ans.begin(), ans.end(), [](pll& a, pll& b){
            return a.f*b.s < b.f*a.s;
    });
    int g = gcd(ans[0].f, ans[0].s);
    cout<<ans[0].f/g<<"/"<<ans[0].s/g<<endl;
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

