#include <iostream>
using namespace std;

#define N 100010
#define ll long long
ll st[N * 4], a[N];
int n, q;

void build(int id = 1, int l = 1, int r = n) {

	if (l == r) {
		st[id] = a[l];
		return;
	}
	int m = (l + r) >> 1;
	build(id * 2, l, m);
	build(id * 2 + 1, m + 1, r);

	st[id] = st[id * 2] + st[id * 2 + 1];
}
void update(int pos, ll val, int id = 1, int l = 1, int r = n) {

	if (l > pos || r < pos) return;
	if (l == r) {
		st[id] = val;
		return;
	}
	int m = (l + r) >> 1;
	update(pos, val, id * 2, l, m);
	update(pos, val, id * 2 + 1, m + 1, r);

	st[id] = st[id * 2] + st[id * 2 + 1];
}
ll get(int x, int y, int id = 1, int l = 1, int r = n) {

	if (l > y || r < x) return 0;
	if (x <= l && r <= y) return st[id];
	int m = (l + r) >> 1;
	return get(x, y, id * 2, l, m) + get(x, y, id * 2 + 1, m + 1, r);
}
int main() {

	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> q;
	for (int i = 1; i <= n; i++) cin >> a[i];

	build();

	for (int i = 1; i <= q; i++) {
		int type, x, y;
		ll w;
		cin >> type;

		if (type == 1) {
			cin >> x >> w;
			update(x, w);
		}
		else {
			cin >> x >> y;
			cout << get(x, y) << '\n';
		}
	}
	return 0;
}
