// Minimum sum distances from 3 points
// Complexity O(n*log(n))

#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;

#define ld long double
#define ll long long
#define X first
#define Y second

const ll inf = 9e18;
const int N = 500050;
typedef pair <ll,ll> pll;

pll a[N];
int n,t;
ld res;

ll dist(pll p,pll q){

	return (p.X-q.X)*(p.X-q.X) + (p.Y-q.Y)*(p.Y-q.Y);
}

ld perimeter(pll x,pll y,pll z){

	return sqrt(dist(x,y)) + sqrt(dist(y,z)) + sqrt(dist(x,z));
}
bool cmpY(pll p, pll q){ return p.Y < q.Y; }

void process(int l,int r){

	if (r <= l) return;
	if (l == r-1){
		if (!cmpY(a[l],a[r])) swap(a[l],a[r]);
		return;
	}
	int m = (l+r) >> 1;
	ll midx = a[m].X;
	process(l,m);
	process(m+1,r);

	int cnt = 0;
	static pll t[N];
	merge(a+l,a+m+1,a+m+1,a+r+1,t,cmpY);
	copy(t,t+r-l+1,a+l);

	for (int i = l; i <= r; i++){
		if (abs(a[i].X-midx) < res/2){
			for (int j = cnt; j > 0 && abs(a[i].Y-t[j].Y) < res/2; j--){
				for (int k = j-1; k > 0 && abs(a[i].Y-t[k].Y) < res/2; k--){
					res = min(res,perimeter(a[i],t[j],t[k]));
				}
			}
			t[++cnt] = a[i];
		}
	}
}
void solve(){

	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> a[i].first >> a[i].second;
	}
	res = inf;
	sort(a+1,a+n+1);
	process(1,n);
	cout << fixed << setprecision(6) << res << '\n';
}
int main(){

	freopen("FACTORIES.inp","r",stdin);
	freopen("FACTORIES.out","w",stdout);
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> t;
	while (t--) solve();
	return 0;
}

