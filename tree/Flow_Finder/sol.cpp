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
const int N = 3e5+5;
int n;
vi G[N];
ll A[N];
ll sum[N];
bool possible = true;
vi* M[N];

void dfs(int u) {
    if(G[u].size()==0) {
        //current node is a leaf
        if(A[u]==0) {
            M[u] = new vi();
            M[u]->pb(u);
        }
        else {
            sum[u] = A[u];
        }
    }
    int big = -1;
    int sz = 0;
    for(int v: G[u]) {
        dfs(v);
        sum[u] += sum[v];
        if(M[v] && (int)M[v]->size()>sz) {
            sz = M[v]->size();
            big = v;
        }
    }
    if(big!=-1) {
        M[u] = M[big];
        for(int v: G[u]) {
            if(v==big) continue;
            if(!M[v]) continue;
            for(int x: *M[v]) {
                M[u]->pb(x);
            }
        }
    }
    if(A[u]!=0 && M[u]) {
        ll left = A[u]-sum[u];
        if(M[u]->size()==0) {
            if(A[u]!=sum[u]) possible = false;
        }
        else if(M[u]->size()==1) {
            int node = M[u]->back();
            M[u]->pop_back();
            A[node] = A[u]-sum[u];
            if(A[node]<1) possible = false;
            sum[u] = A[u];
        }
        else if((int)M[u]->size()==left) {
            while(M[u]->size()) {
                int node = M[u]->back();
                M[u]->pop_back();
                A[node] = 1;
            }
            sum[u] = A[u];
        }
        else possible = false;
    }
}
bool verify(int u) {
    bool valid = true;
    sum[u] = 0;
    for(int v: G[u]) {
        valid &= verify(v);
        sum[u]+=sum[v];
    }
    if(A[u]==0) A[u] = sum[u];
    if(G[u].size()==0) sum[u] = A[u];
    if(G[u].size() && sum[u]!=A[u]) valid = false;
    return valid;
}


void solve() {
    cin>>n;
    FOR(i,n-1) { 
        int p; cin>>p;
        G[p].pb(i+2);
    }
    for(int i=1;i<=n;i++) cin>>A[i];
    memset(sum,0,sizeof(sum));
    dfs(1);
    if(M[1] && (int)M[1]->size()!=0) possible = false;
    if(possible) {
        //for(int i=1;i<=n;i++) cout<<A[i]<<endl;
       if(verify(1)) {
           for(int i=1;i<=n;i++) cout<<A[i]<<endl;
       }
       else {
           cout<<"impossible\n";
       }
    }
    else cout<<"impossible\n";
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

