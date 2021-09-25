int t[10000001];
int next;
long long sum;

int length(int knots,int lim)
{
  if(knots==1) return 0;
  int b=next/2; if(b==knots) b/=2;
  int erg=0;
  while(knots>1)
  {
    if(knots>b+(b+1)/2) { erg+=lim-knots+b+1; knots-=b+1; b>>=1; }
    else { erg+=lim-b/2; knots-=b/2+1; lim-=b/2+1; b>>=1; }
  }
  return erg;
}

int main()
{
  t[1]=0; int knots=1; next=3; int maxadd=1;
  for(int i=2;i<10000001;i++)
  {
    t[i]=i-knots+t[i-knots-1];
    if(t[i]<i-knots+length(knots,i)) t[i]=i-knots+length(knots,i);
    int add=0;
    for(int a=(knots>=7)?8:2;(knots+a<=next)&&(a<=maxadd*2);a*=2)
    {
      if(knots+a>=i) break;
      if(t[i]>i-knots-a+length(knots+a,i))
      {
        t[i]=i-knots-a+length(knots+a,i);
        add=a;
      }
    }
    if(add) { knots+=add; if(knots==next) { next<<=1; next++; } }
    if(add>maxadd) maxadd<<=1;
    sum+=t[i];
  }
  cout << sum << endl;
}