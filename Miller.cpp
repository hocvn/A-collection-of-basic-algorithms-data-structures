#include <iostream>
#define ll unsigned long long
using namespace std;

typedef pair <ll,ll> pp;
ll n;

ll power(ll a,ll d,ll n){

	ll result = 1;
    a = a % n;
    while (d > 0) {
        if (d & 1) result = result * a % n;
        d >>= 1;
        a = a * a % n;
    }
    return result;
}
pp factor(ll n){

	ll s = 0;
	while ((n&1) == 0){
		s++;  n >>= 1;
	}
	return pp(s,n);
}
bool check(ll s,ll d,ll n,ll a){

	if (n == a) return true;
	ll p = power(a,d,n);
	if (p == 1) return true;

	for (; s > 0; s--){
		if (p == n-1) return true;
		p = p * p % n;
	}
	return false;
}
bool miller(ll n){

	if (n < 2) return false;
	if ((n&1) == 0) return (n == 2);
	pp t = factor(n-1);
	return check(t.first,t.second,n,2) && check(t.first,t.second,n,7) && check(t.first,t.second,n,61);
}
int main(){

	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n;
	if (miller(n)) cout << "Nguyen to";
		else cout << "Khong nguyen to";
	return 0;
}

