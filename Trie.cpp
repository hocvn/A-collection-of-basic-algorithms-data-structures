#include <iostream>
#include <cstring>
using namespace std;

struct trie{

	int num;
	trie *link[26];
	trie(){
		for (int i = 0; i < 26; i++)
			link[i] = NULL;
		num = 0;
	}
};
trie *root = new trie();

void Insert(char *s){

	trie *p = root;
	for (int i = 0; i < (int)strlen(s); i++){
		if (p->link[s[i]-'a'] == NULL) p->link[s[i]-'a'] = new trie();
		p = p->link[s[i]-'a'];
	}
	p->num++;
}
bool Find(char *s){

	trie *p = root;
	for (int i = 0; i < (int)strlen(s); i++){
		if (p->link[s[i]-'a'] == NULL) return false;
		p = p->link[s[i]-'a'];
	}
	return p->num > 0;
}
void Delete(char *s){

	trie *p = root;
	for (int i = 0; i < (int)strlen(s); i++){
		if (p->link[s[i]-'a'] == NULL) return;
		p = p->link[s[i]-'a'];
	}
	p->num--;
}
int main(){

	char s[100],t[100];
	cin >> s >> t;
	Insert(s);
	if (Find(t)) cout << "yes";
		else cout << "no";
	return 0;
}

