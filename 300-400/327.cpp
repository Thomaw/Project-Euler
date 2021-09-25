int main()
{
    long long sum=0;
    long long dp[31]={0};
    for(int c=3;c<=30;c++)
    {
        dp[c-1]=c;
        for(int r=c;r<=30;r++)
        {
            long long n=dp[r-1];
            dp[r]=((n-1)%(c-2)) ? n+((n-1)/(c-2))*2+1 : ((n-1)/(c-2))*c;
        }
        sum+=dp[30];
    }
    sum+=(40-30)*31;
    cout << sum << endl;
    return 0;
}