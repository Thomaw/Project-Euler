int primes[1000000];
int isprime[1000000];

main() {
  int i, j, k, m, nprimes=0, s, p, ok, count=0;
  char test[13];
  for(i=2;i&lt;1000000;i++) {
    s = sqrt(i);
    p=1;
    for(j=0;j&lt;nprimes && primes[j] &lt;= s;j++)
      if(i%primes[j] == 0) {
        p=0;
        break;
      }
    if(isprime[i] = p)
      primes[nprimes++] = i;
  }
  for(i=0;i&lt;nprimes;i++) {
    sprintf(test, "%d%d", primes[i], primes[i]);
    k = strlen(test)/2;
    ok=1;
    for(j=k-1;j&gt;=1;j--) {
      test[j+k] = '\0';
      sscanf(test+j, "%d", &m);
      if(!isprime[m]) {
        ok=0;
        break;
      }
    }
    if(ok)
      count++;
  }
  printf("%d\n", count);
}
