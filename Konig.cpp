#include <iostream>
#include <vector>
using namespace std;

#define N 100010
vector <int> a[N];
int n,m,k,match[N],dau[N];
bool dx[N],dy[N];

void read(int &x){

	x = 0;
	register int c = getchar();
	while (!isdigit(c)) c = getchar();
	for (; isdigit(c); c = getchar())
		x = (x<<1) + (x<<3) + c - 48;
}
void enter(){

	read(n); read(m); read(k);
	for (int i = 1; i <= k; i++){
		int x,y;
		read(x); read(y);
		a[x].emplace_back(y);
	}
}
bool visit(int u,int &key){

	if (dau[u] != key) dau[u] = key;
		else return false;

	for (int v : a[u]){
		if (!match[v] || visit(match[v],key)){
			match[v] = u;
			return true;
		}
	}
	return false;
}
void hungary(){

	int key = 0, cnt = 0;
	for (int i = 1; i <= n; i++){
		if (!a[i].empty()) cnt += visit(i,++key);
	}
}
void mark(int u){

	if (dx[u]) return;
	dx[u] = true;
	for (int v : a[u]){
		if (match[v] && !dy[v]){
			dy[v] = true;
			mark(match[v]);
		}
	}
}
void konig(){

	fill(dau,dau+N,0);
	for (int i = 1; i <= m; i++)
		dau[match[i]] = 1;
	for (int i = 1; i <= n; i++){
		if (!dau[i]) mark(i);
	}

	int row = 0, column = 0;
	for (int i = 1; i <= n; i++) row += (dx[i] == false);
	for (int i = 1; i <= m; i++) column += dy[i];

	cout << row << ' ' << column << '\n';
	for (int i = 1; i <= n; i++)
		if (!dx[i]) cout << i << ' ';
	for (int i = 1; i <= m; i++)
		if (dy[i]) cout << i << ' ';
}
int main(){

	enter();
	hungary();
	konig();
	return 0;
}

