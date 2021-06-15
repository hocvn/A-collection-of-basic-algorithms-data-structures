#include <iostream>
#include <cstring>
using namespace std;

#define N 100010
string s;
int z[N],n;

int main(){

	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> s;
	n = s.size();
	int l = 0, r = 0;

	for (int i = 1; i < n; i++){
		if (i <= r) z[i] = min(r-i+1,z[i-l]);
		while (i + z[i] < n && s[z[i]] == s[z[i]+i]) z[i]++;
		if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
	}
	for (int i = 0; i < n; i++) cout << z[i] << ' ';
	return 0;
}

