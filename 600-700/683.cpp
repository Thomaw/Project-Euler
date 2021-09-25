#include <cstdio>
#include <cmath>
const int N=500;
double f[2][N+1];
int get(int x,const int &n)
{
    return (x+n)%n;
}
int main()
{
    double ans=0;
    for (int n=N;n>1;--n)
    {
        f[0][0]=0;
        for (int i=1;i<n;++i)
            f[0][i]=(n-i)*2.0/n/n;
        int now=0;
        double temp=0;
        for (long long s=1;;++s)
        {
            //#pragma omp parallel for shared(f)
            for (int i=0;i<n;++i)
                f[1-now][i]=(f[now][get(i+2,n)]*4+f[now][get(i+1,n)]*8+f[now][i]*12+f[now][get(i-1,n)]*8+f[now][get(i-2,n)]*4)/36;
            double v=f[1-now][0]*s*s;
            f[1-now][0]=0;
            if (v<1e-11)
            {
                printf("%d: %.10f step = %lld\n",n,temp,s);
                break;
            }
            temp+=v;
            now=1-now;
        }
        ans+=temp;
    }
    printf("%.10f\n",ans);
    return 0;
}