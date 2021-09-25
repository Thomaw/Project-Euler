#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <set>
#include <map>

using namespace std;

struct triple {
  int x,y,z;  
  triple():x(0),y(0),z(0){}
  triple(int ix, int iy, int iz):x(ix),y(iy),z(iz){
    if (y>z) swap(y,z);
    if (x>y) swap(x,y);
    if (y>z) swap(y,z);
  }
  triple(const triple &i):x(i.x),y(i.y),z(i.z){}
};

bool operator==(const triple &i1, const triple &i2) {
  return i1.x==i2.x && i1.y==i2.y && i1.z==i2.z;
}

bool operator<(const triple &i1, const triple &i2) {
  return (i1.x<i2.x) || (i1.x==i2.x && i1.y<i2.y) || (i1.x==i2.x && i1.y==i2.y && i1.z<i2.z);
}

const long long int N=6124;
const long long int NN=75000000;
set<triple> ss;

void checkadd(long long int a, long long int b, long long int c, long long int d){

  if (b*b+c*c!=d*d-1 || a!=1){
    cout<<"ERROR:"<<a<<","<<b<<","<<c<<","<<d<<endl;
    system("PAUSE");
  }/* else cout<<a<<","<<b<<","<<c<<","<<d<<endl;*/

  b=abs(b); c=abs(c); d=abs(d);
  if (b==0 || c==0 || d==0 || b+c+d>NN || d+b<=c || d+c<=b || b+c<=d) return;

  triple t(b,c,d);
  ss.insert(t);
}

int main(int argc, char *argv[])
{
  clock_t start,finish;
  double time;
  start = clock();    

  set<int> s;
  multimap< int,pair<int,int> > mm;
  for(int i=0;i<=N;i++){  
    if (i%100==0) cout<<i<<endl;
    for(int o=i;o<=N;o++){  
      if (2*i*i+2*o*o-1<=NN) s.insert(i*i+o*o);
    }
  }
  cout<<s.size()<<endl;

  for(int i=0;i<=N;i++){  
    if (i%100==0) cout<<i<<endl;
    for(int o=i;o<=N;o++){  
      if (2*i*i+2*o*o-1<=NN && s.find(i*i+o*o+1)!=s.end()) {
        mm.insert(pair<int,pair<int,int> >(i*i+o*o+1,pair<int,int>(i,o)));
      }
    }
  }
  cout<<mm.size()<<endl;
/*   
  int nr=0;
  for(multimap< int,pair<int,int> >::iterator it=m.begin();it!=m.end() && nr<5000;it++,nr++){
    cout<<it->first<<": "<<it->second.first<<","<<it->second.second<<endl;
  }
*/

  for(long long int m=-N;m<=N;m++) {
//  for(long long int m=0;m<=N;m++) {
    if (abs(m)%100==0) cout<<m<<" ("<<ss.size()<<")"<<endl;
//    int B=(NN+1)/2-m*m;
    long long int B=NN-m*m;
    if (B<0) B=0; else B=sqrt(B)+1;
    for(long long int n=-B;n<=B;n++) {
      multimap< int,pair<int,int> >::iterator it;
      pair<multimap< int,pair<int,int> >::iterator,multimap< int,pair<int,int> >::iterator> mp;
      mp=mm.equal_range(m*m+n*n);
      for(it=mp.first;it!=mp.second;it++){
        long long int p;      
        long long int q;      

        p=it->second.first;      
        q=it->second.second;      
        if (p<q) {
          long long int a=m*m+n*n-p*p-q*q;
          long long int b=2*(m*p+n*q);
          long long int c=2*(n*p-m*q);
          long long int d=m*m+n*n+p*p+q*q;
          if (b>0 && c>0 && d>0 && b+c+d<=NN) {
            checkadd(a,b,c,d);
          }
        }
        q=it->second.first;      
        p=it->second.second;      
        if (p<q) {
          long long int a=m*m+n*n-p*p-q*q;
          long long int b=2*(m*p+n*q);
          long long int c=2*(n*p-m*q);
          long long int d=m*m+n*n+p*p+q*q;
          checkadd(a,b,c,d);
        }

        p=-it->second.first;      
        q=it->second.second;      
        if (p<q) {
          long long int a=m*m+n*n-p*p-q*q;
          long long int b=2*(m*p+n*q);
          long long int c=2*(n*p-m*q);
          long long int d=m*m+n*n+p*p+q*q;
          checkadd(a,b,c,d);
        }
        q=-it->second.first;      
        p=it->second.second;      
        if (p<q) {
          long long int a=m*m+n*n-p*p-q*q;
          long long int b=2*(m*p+n*q);
          long long int c=2*(n*p-m*q);
          long long int d=m*m+n*n+p*p+q*q;
          checkadd(a,b,c,d);
        }

        p=it->second.first;      
        q=-it->second.second;      
        if (p<q) {
          long long int a=m*m+n*n-p*p-q*q;
          long long int b=2*(m*p+n*q);
          long long int c=2*(n*p-m*q);
          long long int d=m*m+n*n+p*p+q*q;
          checkadd(a,b,c,d);
        }
        q=it->second.first;      
        p=-it->second.second;      
        if (p<q) {
          long long int a=m*m+n*n-p*p-q*q;
          long long int b=2*(m*p+n*q);
          long long int c=2*(n*p-m*q);
          long long int d=m*m+n*n+p*p+q*q;
          checkadd(a,b,c,d);
        }

        p=-it->second.first;      
        q=-it->second.second;      
        if (p<q) {
          long long int a=m*m+n*n-p*p-q*q;
          long long int b=2*(m*p+n*q);
          long long int c=2*(n*p-m*q);
          long long int d=m*m+n*n+p*p+q*q;
          checkadd(a,b,c,d);
        }
        q=-it->second.first;      
        p=-it->second.second;      
        if (p<q) {
          long long int a=m*m+n*n-p*p-q*q;
          long long int b=2*(m*p+n*q);
          long long int c=2*(n*p-m*q);
          long long int d=m*m+n*n+p*p+q*q;
          checkadd(a,b,c,d);
        }       

      }
    }
  }

  cout<<"Res.:"<<ss.size()<<endl;

  finish = clock();
  time = (double(finish)-double(start))/CLOCKS_PER_SEC;  
  cout<<"Time:"<<time<<endl;
  
  ofstream f("res.txt");
  f<<"Res.:"<<ss.size()<<endl;
  int nr=0;
  for(set<triple>::iterator it=ss.begin();it!=ss.end();it++){
    f<<++nr<<":"<<it->x<<","<<it->y<<","<<it->z<<" ("<<it->x+it->y+it->z<<")"<<endl;
  }
  f.close();

  system("PAUSE");
  return EXIT_SUCCESS;
}