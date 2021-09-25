int factors(int k, int n)
{
  if(n%k || n<k) return 0;
  else return 1+factors(k, n/k);
}

int main()
{
  int n=200000, f2s[n+1], f5s[n+1], c2s=0, c5s=0;

  for(int i=0; i<=n; i++) {
    c2s += factors(2, i);  f2s[i] = c2s;
    c5s += factors(5, i);  f5s[i] = c5s;
  }
  
  long long s=0;
  for(int i=0; i<=n/3; i++)
    for(int j=i; 2*j<=n-i; j++) {
      int k = n-i-j;
      if( c2s-f2s[i]-f2s[j]-f2s[k] >= 12 &&
          c5s-f5s[i]-f5s[j]-f5s[k] >= 12 )
        // i=j=k won't happen since i+j+k=n%3 != 0
        s += (i==j || j==k) ? 3 : 6;
    }
  printf("Sum: %lld\n", s);
  exit(0);
}