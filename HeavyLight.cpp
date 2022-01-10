//https://oj.vnoi.info/problem/qtree3
#include <iostream>
#include <vector>
using namespace std;

#define N 100010
const int inf = 1e9;

vector <int> a[N];
int head[N],label[N],child[N],dep[N],par[N];
int st[4*N],heavy[N],pos[N],b[N];
int n,q,nchain,cnt;

void enter(){

    cin >> n >> q;
    for (int i = 1; i < n; i++){
        int x,y;
        cin >> x >> y;
        a[x].push_back(y);
        a[y].push_back(x);
    }
}
void DFS(int u,int parent){

	par[u] = parent;
    dep[u] = dep[parent] + 1;
    for (int v : a[u]){
		if (v == parent) continue;
        DFS(v,u);
        if (!heavy[u] || child[v] > child[heavy[u]]) heavy[u] = v;
        child[u] += child[v]+1;
    }
}
void hld(int u,int parent){

    if (head[nchain] == 0) head[nchain] = u;
    label[u] = nchain;
    pos[u] = ++cnt;
    b[cnt] = u;

    if (!heavy[u]) return;
    hld(heavy[u],u);

    for (int v : a[u])
		if (v != heavy[u] && v != parent) nchain++,hld(v,u);
}
void build(int id,int l,int r){

    if (l == r){
        st[id] = inf;
        return;
    }
    int m = (l+r) >> 1;
    build(id*2,l,m);
    build(id*2+1,m+1,r);
    st[id] = inf;
}
void update_st(int id,int l,int r,int p){

    if (l > p || r < p) return;
    if (l == r){
		if (st[id] == inf) st[id] = l;
			else st[id] = inf;
        return;
    }
    int m = (l+r) >> 1;
    update_st(id*2,l,m,p);
    update_st(id*2+1,m+1,r,p);
    st[id] = min(st[id*2],st[id*2+1]);
}
int get_st(int id,int l,int r,int x,int y){

    if (l > y || r < x) return inf;
    if (x <= l && r <= y) return st[id];
    int m = (l+r) >> 1;
    return min(get_st(id*2,l,m,x,y), get_st(id*2+1,m+1,r,x,y));
}
int get(int x){

    int y = 1, res = inf;
    for (;label[x] != label[y]; y = par[head[label[y]]]){
        if (label[x] > label[y]) swap(x,y);
        res = min(res,get_st(1,1,n,pos[head[label[y]]],pos[y]));
    }
    if (child[x] < child[y]) swap(x,y);
    return min(res,get_st(1,1,n,pos[x],pos[y]));
}
int main(){

    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    enter();
    DFS(1,0);
    hld(1,0);
    build(1,1,n);
    while (q--){
        int x,y; cin >> x >> y;
        if (x){
            int p = get(y);
            if (p == inf) cout << -1 << '\n';
                else cout << b[p] << '\n';
        }
        else update_st(1,1,n,pos[y]);
    }
    return 0;
}
