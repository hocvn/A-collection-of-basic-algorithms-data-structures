#include <iostream>
using namespace std;

#define N 60010
int n,m,bit[N],a[N];

void update(int x){

    for ( ; x <= m; x += x & -x) bit[x]++;
}
int get(int x){

    int ret = 0;
    for ( ; x > 0; x -= x & -x) ret += bit[x];
    return ret;
}
int main(){

    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n;
    for (int i = 1,x; i <= n; i++) cin >> a[i], m = max(m,a[i]);
    long long ans = 0;
    for (int i = n; i > 0; i--){
        ans += get(a[i]-1);
        update(a[i]);
    
    cout << ans;
    return 0;
}

