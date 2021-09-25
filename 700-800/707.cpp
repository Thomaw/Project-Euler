#include<bits/stdc++.h>
using namespace std;
const int N=199;
typedef bitset<N> bit;
struct mat{
	bitset<N+N> a[N+N];
	bitset<N+N>& operator[](int n){
		return a[n];
	}
	void eye(){
		for(int i=0;i<N+N;i++){
			a[i][i]=1;
		}
	} 
};
mat operator*(mat a,mat b){
	mat c,rot;
	for(int i=0;i<N+N;i++){
		for(int j=0;j<N+N;j++){
			rot.a[i][j]=b.a[j][i];
		}
	}
	for(int i=0;i<N+N;i++){
		for(int j=0;j<N+N;j++){
			c[i][j]=(a[i]&rot[j]).count()&1;
		}
	}
	return c;
}
mat trans(){
	mat ma;
	for(int i=0;i<N;i++){
		ma[i][i+N]=1;
	}
	for(int i=N;i<2*N;i++){
		ma[i][i]=1;
		if(i!=N)ma[i][i-1]=1;
		if(i!=N*2)ma[i][i+1]=1;
		ma[i][i-N]=1;
	}
	return ma;
}
#define I inline
#define RG register
#define R RG T
#define UI unsigned int
	template<typename T,const UI L>
	struct LB{
		T a[L];
		int rk=0;
		LB(){
			memset(a,0,sizeof(a));
		}
		I void operator+=(R x){
			for(RG UI i=L-1;x!=0;--i)
				if(x[i]){
					if(a[i]==0){a[i]=x;rk++;return;}
					x^=a[i];
				}
		}
		I void operator+=(RG LB&x){
			for(RG UI i=0;i<L;++i)
				*this+=x.a[i];
		}
	};
#undef I
#undef RG
#undef R
#undef UI
int cal(mat& ma){
	LB<bit,N> t;
	vector<bit>v(N+N);
	for(int i=0;i<N+N;i++){
		bit& s=v[i];
		for(int j=N;j<N+N;j++){
			if(ma[i][j]){
				s[j-N]=1;	
			}
		}
	}
	for(int i=0;i<N;i++){
		t+=v[i+N];
	}
	return t.rk;
}
const int P=1e9+7; 
inline int qpow(int a,int b){
	int res=1;
	for(;b;b>>=1){
		if(b&1){
			res=1ll*res*a%P;
		}
		a=1ll*a*a%P;
	}
	return res;
}
mat m[200];
int f[200];
int main()
{
	m[1]=m[2]=trans();
	int w=199,n=199;
	for(int i=3;i<=n;i++){
		m[i]=m[i-1]*m[i-2];
	}
	f[1]=f[2]=2;
	for(int i=3;i<=n;i++){
		f[i]=1ll*f[i-1]*f[i-2]%P;
	}
	int ans=0;
	const int inv=qpow(2,P-2);
	for(int i=1;i<=n;i++){
		int t=cal(m[i]);
		f[i]=1ll*f[i]*inv%P;
		ans+=1ll*qpow(f[i],w)*qpow(2,t)%P;
		if(ans>=P)ans-=P;
	}
	cout<<ans;
}