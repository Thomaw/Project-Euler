#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long double real;
const int	N= 2000000;
const int	g1=1248,m1=32323,s1=m1/2,
			g2=8421,m2=30103,s2=m2/2;
int x[N],y[N],id[N];
int prod(int i,int j){return x[i]*y[j]-x[j]*y[i];}
int main(){
	long long ans = N*(N-1ll)*(N-2)/6;
	for	(int i=0,g,p1=1,p2=1;i<N;++i){
		p1=(p1*g1)%m1;p2=(p2*g2)%m2;
		x[i]=p1-s1;y[i]=p2-s2;id[i]=i;
	}
	sort(id,id+N,[](int a,int b)
			{return atan2(y[a],x[a])<atan2(y[b],x[b]);});
	for(int i=0,j=1,k=1;i<N;++i){
		for(;prod(id[i],id[j%N])>0;)++j;
		for(k=max(k,j);prod(id[i],id[k%N])==0;)++k;
		int cnt1 =k-i-1,cnt2=k-j;
		ans-= cnt1*(cnt1-1ll)/2-cnt2*(cnt2-1ll)/2;
	}
	cout << ans << endl;
	return 0; 
}