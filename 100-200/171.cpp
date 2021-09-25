#include<iostream>
#define MOD 1000000000
using namespace std;
unsigned long long arr[30][2000],cnt[30][2000];
int main()
{
        for(int i=0;i<10;i++){
                arr[1][i*i]+=i;
                cnt[1][i*i]++;
        }
        for(int dig=2;dig<21;dig++){
                for(int i=0;i<10;i++){
                        for(int sum=1;sum<2000;sum++){
                                if(sum+i*i<2000){
                                        arr[dig][sum+i*i]+=(arr[dig-1][sum]*10+i*cnt[dig-1][sum]);
                                        arr[dig][sum+i*i]%=MOD;
                                        cnt[dig][sum+i*i]+=cnt[dig-1][sum];
                                }
                        }
                }
        }
        long long ans=0;
        for(int dig=1;dig<21;dig++){
                for(int sum=1;sum<50;sum++){
                        if(sum*sum<2000){
                                ans+=arr[dig][sum*sum];
                                ans%=MOD;
                        }
                }
        }
        cout<<ans%MOD<<endl;
}