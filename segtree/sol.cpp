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

const int N = 3e5+1;
int A[N];
int B[N];
string S;
int dp[N][2];
struct Tree {
	typedef int T;
	static constexpr T unit = INT_MIN;
	T f(T a, T b) { return max(a, b); } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};
Tree* st[2];
int dp2[N];
void solve() {
    int n; cin>>n;
    FOR(i,n) cin>>A[i];
    cin>>S;
    FOR(i,n-1) B[i] = S[i]=='U';
    int best = 1;
    for(int i=0;i<2;i++) st[i] = new Tree(n+1);
    for(int i=0;i<2;i++) for(int k=0;k<=n;k++) st[i]->update(k,0);
    dp[0][B[0]] = 1;
    for(int i=0;i<n;i++) {
        dp2[i] = 1+max(st[0]->query(A[i],n+1), st[1]->query(0,A[i]));
        int b = B[dp2[i]-1];
        st[b]->update(A[i], dp2[i]);
        best = max(best, dp2[i]);
    }
    cout<<best-1<<endl;
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

