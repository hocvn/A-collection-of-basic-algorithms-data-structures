#include <iostream>
using namespace std;

#define N 100010
#define ll long long
ll st[N*4],lazy[N*4],a[N];
int n,q;

void build(int id,int l,int r){

	if (l == r){
		st[id] = a[l];
		return;
	}
	int m = (l+r) >> 1;
	build(id*2,l,m);
	build(id*2+1,m+1,r);

	st[id] = st[id*2] + st[id*2+1];
}
void down(int id,int l,int r,int m){

	lazy[id*2] += lazy[id];
	lazy[id*2+1] += lazy[id];

	st[id*2] += lazy[id] * (m-l+1);
	st[id*2+1] += lazy[id] * (r-m);

	lazy[id] = 0;
}
void update(int id,int l,int r,int x,int y,ll val){

	if (l > y || r < x) return;
	if (x <= l && r <= y){
		lazy[id] += val;
		st[id] += val*(r-l+1);
		return;
	}
	int m = (l+r) >> 1;
	down(id,l,r,m);

	update(id*2,l,m,x,y,val);
	update(id*2+1,m+1,r,x,y,val);

	st[id] = st[id*2] + st[id*2+1];
}
ll get(int id,int l,int r,int x,int y){

	if (l > y || r < x) return 0;
	if (x <= l && r <= y) return st[id];
	int m = (l+r) >> 1;
	down(id,l,r,m);
	return get(id*2,l,m,x,y) + get(id*2+1,m+1,r,x,y);
}
int main(){

	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> q;
	for (int i = 1; i <= n; i++) cin >> a[i];
	build(1,1,n);

	for (int i = 1; i <= q; i++){
		int type,x,y;
		ll w;
		cin >> type;
		if (type == 1){
			cin >> x >> y >> w;
			update(1,1,n,x,y,w);
		}
		else{
			cin >> x >> y;
			cout << get(1,1,n,x,y) << '\n';
		}
	}
	return 0;
}

