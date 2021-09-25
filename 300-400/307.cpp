
#includes

using namespace std;

#define REP(i,n) for((i)=0;(i)<(int)(n);(i)++)

#define N 1000000
#define M 20000

long double flog[N+10];

int main(void){
	long double ans = 1.0;
	
	int i;
	REP(i,N) flog[i+1] = flog[i] + log(i+1.0);
	
	int x,y;
	REP(y,M/2+1){
		x = M - 2*y;
		ans -= exp(flog[M] + flog[N] - flog[x] - flog[y] - flog[N-x-y] - log(2.0) * y - log(N) * M);
	}
	
	double ans2 = ans;
	printf("%.10f\n",ans2);
	
	return 0;
}