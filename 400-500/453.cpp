#include<stdio.h>
#include<assert.h>
//#define MOD 135707531
//typedef long long LL;
typedef __int128 LL;

void print(LL x) {
  char buf[100],i;
  for(buf[i=99]=0;x&&i;) {buf[--i]='0'+x%10;x/=10;}
  printf("%s\n",buf+i);fflush(stdout);  
}


LL s_t4[20000],s_t3[20000],s_t2[20000],s_t1[20000];

LL gcd(LL a,LL b) {LL c;while(b){c=a%b;a=b;b=c;} return (a>0)?a:-a;}
LL min(LL a,LL b) {return (a<b)?a:b;}

LL vierer(LL m,LL n) {
  LL c=0;
  c+=(m+1)*(n+1)*n*(n-1)*(n-2)/24; // horizontal
  c+=(n+1)*(m+1)*m*(m-1)*(m-2)/24; // vertical

  LL x,y,a,b,g,t,T;
  LL X=n/3,Y=m/3;
  for(y=1;y<=Y;y++) {
    for(x=1;x<=X;x++) {
      g=gcd(x,y);
      if(g>1) continue;
      T=min(m/y,n/x);
      assert(T>=3);
      a=n-T*x+1;
      b=m-T*y+1;
      T--;
      //for(t=0;t<=T-2;t++) c+=(T-t)*(T-t-1)/*/2*2*/*(a+t*x)*(b+t*y);  // TODO: O(1)
      /*
      for(t=0;t<=T-2;t++) {
        c+=(y*x) * t*t*t*t;
        c+=(y*a + (x*b + (-2*T + 1)*y*x)) * t*t*t;
        c+=((b + (-2*T + 1)*y)*a + ((-2*T + 1)*x*b + (T*T - T)*y*x)) * t*t;
        c+=(((-2*T + 1)*b + (T*T - T)*y)*a + (T*T - T)*x*b) * t;
        c+=(T*T - T)*b*a;
      }
      */
      c+=(y*x) * s_t4[T-2];
      c+=(y*a + (x*b + (-2*T + 1)*y*x)) * s_t3[T-2];
      c+=((b + (-2*T + 1)*y)*a + ((-2*T + 1)*x*b + (T*T - T)*y*x)) * s_t2[T-2];
      c+=(((-2*T + 1)*b + (T*T - T)*y)*a + (T*T - T)*x*b) * s_t1[T-2];
      c+=(T*T - T)*b*a * (T-2+1);
    }
  }
  return c;
}

LL dreier(LL m,LL n) {
  LL c=0;
  c+=(m+1)*(n+1)*n*(n-1)/6; // horizontal
  c+=(n+1)*(m+1)*m*(m-1)/6; // vertical

  LL x,y,a,b,g,t,T;
  LL X=n/2,Y=m/2;
  for(y=1;y<=Y;y++) {
    for(x=1;x<=X;x++) {
      g=gcd(x,y);
      if(g>1) continue;
      T=min(m/y,n/x);
      assert(T>=2);
      a=n-T*x +1;
      b=m-T*y +1;
      T--;
      //for(t=0;t<=T-1;t++) c+=(T-t)*2*(a+t*x)*(b+t*y);  // TODO: O(1)
      c+=-2*y*x * s_t3[T-1];
      c+=(-2*y*a + (-2*x*b + 2*T*y*x)) * s_t2[T-1];
      c+=((-2*b + 2*T*y)*a + 2*T*x*b) * s_t1[T-1];
      c+=2*T*b*a*(T-1+1);
    }
  }
  return c;
}

LL all3(LL m,LL n) {
  LL x=(m+1)*(n+1);
  return x*(x-1)*(x-2)/6;
}

LL all4(LL m,LL n) {
  LL x=(m+1)*(n+1);
  return x*(x-1)*(x-2)*(x-3)/24;
}

/*
LL area3(LL m,LL n) { // sum of areas of all triangles
  LL a,b;
  LL s=0,c,d,E;
  for(a=1;a<=n;a++) for(b=1;b<=m;b++) {
    c=0;
    c+=( (a-1)*(b-1)*a*b-(a-1)*a/2*(b-1)*b/2 )*4;
    c+=( a*b*(a-1+b-1) )*2;
    for(d=0;d<a;d++) {
      E=b*(a-d)/a;
      c+=( (E+1)*(a*b-d*b)-a*E*(E+1)/2 )*4;
    }
    s+=c*(n+1-a)*(m+1-b);
  }
  return s;
  //return 2943432;
}
*/

LL area3(LL m,LL n) { // sum of areas of all triangles
  LL b;
  LL s=0;
  #pragma omp parallel for schedule(dynamic) reduction(+:s)
  for(b=1;b<=m;b++) {
    LL a,c,d,E,r,dE,dr;
    for(a=1;a<=n;a++) {
      c=0; 
      E=b+1,r=0;
      dE=b/a,dr=b-a*dE;
      for(d=0;d<a;d++) {
        c+=E* (b*(a-d) + r);
        E-=dE,r-=dr;
        if(r<0) E--,r+=a;
      }
      c*=2;
      c+=( 3*(a-1)*(b-1)+2*(a-1+b-1) ) *a*b;
      s+=c*(n+1-a)*(m+1-b);
    }
  }
  return s;
}

int main(int argc,char **argv) {
  
  LL t;
  s_t4[0]=s_t3[0]=s_t2[0]=s_t1[0]=0;
  for(t=1;t<20000;t++) {
    s_t4[t]=s_t4[t-1]+t*t*t*t; 
    s_t3[t]=s_t3[t-1]+t*t*t; 
    s_t2[t]=s_t2[t-1]+t*t; 
    s_t1[t]=s_t1[t-1]+t; 
  }

  LL m=2,n=2;

  if(argc>1) {
    m=atoi(argv[1]);
    n=atoi(argv[2]);
  }

  LL v,d,dp,a4,realborder,cnt4,a3,count3,border3,A2,cnt3;
  print(m);
  print(n);
  print(v=vierer(m,n));
  print(d=dreier(m,n));
  print(dp=d*((m+1)*(n+1)-3));
  print(a4=all4(m,n));
  print(realborder=dp-4*v);  // border3-count3*3
  print(cnt4=a4-v-(dp-4*v));  
  print(a3=all3(m,n));  
  print(count3=a3-d);  
  print(border3=count3*3+realborder); 
  print(A2=area3(m,n));  
  print(cnt3=(A2-border3+2*count3)/2);  
  print(cnt3*3+(cnt4-cnt3));  // concave and convexe solutions 
}
