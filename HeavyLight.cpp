// https://oj.vnoi.info/problem/lubenica

#include <iostream>
#include <vector>
using namespace std;

#define N 100010
vector <pair <int,int>> a[N];
int par[N],head[N],lab[N],child[N],dep[N],pos[N],w[N],b[N];
int n,nchain;
pair <int,int> st[4*N];

void enter(){

    cin >> n;
    for (int i = 1,x,y,w; i < n; i++){
        cin >> x >> y >> w;
        a[x].push_back({y,w});
        a[y].push_back({x,w});
    }
}
void DFS(int u,int p){

    par[u] = p;
    dep[u] = dep[p] + 1;
    for (int i = 0; i < a[u].size(); i++){
        int v = a[u][i].first;
        if (v != p){
            DFS(v,u);
            w[v] = a[u][i].second;
            if (a[u][0].first == p || child[v] > child[a[u][0].first]) swap(a[u][0],a[u][i]);
            child[u] += child[v]+1;
        }
    }
}
void HLD(int u,int p){

    if (!head[nchain]) head[nchain] = u;
    pos[u] = ++pos[0];
    b[pos[u]] = w[u];
    lab[u] = nchain;
    if (a[u][0].first != p) HLD(a[u][0].first,u);
    for (int i = 1; i < a[u].size(); i++){
        if (a[u][i].first != p) nchain++, HLD(a[u][i].first,u);
    }
}
pair <int,int> com(pair <int,int> P,pair <int,int> Q){

    return make_pair(max(P.first,Q.first), min(P.second,Q.second));
}
void build(int id,int l,int r){

    st[id] = {b[l],b[l]};
    if (l == 1) st[id] = make_pair(0,1e9);
    if (l == r) return;
    int m = (l+r) >> 1;
    build(id*2,l,m);
    build(id*2+1,m+1,r);
    st[id] = com(st[id*2],st[id*2+1]);
}
pair <int,int> getST(int id,int l,int r,int x,int y){

    if (l > y || r < x) return make_pair(0,1e9);
    if (x <= l && r <= y) return st[id];
    int m = (l+r) >> 1;
    return com(getST(id*2,l,m,x,y), getST(id*2+1,m+1,r,x,y));
}
pair <int,int> get(int x,int y){

    pair <int,int> ret = {0,1e9};
    while (lab[x] != lab[y]){
        if (lab[x] > lab[y]) swap(x,y);
        int hy = head[lab[y]];
        pair <int,int> tmp = getST(1,1,n,pos[hy],pos[y]);
        ret = com(ret,tmp);
        y = par[hy];
    }
    if (x != y){
        if (pos[x] > pos[y]) swap(x,y);
        pair <int,int> tmp = getST(1,1,n,pos[x]+1,pos[y]);
        ret = com(ret,tmp);
    }
    return ret;
}
void solve(){

    int q; cin >> q;
    while (q--){
        int x,y; cin >> x >> y;
        pair <int,int> ans = get(x,y);
        cout << ans.second << ' ' << ans.first << '\n';
    }
}
int main(){

    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    enter();
    DFS(1,0);
    HLD(1,0);
    build(1,1,n);
    solve();
    return 0;
}
