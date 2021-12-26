#include <iostream>
#include <algorithm>

#define N 100010
#define ll long long
#define X first
#define Y second
typedef pair <ll,ll> ii;
ii a[N];
int n;

ll area(ii p1,ii p2,ii p3){

    return p1.X*(p3.Y-p2.Y) + p2.X*(p1.Y-p3.Y) + p3.X*(p2.Y-p1.Y);
}
int convexhull(){

    sort(a+1,a+n);
    pair <ll,ll> st[2][N];
    int d[2] = {0,0};

    for (int i = 1; i <= n; i++){
        while (d[0] > 1 && area(st[0][d[0]-1],st[0][d[0]],a[i]) <= 0) d[0]--;
        while (d[1] > 1 && area(st[1][d[1]-1],st[1][d[1]],a[i]) >= 0) d[1]--;
        st[0][++d[0]] = a[i];
        st[1][++d[1]] = a[i];
    }
    return d[0] + d[1] - 2;
}

int main(){

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i].X >> a[i].Y;
    cout << convexhull();
    return 0;
}
