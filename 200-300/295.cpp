#include <stdio.h>
#include <time.h>

#define N 100000
#define M 2000000
//#define N 1000000
//#define M 50000000
#define N2 ((long long int)N*(long long int)N)

typedef long long int L;
long long int answer = 0;

L *dp[M*2];
int dpn = 0;
L da[M];
int dan = 0;
L da_f[M];

L **dp0;

int k[N+1];
int r_k[N];
int rn = 0;

int ll[N];
int xn = 0;

void recur (L x0, L y0, L x1, L y1);
void delete_double();
void register_d(int r, int mink);
void compact_list();
int merge_one(int l0, int l1, int l2);
void merge_all();

int main(int argc, char **argv) {
  int i;

  double start=clock(); 
  recur(1, 0, 1, 1);

  // (1,1)
  register_d(1, 0);

  for (i=0; i<rn; i++)
    register_d(r_k[i], k[r_k[i]]);

  merge_all();

  compact_list();
  delete_double();

  printf("time %.3f sec\n",(clock() - start) / CLOCKS_PER_SEC);
  printf ("answer: %lld\n", answer);
}

void recur (L x0, L y0, L x1, L y1) {
  L x2, y2;
  static L limity, limitx;
  static L basey, basex;
  static L n;
  static L distance;
  static int r;

  x2 = x0 + x1;
  y2 = y0 + y1;

  limity = x0*x2*x1+x2*y0*y1+y2;
  limity /= 2;
  limitx = x2-y0*y2*y1-y2*x0*x1;
  limitx /= 2;
  distance = limitx*limitx+limity*limity;
  if (distance > N2)
    return;
  basey = (x2+y2)/2;
  basex = (x2-y2)/2;
  n = (limity-basey)/x2;
  basey += x2*(n+1);
  basex -= y2*(n+1);
  distance = basex*basex+basey*basey;

  if ((x2&1)&&(y2&1)&&(distance<=N2)) {
    r = (x2*x2+y2*y2)>>1;
    if (!k[r]) {
      k[r] = n+1;
      r_k[rn++] = r;
    } else if (k[r] > n+1)
      k[r] = n+1;
  }

  recur (x0, y0, x2, y2);
  recur (x2, y2, x1, y1);
}

void delete_double() {
  int i, j, k, pre_i;
  L r, r_pre;
  L *p_now;
  L *p_pre[1000];

  r_pre = 0;
  for (i=1; i<dpn; i++) {
    r = *dp0[i];
    if (r==r_pre) {
      answer--;
      p_now = dp0[i]+1;
      for (j=pre_i, k=0; j<i; j++, k++)
        p_pre[k] = dp0[j]+1;
      
      while (*p_now) {
        for (j=0; j<k; j++) {
          while (*p_pre[j] < *p_now) {
            if (!*p_pre[j])
              goto Label_nextj;
            p_pre[j]++;
          }
          if (*p_pre[j]==*p_now) {
            answer--;
            p_pre[j]++;
            goto Label_nextpnow;
          }
        Label_nextj:
          ;
        }
      Label_nextpnow:
        p_now++;
      }
    } else {
      r_pre = r;
      pre_i = i;
    }
  }
}

void register_d(int r, int mink) {
  int k;
  int lanswer;
  L dis;
  k = mink*2+1;

  ll[xn++] = dpn;

  lanswer = 1;
  dis = (L)r*((1 + (L)k*k)>>1);
  while (dis <= N2) {
    dp[dpn++] = &da[dan];
    da[dan++] = dis;

    answer += lanswer;
    lanswer++;
    k += 2;
    dis = (L)r*((1 + (L)k*k)>>1);
  }
  dp[dpn++] = &da[dan];
  da[dan++] = 0;
}

void compact_list() {
  int i, j;
  int dan2, dpn2;

  dpn2 = 1;
  for (i=2; i<dpn; i++) {
    if (*dp0[i] == *dp0[i-1]) {
      da_f[dp0[i-1]-da] = dpn2++;
      da_f[dp0[i]-da] = dpn2++;
      j=i+1;
      while (j<dpn) {
        if (*dp0[j]!=*dp0[i])
          break;
        da_f[dp0[j]-da] = dpn2++;
        j++;
      }
      i = j;
    }
  }
  
  dan2 = 0;
  for (i=1; i<dan; i++)
    if (da_f[i]) {
      da[dan2] = da[i];
      dp0[da_f[i]] = &da[dan2++];
    } else if (!da[i])
      da[dan2++] = 0;

  dan = dan2;
  dpn = dpn2;
}

// merge sort
int merge_one(int l0, int l1, int l2) {
  while(1) {
    if (*dp[l0] <= *dp[l1]) {
      dp[l2++] = dp[l0++];
      if (*dp[l0] == 0) {
        while (*dp[l1])
          dp[l2++] = dp[l1++];
        dp[l2++] = dp[l1];
        return l2;
      }
    } else {
      dp[l2++] = dp[l1++];
      if (*dp[l1] == 0) {
        while (*dp[l0])
          dp[l2++] = dp[l0++];
        dp[l2++] = dp[l0];
        return l2;
      }
    }
  }
}

void merge_all() {
  int i, xn2;
  int lt, lt0, lt_old;
  int *llp, *llp2;

  lt0 = M;
  llp = ll;
  llp2 = &ll[xn];
  while (xn > 1) {
    xn2 = 0;
    lt = lt0;
    for (i=0; i<xn-1; i+= 2) {
      *llp2 = lt;
      lt = merge_one(*llp, *(llp+1), lt);
      llp+=2;
      llp2++;
      xn2++;
    }
    if (i == xn-1) {// xn:odd
      *llp2 = *llp;
      llp++;
      llp2++;
      xn2++;
    }
    xn = xn2;
    lt0 = M-lt0;
    lt_old = lt;
  }
  dp0 = &dp[M-lt0];
  dpn = lt-1-M+lt0; //include 0
}