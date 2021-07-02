#include <iostream>
using namespace std;

#define ll long long
#define N 1010
ll bit[N][N];
int n,q;
void update(int x,int y,ll val);
void enter(){

	cin >> n;
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			ll x; cin >> x;
			update(i,j,x);
		}
	}
}
void update(int x,int y,ll val){

	for (; x <= n; x += (x & -x)){
		for (int i = y ; i <= n; i += (i & -i)){
			bit[x][i] += val;
		}
	}
}
ll get(int x,int y){

	ll sum = 0;
	for (; x > 0; x -= (x & -x)){
		for (int i = y; i > 0; i -= (i & -i)){
			sum += bit[x][i];
		}
	}
	return sum;
}
ll query(int x,int y,int u,int v){

	return get(u,v) - get(u,y-1) - get(x-1,v) + get(x-1,y-1);
}
int main(){

	freopen("SUMTABLE.inp","r",stdin);
	freopen("SUMTABLE.out","w",stdout);
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	enter();
	int type,x,y,u,v;
	ll w;
	cin >> q;
	while (q--){
		cin >> type;
		if (type == 1){
			cin >> x >> y >> w;
			update(x,y,w);
		}
		else{
			cin >> x >> y >> u >> v;
			cout << query(x,y,u,v) << '\n';
		}
	}
	return 0;
}

