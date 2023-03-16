// https://oj.vnoi.info/problem/ioibin

#include <iostream>
using namespace std;

#define N 10010
int par[N],d[N];

int root(int x){

    return x == par[x] ? x : par[x] = root(par[x]);
}
void join(int x,int y){

    int u = root(x), v = root(y);
    if (u == v) return;
    if (d[u] < d[v]) swap(u,v);
    d[u] += d[v];
    par[v] = u;
}
int main(){

    for (int i = 1; i <= 10000; i++){
      par[i] = i;
    }
  
    int q; cin >> q;
  
    while (q--){
        int type,x,y;
        cin >> x >> y >> type;
        if (type == 1) join(x,y);
        else cout << (root(x) == root(y)) << '\n';
    }
    return 0;
}
