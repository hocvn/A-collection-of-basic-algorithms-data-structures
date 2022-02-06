#include <iostream>
#include <vector>
using namespace std;

#define logN 20
#define N 200010
vector <int> a[N];
int dep[N],d[N],f[N][logN],n,m,ans;

void read(int &x){

    register int c = getchar();
    x = 0;
    while (!isdigit(c)) c = getchar();
    for ( ; isdigit(c); c = getchar()) x = (x<<1) + (x<<3) + c - '0';
}
void enter(){

    read(n);
    for (int i = 1,x,y; i < n; i++){
        read(x); read(y);
        a[x].emplace_back(y);
        a[y].emplace_back(x);
    }
    for (int i = 1; i <= n; i++){
        for (int j = 0; j < logN; j++) f[i][j] = -1;
    }
}
void dfs(int u,int p){

    for (int i = 1; i < logN; i++){
        if (f[u][i-1] != -1) f[u][i] = f[f[u][i-1]][i-1];
    }
    for (int v : a[u]) if (v != p){
        f[v][0] = u;
        dep[v] = dep[u] + 1;
        dfs(v,u);
    }
}
int lca(int u,int v){

    if (dep[u] < dep[v]) swap(u,v);

    for (int i = logN-1; i >= 0; i--){
        if (f[u][i] != -1 && dep[f[u][i]] >= dep[v]) u = f[u][i];
    }
    if (u == v) return u;

    for (int i = logN-1; i >= 0; i--){
        if (f[v][i] != -1 && f[u][i] != f[v][i]){
            u = f[u][i];
            v = f[v][i];
        }
    }
    return f[u][0];
}
void visit(int u,int p){

    for (int v : a[u]) if (v != p){
        visit(v,u);
        d[u] += d[v];
        if (!d[v]) ans++;
    }
}
void solve(){

    read(m);
    while (m--){
        int x,y; read(x); read(y);
        int p = lca(x,y);
        d[x]++, d[y]++;
        d[p] -= 2;
    }
    visit(1,1);
    cout << ans;
}
int main(){

    enter();
    dfs(1,1);
    solve();
}

