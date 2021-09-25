#include<iostream>
#include<algorithm>
#include<queue>
#include<map>
using namespace std;
typedef struct node *trie;
typedef unsigned long long num;
struct node{
	trie pre,next[10];
	bool end;
	static int cnt;
} mem[500];
int node::cnt = 1;
void insert(num x){
	static int digit[32],len;
	for(len = 0;x > 0;x/=10)digit[len ++ ] = x % 10;
	reverse(digit,digit + len);
	trie t = mem;
	for(int i=0;i<len;++i){
		int c = digit[i];
		if( !t->next[c])
			t->next[c] = & mem[node::cnt ++];
		t = t->next[c];
	}
	t -> end = true;
}
void build(){
	trie t= mem;
	queue<trie> q;
	for(int i=0;i<10;++i)
	if(t->next[i]){
		t->next[i]->pre = t;
		q.push(t->next[i]);
	}else t-> next[i] = t;
	for(;!q.empty();){
		t = q.front();q.pop();
		t-> end |= t -> pre-> end;
		for(int i=0;i<10;++i)
			if(t->next[i]){
				t->next[i]->pre = t->pre->next[i];
				q.push(t->next[i]);
			}else
				t->next[i] = t->pre->next[i];
	}
}
num go(trie t,int n){
	map<trie,num > f,g;
	f[t] = 1;
	for(;n--;){
		for(auto i:f)
		if(!i.first->end)
			for(int j=0;j<10;++j)
				g[i.first->next[j]] += i.second;
		g.swap(f);
		g.clear();
	}
	num ret = 0;
	for(auto i:f)
		if(!i.first->end)
			ret+=i.second;
	return ret;
}
num count_11(num x){
	static int digit[32],len;
	for(len = 0;x > 0;x/=10)digit[len ++ ] = x % 10;
	reverse(digit,digit+len);
	trie t = mem;
	num ret = 0;
	int l;
	for(l=0;l<len;++l){
		for(int i=0;i<digit[l];++i)
			ret+= go(t->next[i], len-l-1);
		t = t -> next[digit[l]];
		if(t -> end)break;
	}
	return ret + (l==len) -1;
}
int main(){
	num x = 1;
	for(int i=0;i<18;++i)insert(x*=11);
	build();
	num target = 1000000000000000000ll;
	num l =0 , r = 1;
	while(count_11(r) < target){
		l = r; r *= 2;
	}
	while(l+1<r){
		num m = l + r >> 1;
		if(count_11(m) < target) l = m;
		else r = m;
	}
	cout << r << endl;
}