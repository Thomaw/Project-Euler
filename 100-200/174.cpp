int a=0;
int c=1000000/4;
int L[1000000]
for(int i=0;i<=1000000;i++)
   {L[i]=0;}

for(int x=1;x<=500;x++)
   {
   int q=x*x;
   for(int b=1;b<=250000;b++)
       {
       int y=q+b*x;
       if(y<=c){L[y*4]++;}
       }
   }

for(int i=0;i<=1000000;i++)
   {if(L[i]<=10&&L[i]>=1)
      {a++;}
   }

cout<<a;
