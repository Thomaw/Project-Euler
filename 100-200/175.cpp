void f175()
{
   const int N=16;
   int a[N];
   //int64 p=13, q=17;
   int64 p=123456789, q=987654321;
   int i=N;
   while (p>0 && q>0)
   {
      if (p>q)
         a[--i]=p/q, p-=q*a[i];
      else
         a[--i]=q/p, q-=p*a[i];
      if (p==0)
         p=q, --a[i];
   }
   printf("%d", a[i]);
   while (++i<N)
      printf(",%d", a[i]);
   printf("\n");
}
int main(int argc, char**argv)
{
   timer t;
   f175();
   return 0;
}
/*
1,13717420,8
runtime 0.000 secs
*/