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


template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
};
typedef Point<double> P;
vector<P> convexHull(vector<P> pts) {
	if (sz(pts) <= 1) return pts;
	sort(all(pts));
	vector<P> h(sz(pts)+1);
	int s = 0, t = 0;
	for (int it = 2; it--; s = --t, reverse(all(pts)))
		for (P p : pts) {
			while (t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) t--;
			h[t++] = p;
		}
	return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

double eps = 1e-9;

long double binarySearch(P a, P b) {
    auto F = [&](long double x) {
        long double y = (x-a.x)*((b.y-a.y)/(b.x-a.x))+a.y;
        return x*y;
    };
    long double l = min(a.x,b.x), r = max(a.x,b.x);
    long double ans = 0;
    while(r-l>=eps){
        long double m = (l+r)/2.0;
        ans = max(ans,F(m));
        if(F(m) < F(m+eps)) {
            l = m;     
        }
        else r = m;
    }
    return ans;
}

void solve() {
    int n,b; cin>>n>>b;
    vector<P> pts;
    FOR(i,n) {
        double c,h,p;
        cin>>c>>h>>p;
        pts.pb(P(h/c,p/c));
    }
    pts = convexHull(pts);
    long double ans = 0;
    FOR(i,(int)pts.size()) {
        long double val = binarySearch(pts[i], pts[(i+1)%pts.size()]);
        ans = max(ans,val);
    }
    printf("%.7Lf\n", ans*b*b);
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

