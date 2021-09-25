#include<iostream>
#include<vector>
#include<map>

using namespace std;

int main(void) {
  const int64_t N=100000000000000000;
  map<int64_t,int64_t> xis;
  for(int64_t xi=2;xi*xi<=N;xi++) {
    int64_t power=xi*xi;
    int64_t foo2=xi*xi - (xi-1)*(xi-1);
    int64_t foo1=xi*xi + xi*(xi-1) + (xi-1)*(xi-1);
    while(true) {
      map<int64_t,int64_t>::iterator iter=xis.lower_bound(power);
      if(iter == xis.end()) {
        map<int64_t,int64_t>::reverse_iterator jter=xis.rbegin();
        if(jter == xis.rend() || jter->second < foo1) {
          xis[power]=foo1;
        }
      } else {
        if(iter->first == power) {
          if(iter->second < foo1) {
            iter->second = foo1;
            iter++;
            while(iter != xis.end() && iter->second <= foo1) {
              map<int64_t,int64_t>::iterator tmp=iter;
              iter++;
              xis.erase(tmp);
            }
          }
        } else {
          if(iter == xis.begin()) {
            xis[power]=foo1;
          } else {
            map<int64_t,int64_t>::iterator tmp=iter;
            tmp--;
            if(tmp->second < foo1) {
              while(iter != xis.end() && iter->second <= foo1) {
                tmp=iter;
                iter++;
                xis.erase(tmp);
              }
              xis[power]=foo1;
            }
          }
        }
      }
      if(power >= N/xi + 1) break;
      power=power*xi;
      int64_t tmp=foo1;
      foo1=(2*xi-1)*foo1 - (xi-1)*xi*foo2;
      foo2=tmp;
    }
  }
  typedef pair<int64_t,int64_t> P;
  vector<P> xiv;
  for(auto xi: xis) {
    xiv.push_back({xi.second, xi.first});
  }
  int64_t y=xiv[0].first;
  int64_t x=xiv[0].second;
  int64_t S=0;
  while(true) {
    int64_t newx=N+1;
    int64_t newy=y;
    for(int64_t i=0;i<xiv.size();i++) {
      int64_t k=max((y + xiv[i].first - 1) / xiv[i].first, x / xiv[i].second + 1);
      if(k*xiv[i].second < newx) {
        newx=k*xiv[i].second;
        newy=k*xiv[i].first;
      } else if(k*xiv[i].second == newx) {
        newy=max(newy, k*xiv[i].first);
      }
    }
    if((newx-x)%2 == 1) {
      if(x%2 == 0) S+=y;
      else S-=y;
    }
    x=newx;
    y=newy;
    if(x == N+1) break;
  }
  cout << S << endl;
  return 0;
}