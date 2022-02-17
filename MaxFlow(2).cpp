// Ford–Fulkerson using Priority First Search

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define ll long long
#define N 120002
const ll inf = 1e16;

vector <pair <int,int>> a[1202];
pair <int,int> edge[N*2];
int n,m,s,t,trace[1202];
ll d[1202],c[N*2],f[N*2];

void enter(){

    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n >> m >> s >> t;
    for (int i = 1,x,y; i <= m; i++){
        cin >> x >> y >> c[i];
        edge[i] = {x,y};
        a[x].push_back({y,i});
        a[y].push_back({x,-i});
    }
}
bool FindPath(){

    fill(d,d+n+1,0);
    fill(trace,trace+n+1,0);
    priority_queue <pair <ll,int>> q;
    q.push({d[s] = inf,s});

    while (!q.empty()){
        int u = q.top().second;
        ll du = q.top().first;
        q.pop();
        if (d[u] != du) continue;
        for (pair <int,int> T : a[u]){
            int v = T.first, e = T.second;
            if (!trace[v]){
                if (e < 0 && d[v] < min(d[u],f[-e])){
                    d[v] = min(d[u],f[-e]);
                    q.push({d[v],v});
                    trace[v] = e;
                }
                else if (e > 0 && d[v] < min(d[u],c[e] - f[e])){
                    d[v] = min(d[u],c[e] - f[e]);
                    q.push({d[v],v});
                    trace[v] = e;
                }
            }
        }
    }
    return d[t] > 0;
}
void solve(){

    ll ans = 0;
    while (FindPath()){
        int v = t;
        ans += d[t];
        while (v != s){
            int e = trace[v],u;
            if (e > 0) u = edge[e].first;
                else u = edge[-e].second;
            if (e > 0) f[e] += d[t]; else f[-e] -= d[t];
            v = u;
        }
    }
    cout << ans;
}
int main(){

    enter();
    solve();
}

