#include <iostream>
#include <queue>
using namespace std;

#define N 1010
int a[N][N],f[N][N],trace[N];
int n,m,s,t,ans;

int find_path(){

    fill(trace,trace + N,0);
    trace[s] = -1;
    queue <pair <int,int>> q;
    q.push({s,1e9});

    while (!q.empty()){
        int i = q.front().first;
        int flow = q.front().second;
        q.pop();
        for (int j = 1; j <= n; j++) if (a[i][j] > 0){
            if (!trace[j] && a[i][j] > f[i][j]){
                trace[j] = i;
                int nflow = min(flow,a[i][j] - f[i][j]);
                if (j == t) return nflow;
                q.push({j,nflow});
            }
        }
    }
    return 0;
}
int main(){

    scanf("%d%d%d%d",&n,&m,&s,&t);
    for (int i = 1,x,y,w; i <= m; i++){
        scanf("%d%d%d",&x,&y,&w);
        a[x][y] = a[y][x] = w;
    }
    int tmp;
    while (tmp = find_path()){
        ans += tmp;
        int v = t;
        while (v != s){
            int u = trace[v];
            f[u][v] += tmp;
            f[v][u] -= tmp;
            v = u;
        }
    }
    printf("%d",ans);
    return 0;
}

