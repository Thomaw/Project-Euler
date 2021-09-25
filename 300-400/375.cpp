#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef long long ll;

int main(int argc, char* argv[]) {
  if (argc != 2 || strtoull(argv[1], NULL, 10) == ULLONG_MAX) {
    printf("Usage:  %s <natural number>\n", argv[0]);
    exit(1);
  }
  ll N = (ll)strtoull(argv[1], NULL, 10);

  ll ans=0;
  ll S=290797, n=0;
  S=S*S%50515093, n=1;

  const ll lcMax=1000, dcMax=1000;
  ll lowS[lcMax]={S}, lowN[lcMax]={n}, lc=1;
  ll deferS[dcMax]={S}, deferN[dcMax]={n}, deferIMin[dcMax]={1}, dc=1;
#ifdef VERBOSE
    printf("S_%03lld = %8lld, ans up to %10lld, lc=%lld, dc=%lld\n", n, S, ans, lc, dc);
#endif
  for (n=2; n<=N; n++) {
    S=S*S%50515093;
    for (ll di=0; di<dc; di++)
      if (S<=deferS[di]) {
	ans+=deferS[di]*(deferN[di]-deferIMin[di]+1)*(n-1-deferN[di]+1);
	if (di<dc-1)
	  deferS[di]=deferS[dc-1], deferN[di]=deferN[dc-1], deferIMin[di]=deferIMin[dc-1];
	dc--;
	di--;
      }

    deferS[dc]=S;
    deferN[dc]=n;
    deferIMin[dc]=1;
    for (ll li=0; li<lc; li++)
      if (S>lowS[li])
	deferIMin[dc]=lowN[li]+1;
      else {
	lc=li;
	break;
      }
    if (++dc>=dcMax)
      printf("dc exceeded dcMax=%lld\n", dcMax), abort();

    lowS[lc]=S;
    lowN[lc]=n;
    if (++lc>=lcMax)
      printf("lc exceeded lcMax=%lld\n", lcMax), abort();
#ifdef VERBOSE
    printf("S_%03lld = %8lld, ans up to %10lld, lc=%lld, dc=%lld\n", n, S, ans, lc, dc);
#endif
  }

  for (ll di=0; di<dc; di++)
    ans+=deferS[di]*(deferN[di]-deferIMin[di]+1)*(N-deferN[di]+1);

  printf("%lld\n", ans);
}