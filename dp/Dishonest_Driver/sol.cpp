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

const ll MOD = 1e9+7;
const ll P = 71;
const int N = 701;
string A;
ll powers[N];
ll inv[N];
ll H[N];
int n;
ll binpow(ll a, ll b) {
    if(b==0) return 1;
    if(b==1) return a;
    ll x = binpow(a, b/2)%MOD;
    x = (x*x)%MOD;
    if(b%2) x = (x*a) % MOD;
    return x;
}
map<char,int> val;
void precompute() {
    powers[0] = inv[0] = 1;
    for(int i=1;i<=n;i++) powers[i] = (powers[i-1] * P) % MOD;
    for(int i=1;i<=n;i++) inv[i] = binpow(powers[i], MOD-2);
    H[0] = val[A[0]];
    for(int i=1;i<n;i++) {
        ll v = (powers[i] * val[A[i]])%MOD;
        H[i] = (H[i-1] + v)%MOD;
    }
}
ll hs(int i, int j) {
    //compute substring hash in O(1)
    ll v = H[j]; 
    if(i!=0) v = ((v-H[i-1])%MOD+MOD)%MOD;
    v = (v * inv[i])%MOD;
    return v;
}

bool compare(int i, int j, int k, int l) {
    //compare string A[i..j] ==? A[k..l];
    return hs(i,j) == hs(k,l);
}
typedef bitset<N> bs;
bs able[N][N];
int dp[N][N];
void solve() {
    cin>>n;
    cin>>A;
    for(char c='0';c<='9';c++) val[c] = sz(val);
    for(char c='a';c<='z';c++) val[c] = sz(val);
    for(char c='A';c<='Z';c++) val[c] = sz(val);
    precompute();
    for(int i=0;i<n;i++) {
        for(int j=1;j<=n;j++) {
            for(int k=1;i+j*k<n;k++) {
                //can we copy substring A[i..i+j-1] k times 
                able[i][j][k] = compare(i,i+j-1,i+j*k,i+j*(k+1)-1);
                if(!able[i][j][k]) {
                    break;
                }
            }
        }
    }
    for(int i=0;i<n;i++) dp[i][i] = 1;
    for(int len=2;len<=n;len++) {
        for(int i=0;i<n;i++) {
            int j = i+len-1;
            dp[i][j] = MOD;
            //a power operation
            for(int k=1;k*k<=len;k++) {
                if(len%k!=0) continue;
                if(able[i][k][len/k-1]) {
                    dp[i][j] = min(dp[i][j], dp[i][i+k-1]);
                }
                int l = len/k;
                if(able[i][l][len/l-1]) {
                    dp[i][j] = min(dp[i][j], dp[i][i+l-1]);
                }

            }
            //a combine operation
            for(int k=i;k<j;k++) {
                dp[i][j] = min(dp[i][j], dp[i][k]+dp[k+1][j]);
            }
        }
    }
    cout<<dp[0][n-1]<<endl;

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

