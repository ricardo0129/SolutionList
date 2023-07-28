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
    int n,m; cin>>n>>m;
    vector<pii> A;
    FOR(i,n) {
        int a, b;
        cin>>a>>b;
        A.pb(make_pair(a,b));
    }
    sort(A.begin(), A.end(),[](pii& a, pii& b){
            if(a.f==b.f) return a.s>b.s;
            return a.f<b.f;
    });
    vector<pii> merged;
    int l = A[0].f, r = A[0].s;
    for(int i=0;i<n;i++) {
        if(l<=A[i].f && A[i].f<=r) {
            r = max(r, A[i].s);
        }
        else if(A[i].f == r+1) {
            r = max(r, A[i].s);
        }
        else {
            merged.pb(make_pair(l,r));
            l = A[i].f, r = A[i].s;
        }
    }
    merged.pb(make_pair(l,r));
    int k = merged.size();
    int first_missing = 0;
    int last_missing = 0;
    if(merged[0].f>1) first_missing = 1;
    else first_missing = merged[0].s+1;
    if(merged[k-1].s<m) last_missing = m;
    else last_missing = merged[k-1].f-1;
    int ans = 0;
    if(first_missing<=last_missing) ans = last_missing-first_missing+1;
    cout<<ans<<endl;
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

