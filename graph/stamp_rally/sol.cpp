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


struct UF {
    vi par,sz;
    UF(int n=0) {
        par.resize(n);
        sz.assign(n,1);
        FOR(i,n) {
            par[i] = i;
        }
    }
    int find(int u) {
        if(par[u]==u) return u;
        return par[u] = find(par[u]);
    }
    bool join(int u, int v) {
        u = find(u); v = find(v);
        if(par[u]==par[v]) return false;
        if(sz[u] < sz[v]) swap(u,v);
        sz[u]+=sz[v];
        par[v] = u;
        return true;
    }
};

struct Query {
    int x, y, z;
    Query(int x=0, int y=0, int z=0) : x(x), y(y), z(z) {}
};

void solve() {
    int n,m; cin>>n>>m;
    vector<pii> edges(m);
    //read in all edges and store them
    for(pii& p: edges) cin>>p.f>>p.s;
    
    int q; cin>>q;
    vector<Query> Q(q);
    for(Query& q: Q) cin>>q.x>>q.y>>q.z;
    vector<pii> bs(q);
    vi ans(q, m);
    FOR(i,q) {
        bs[i].f = 1, bs[i].s = m;
    }
    FOR(i, log2(m)+1) {
        vector<vi> B(m+1);
        FOR(i,q) {
            int m = (bs[i].f+bs[i].s)/2;
            B[m].pb(i);
        }
        UF dsu(n+1);
        FOR(i,m) {
            dsu.join(edges[i].f, edges[i].s);
            for(int idx: B[i+1]) {
                int u = dsu.sz[dsu.find(Q[idx].x)];
                if(dsu.find(Q[idx].x)!=dsu.find(Q[idx].y)) {
                    u+=dsu.sz[dsu.find(Q[idx].y)];
                }
                if(u>=Q[idx].z) {
                    //able to do it 
                    bs[idx].s=i+1;
                    ans[idx]=i+1;
                }
                else {
                    //cannot do it
                    bs[idx].f=i+2;
                }
            }
        }
    }
    FOR(i,q) {
        cout<<bs[i].f<<endl;
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

