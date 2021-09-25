int main (int argc, char ** argv){
    int i,m;
    double max;
    long long int sum=0;
    for (m=2; m<=M; sum+=max, m++)
        for (i=1, max=1; i<=m; i++)
            max*=pow(i*2./(m+1), i*1.);
    printf("sum=%lld\n",sum);
	return 0;
}