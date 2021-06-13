#include <iostream>
#include <vector>
using namespace std;

#define sz(a) (int)a.size()
#define ll long long
const ll base = 1e8;
typedef vector <ll> bignum;

void read(bignum &x){

	string s;
	cin >> s;
	if (sz(s) == 0) { x.push_back(0); return; }
	while (sz(s) % 8) s = '0' + s;
	ll y = 0, cnt = 0;
	for (int i = 0; i < sz(s); i++){
		cnt++;
		y = y*10 + (s[i]-'0');
		if (cnt == 8) x.insert(x.begin(),y), cnt = y = 0;
	}
	if (y > 0) x.insert(x.begin(),y);
}
bignum operator + (bignum a, bignum b){

	ll carry = 0;
	bignum c;
	for (int i = 0; i < sz(a) || i < sz(b); i++){
		if (i < sz(a)) carry += a[i];
		if (i < sz(b)) carry += b[i];
		c.push_back(carry % base);
		carry /= base;
	}
	if (carry) c.push_back(carry);
	return c;
}
bignum operator - (bignum a, bignum b){

	bignum c;
	ll carry = 0;
	for (int i = 0; i < sz(a); i++){
		ll s = a[i] - carry;
		if (i < sz(b)) s -= b[i];
		if (s < 0) s += base, carry = 1;
			else carry = 0;
		c.push_back(s);
	}
	while (*c.rbegin() == 0 && sz(c) > 1) c.pop_back();
	return c;
}
bignum operator * (bignum a, bignum b){

	ll carry = 0;
	bignum c(sz(a) + sz(b) + 16,0);

	for (int i = 0; i < sz(a); i++){
		carry = 0;
		for (int j = 0; j < sz(b); j++){
			int k = i + j;
			c[k] += a[i]*b[j] + carry;
			carry = c[k] / base;
			c[k] %= base;
		}
		if (carry) c[i + b.size()] += carry;
	}
	while (*c.rbegin() == 0 && sz(c) > 1) c.pop_back();
	return c;
}
bool operator < (bignum a, bignum b){

	while (sz(a) && *a.rbegin() == 0) a.pop_back();
    while (sz(b) && *b.rbegin() == 0) b.pop_back();
	if (sz(a) != sz(b)) return sz(a) < sz(b);

	for (int i = sz(a)-1; i >= 0; i--)
		if (a[i] != b[i]) return a[i] < b[i];
	return false;
}
void print(bignum ans){

	if (ans.empty()){ printf("0\n"); return; }
	printf("%lld",ans.back());
	for (int i = sz(ans)-2; i >= 0; i--) printf("%.08lld",ans[i]);
	putchar('\n');
}
int main(){

	bignum a,b;
	read(a); read(b);

	print(a+b);
	if (a < b) putchar('-'), print(b-a);
		else print(a-b);
	print(a*b);
	return 0;
}

