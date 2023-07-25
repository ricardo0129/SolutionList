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

struct dsu {
    vi par, ss;
    int n;
    dsu(int n=0) : n(n) {
        par.resize(n);
        ss.assign(n,1);
        for(int i=0;i<n;i++) {
            par[i] = i;
        }
    }
    int find(int u) {
        if(par[u]==u) return u;
        return par[u] = find(par[u]);
    }
    void join(int u, int v) {
        u = find(u), v = find(v);
        if(u==v) return;
        if(ss[u]<ss[v]) swap(u,v);
        ss[u]+=ss[v];
        par[v] = par[u];
    }
    ll ans() {
        ll sol = 0;
        FOR(i,n) {
            if(find(i)!=i) continue;
            sol += (ll)ss[i] * (ss[i]-1)/2;
        }
        return sol;
    }
};
const int N = 3e5+1;
vi G[N];
set<int> vals[N];
map<int,int> mp[N];
vector<dsu> dj_set;
void dfs(int u, int p) {
    for(int v: G[u]) {
        if(v==p) continue;
        dfs(v,u);
        for(int idx: vals[v]) {
            if(vals[u].count(idx)) {
                int uu = mp[idx][u];
                int vv = mp[idx][v];
                dj_set[idx].join(uu,vv);
            }
        }
    }
}

void solve() {
    int n;
    scanf("%d",&n);
    FOR(i,n-1) {
        int u,v;
        scanf("%d%d", &u,&v);
        u--;v--;
        G[u].pb(v);
        G[v].pb(u);
    }
    int q; scanf("%d",&q);
    FOR(i,q) {
        int l; scanf("%d", &l);
        dj_set.pb(dsu(l));
        FOR(j,l) {
            int x; scanf("%d", &x);
            x--;
            vals[x].insert(i);
            mp[i][x] = j;
        }
    }
    dfs(0,0);
    FOR(i,q) {
        cout<<dj_set[i].ans()<<endl;
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

