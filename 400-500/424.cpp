#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <complex>
#pragma comment(linker, "/STACK:266777216")
using namespace std;

#define assert(f) { if(!(f)) { fprintf(stderr,"Assertion failed: "); fprintf(stderr,#f); fprintf(stderr,"\n"); exit(1); } }

typedef long long LL;
typedef unsigned long long ULL;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int,int> PII;
typedef vector<PII> VPII;
typedef vector<double> VD;
typedef pair<double,double> PDD;
typedef vector<string> VS;

const int inf=1000000000;
const LL INF=LL(inf)*inf;
const double eps=1e-9;
const double PI=2*acos(0.0);
#define bit(n) (1<<(n))
#define bit64(n) ((LL(1))<<(n))
#define pb push_back
#define sz size()
#define mp make_pair
#define cl clear()
#define all(a) (a).begin(),(a).end()
#define fill(ar,val) memset((ar),(val),sizeof (ar))
#define MIN(a,b) {if((a)>(b)) (a)=(b);}
#define MAX(a,b) {if((a)<(b)) (a)=(b);}
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define sqr(x) ((x)*(x))
#define X first
#define Y second

#define N 7

int can[100][10][1111];

void precalc()
{
  for(int mask=0;mask<bit(10);mask+=2)
  {
    int sum=0;
    int cnt=0;
    for(int i=1;i<10;i++)
      if(mask & bit(i)) {
        sum += i;
        cnt++;
      }
    for(int p=0;p<bit(10);p+=2)
      if((mask & p) == mask)
        can[sum][cnt][p] = 1;
  }
}

int n;

int h[N][N],v[N][N];
bool puz_found;

void print(VVI a)
{
  for(int x=0;x<n;x++)
  {
    for(int y=0;y<n;y++)
      fprintf(stderr,"%3d", a[x][y]);
    fprintf(stderr,"\n");
  }
}

bool isCorrect(VVI a)
{
  int d;
  for(int x=0;x<n;x++)
    for(int y=0;y<n;y++)
      if(a[x][y]>=0) {
        if(x==0 || a[x-1][y]<0) {
          int zero=0;
          int mask=0;
          int sum=0;
          for(int z=x;z<n && (d=a[z][y])>=0;z++)
          {
            if(d==0) {
              zero++;
              continue;
            }
            sum+=d;
            if(mask & bit(d)) return false;
            mask |= bit(d);
          }
          if(sum>v[x][y]) return false;
          if(zero==0 && sum!=v[x][y]) return false;
        }
        if(y==0 || a[x][y-1]<0) {
          int zero=0;
          int mask=0;
          int sum=0;
          for(int z=y;z<n && (d=a[x][z])>=0;z++)
          {
            if(d==0) {
              zero++;
              continue;
            }
            sum+=d;
            if(mask & bit(d)) return false;
            mask |= bit(d);
          }
          if(sum>h[x][y]) return false;
          if(zero==0 && sum!=h[x][y]) return false;
        }
      }
  return true;
}

void puz(VVI a)
{
  if(puz_found) return;
  if(!isCorrect(a)) return;
  int d;
  vector<pair<pair<int,VI>,PII> > tmp;
  for(int x=0;x<n;x++) {
    for(int y=0;y<n;y++) {
      if(a[x][y]==0) {
        int x1,x2;
        int vmask=0;
        int vsum=v[x][y];
        int vcnt=0;
        for(x1=x-1;x1>=0 && a[x1][y]>=0;x1--)
          if(d=a[x1][y]) {
            assert(!(vmask & bit(d)));
            vmask |= bit(d);
            vsum-=d;
          } else vcnt++;
        for(x2=x+1;x2<n && a[x2][y]>=0;x2++)
          if(d=a[x2][y]) {
            assert(!(vmask & bit(d)));
            vmask |= bit(d);
            vsum-=d;
          } else vcnt++;
        vmask = 1022 - vmask;

        int y1,y2;
        int hmask=0;
        int hsum=h[x][y];
        int hcnt=0;
        for(y1=y-1;y1>=0 && a[x][y1]>=0;y1--)
          if(d=a[x][y1]) {
            assert(!(hmask & bit(d)));
            hmask |= bit(d);
            hsum-=d;
          } else hcnt++;
        for(y2=y+1;y2<n && a[x][y2]>=0;y2++)
          if(d=a[x][y2]) {
            assert(!(hmask & bit(d)));
            hmask |= bit(d);
            hsum-=d;
          } else hcnt++;
        hmask = 1022 - hmask;

        int cnt=0;
        VI mask;
        for(d=1;d<=hsum && d<=vsum && d<=9;d++)
          if((hmask & bit(d)) && (vmask & bit(d))
            && can[hsum-d][hcnt][hmask^bit(d)]
            && can[vsum-d][vcnt][vmask^bit(d)])
            {
              cnt++;
              mask.pb(d);
            }
        if(cnt==0)
          return;
        tmp.pb(mp(mp(cnt,mask),mp(x,y)));
      }
    }
  }
  sort(all(tmp));
  int i;
  for(i=0;i<tmp.sz;i++)
  {
    int cnt = tmp[i].X.X;
    VI mask = tmp[i].X.Y;
    int x = tmp[i].Y.X;
    int y = tmp[i].Y.Y;
    if(cnt==1) {
      a[x][y] = mask[0];
    } else break;
  }
  if(!isCorrect(a)) return;
  if(i==tmp.sz) {
    puz_found=true;
    //print(a);
    return;
  }
  VI mask = tmp[i].X.Y;
  int x = tmp[i].Y.X;
  int y = tmp[i].Y.Y;
  for(int j=0;j<mask.sz;j++)
  {
    a[x][y]=mask[j];
    puz(a);
  }
}

LL ans = 0;

vector<vector<VS> > a;

bool found;

int minv[10],maxv[10];
int mark[10];
int val[10];

void rec(int d)
{
  if(found) return;
  if(d==10)
  {
    if(val[0]==8 && val[1]==4 && val[2]==2 && val[3]==6 && val[6]==9)
      d=d;
    VVI c(n,VI(n));
    fill(h,-1);
    fill(v,-1);
    for(int x=0;x<n;x++)
      for(int y=0;y<n;y++)
      {
        VS b=a[x][y];
        if(b[0][0]=='O') c[x][y]=0; else
        if(b[0][0]<='J') {
          assert(c[x][y]=val[b[0][0]-'A']);
        } else {
          h[x][y]=v[x][y]=c[x][y]=-1;
          if(b[0][0]!='X') {
            for(int i=0;i<b.sz;i++) {
              string s = b[i];
              int sum = val[s[1]-'A'];
              if(s.sz==3) sum = 10 * sum + val[s[2]-'A'];
              if(s[0]=='h') {
                for(int z=y+1;z<n && a[x][z][0][0]<='O';z++)
                  h[x][z]=sum;
              } else {
                for(int z=x+1;z<n && a[z][y][0][0]<='O';z++)
                  v[z][y]=sum;
              }
            }
          }
        }
      }
    puz_found=false;
    puz(c);
    if(puz_found) {
      LL res=0;
      for(int d=0;d<10;d++)
        res = 10 * res + val[d];
      ans += res;
      found = true;
    }
    return;
  }
  for(int x=minv[d];x<=maxv[d];x++) if(!mark[x])
  {
    val[d]=x;
    mark[x]=1;
    rec(d+1);
    mark[x]=0;
    val[d]=-1;
  }
}

int main()
{
  clock_t start=clock();
  freopen("in.txt","rt",stdin);
  freopen("out.txt","wt",stdout);

  precalc();

  int it=0;
  char s[1111];
  while(scanf("%s",s)>0)
  {
    n = s[0]-'0';
    int i = 2;
    a = vector<vector<VS> >(n, vector<VS>(n));
    for(int x=0;x<n;x++) {
      for(int y=0;y<n;y++) {
        if(s[i]!='(') a[x][y]=VS(1,string(1,s[i])); else
        {
          a[x][y].cl;
          string tmp="";
          for(i++;;i++)
          {
            if(s[i]==',' || s[i]==')') {
              a[x][y].pb(tmp);
              tmp="";
            } else {
              tmp+=s[i];
            }
            if(s[i]==')') break;
          }
        }
        i+=2;
      }
    }
    for(int d=0;d<10;d++) {
      minv[d]=0;
      maxv[d]=9;
    }
    for(int x=0;x<n;x++)
      for(int y=0;y<n;y++)
      {
        vector<string> b = a[x][y];
        if(b[0][0]>='a') {
          for(int i=0;i<b.sz;i++)
          {
            string s = b[i];
            int k = 0;
            if(s[0]=='h') {
              for(int z=y+1;z<n && a[x][z][0][0]<='O';z++)
                k++;
            } else {
              for(int z=x+1;z<n && a[z][y][0][0]<='O';z++)
                k++;
            }
            int mn = k*(k+1)/2;
            int mx = 10*k - mn;
            if(s.sz==3) mn/=10, mx/=10;
            int d = s[1]-'A';
            MAX(minv[d], 1);
            MAX(minv[d], mn);
            MIN(maxv[d], mx);
          }
        } else {
          if(b[0][0]<='J')
            MAX(minv[b[0][0]-'A'], 1);
        }
      }
      fill(val,-1);
      fill(mark,0);
      found=false;
      LL prev=ans;
      rec(0);
      //fprintf(stderr,"%010lld\n",ans-prev);
      assert(found);
      fprintf(stderr,"puz=%d: %lld\n",++it,ans);
  }
  printf("%lld\n",ans);
  fprintf(stderr,"time=%.3lfsec\n",0.001*(clock()-start));
  return 0;
}