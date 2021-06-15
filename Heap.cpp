#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int N = 100010;
int n,x,a[N],sz;

void heapify_push(int i){

	if (i <= 1) return;
	int par = i/2;
	if (a[par] > a[i]){
		swap(a[par],a[i]);
		heapify_push(par);
	}
}
void heapify_pop(int i){

	int largest = i;
	int l = i*2, r = l+1;

	if (l <= sz && a[largest] > a[l]) largest = l;
	if (r <= sz && a[largest] > a[r]) largest = r;

	if (largest != i){
		swap(a[largest], a[i]);
		heapify_pop(largest);
	}
}
void push(int y){

	a[++sz] = y;
	heapify_push(sz);
}
void pop(){

	a[1] = a[sz];
	sz--;
	heapify_pop(1);
}
int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);  cout.tie(0);

	cin >> n;
    while (n--){
        cin >> x;
        push(x);
    }
    vector <int> ans;
    while (sz){
    	cout << a[1] << " ";
        pop();
    }
    return 0;
}

