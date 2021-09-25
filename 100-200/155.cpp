double dtime=clock();
double eps=0.0000001;
int aantal=0;
const int maxd=18;
int dci[maxd+1];
int di[maxd+1];
for(int i=1;i<=maxd;i++)
        {
        di[i]=0;
        }

dd[1]=60;
di[1]=1;
dci[1]=0;

for(int n=2;n<=maxd;n++)
   {
   dci[n]=dci[n-1]+di[n-1];
   for(int k=1;k<=n/2;k++)
      {
      int m=n-k;
      for(int i=1;i<=di[k];i++)
         {
         for(int j=1;j<=di[m];j++)
            {
            double a=dd[dci[k]+i];
            double b=dd[dci[m]+j];
            if((i==1 || a>dd[dci[k]+i-1]+eps || a<dd[dci[k]+i-1]-eps)
            && (j==1 || b>dd[dci[m]+j-1]+eps || b<dd[dci[m]+j-1]-eps))
               {
               di[n]++;
               dd[dci[n]+di[n]]=a+b;
               di[n]++;
               dd[dci[n]+di[n]]=a*b/(a+b);
               }
            }
         }
      }
   Quicksort(dd, dci[n]+1, dci[n]+di[n]);
   }

Quicksort(dd, 1, dci[maxd]+di[maxd]);

for(int n=1;n<=dci[maxd]+di[maxd];n++)
    {if(dd[n+1]>dd[n]+eps || dd[n+1]<dd[n]-eps){aantal++;}}
    
  
cout << aantal << " in " << clock()-dtime << "ms";