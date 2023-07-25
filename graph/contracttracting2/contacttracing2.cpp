#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define vi vector<int>
#define pii pair<int,int>
#define pll pair<ll,ll>
#define vll vector<ll>
#define FOR(i,n) for(int i=0;i<n;i++)
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define f first
#define s second

const int MOD = (int)1e9+7;

struct edge{
    int u,v;
    edge(int u=0,int v=0) : u(u), v(v) {}
};
set<int> rechable;
int n,k,c;
void dfs(int u, int d, vector<vector<vector<edge>>>& G){
    if(d==k){
        rechable.insert(u);
    }
    for(edge v: G[d][u]){
        dfs(v.v,d+1,G); 
    }
}
int main()
{
    cin>>n>>k>>c;
    vector<vector<edge> > edges(k+1);
    vi lastday(n+1,0);
    FOR(i,c){
        int u,v,d;
        cin>>u>>v>>d;
        edges[d].pb(edge(u,v));
        lastday[u] = max(lastday[u],d);
        lastday[v] = max(lastday[v],d);
    }
    vector<vector<vector<edge>>> G(k+1,vector<vector<edge>>(n+1));
    for(int i=1;i<=k;i++){
        for(edge e: edges[i]){
            if(lastday[e.u]==i){
                cout<<i-1<<" "<<e.u<<" "<<e.v<<endl;
                G[i-1][e.u].pb(edge(i,e.v));    
            }
            if(lastday[e.v]==i){
                cout<<i-1<<" "<<e.v<<" "<<e.u<<endl;
                G[i-1][e.v].pb(edge(i,e.u));    
            }
        }
    }
    for(int i=1;i<=n;i++){
        dfs(i,0,G);
    }
    cout<<sz(rechable)<<endl;
    for(int x: rechable) cout<<x<<endl;


    return 0;
}

