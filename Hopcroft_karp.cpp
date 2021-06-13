#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define N 100010
#define inf 10000000
vector <int> a[N];
int n,m,p,match[N],d[N];

bool BFS(){

	queue <int> q;
	for (int i = 1; i <= n; i++){
		if (!match[i]) q.push(i), d[i] = 0;
			else d[i] = inf;
	}
	d[0] = inf;
	while (!q.empty()){
		int u = q.front();
		q.pop();
		if (!u) continue;
		for (int v : a[u]){
			if (d[match[v]] == inf){
				d[match[v]] = d[u] + 1;
				q.push(match[v]);
			}
		}
	}
	return d[0] != inf;
}
bool DFS(int u){

	if (!u) return true;
	for (int v : a[u]){
		if (d[match[v]] == d[u] + 1 && DFS(match[v])){
			match[v] = u;
			match[u] = v;
			return true;
		}
	}
	d[u] = inf;
	return false;
}
void hopcroft_karp(){

	int cnt = 0;
	while (BFS()){
		for (int i = 1; i <= m; i++){
			if (!match[i]) cnt += DFS(i);
		}
	}
	cout << cnt;
}
int main(){

	cin >> n >> m >> p;
	for (int i = 1; i <= p; i++){
		int x,y; cin >> x >> y;
		a[x].push_back(y+n);
		a[y+n].push_back(x);
	}
	hopcroft_karp();
	return 0;
}

