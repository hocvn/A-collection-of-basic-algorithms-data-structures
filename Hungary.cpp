// Find minimum weighted Bipartite graph

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define N 1010
int matchX[N],matchY[N],c[N][N];
int n,m,fx[N],fy[N],trace[N];
bool dx[N],dy[N],a[N][N];

void enter(){

	cin >> n;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) c[i][j] = 8e8;
	int x,y,w;
	while (cin >> x >> y >> w) c[x][y] = w, a[x][y] = true;
}
int cost(int i,int j){

	return c[i][j] - fx[i] - fy[j];
}
int find_path(int s){

	for (int i = 1; i <= n; i++){
		dx[i] = dy[i] = false;
		trace[i] = 0;
	}
	queue <int> q;
	q.push(s);

	while (!q.empty()){
		int u = q.front();
		dx[u] = true;
		q.pop();
		for (int v = 1; v <= n; v++){
			if (!a[u][v]) continue;
			if (!trace[v]){
				if (!cost(u,v)){
					trace[v] = u;
					if (!matchY[v]) return v;
					q.push(matchY[v]);
				}
			}
			else dy[v] = true;
		}
	}
	return 0;
}
void update(){

	int delta = 8e8;
	for (int i = 1; i <= n; i++){
		if (!dx[i]) continue;
		for (int j = 1; j <= n; j++){
			if (!dy[j]) delta = min(delta,cost(i,j));
		}
	}
	for (int i = 1; i <= n; i++)
		if (dx[i]) fx[i] += delta;
	for (int i = 1; i <= n; i++)
		if (dy[i]) fy[i] -= delta;

	for (int i = 1; i <= n; i++)
		dx[i] = dy[i] = false;
}
void enlarge(int finish){

	for (int y = finish, Next; y ; y = Next){
		int x = trace[y];
		Next = matchX[x];
		matchX[x] = y;
		matchY[y] = x;
	}
}
void hungary(){

	for (int i = 1; i <= n; i++){
		int finish;
		do{
			finish = find_path(i);
			if (!finish) update();
		} while (!finish);
		enlarge(finish);
	}
}
void print(){

	int res = 0;
	for (int i = 1; i <= n; i++)
		if (matchX[i]) res += c[i][matchX[i]];
	cout << res << '\n';
	for (int i = 1; i <= n; i++)
		if (matchX[i]) cout << i << ' ' << matchX[i] << '\n';
}
int main(){

	enter();
	hungary();
	print();
	return 0;
}

