#include <iostream>
#include <set>
#include <algorithm>
#define int long long int

using namespace std;

class number {
  public:
    int p,q;

    number(){p=0;q=1;};
    number(int n){p=n;q=1;};
    number(int pp,int qq){p=pp;q=qq;}

    number& operator+=(number const &);
    number& operator-=(number const &);
    number& operator*=(number const &);
    number& operator/=(number const &);

    number operator+(number const &x)const{return number(*this)+=x;}
    number operator-(number const &x)const{return number(*this)-=x;}
    number operator*(number const &x)const{return number(*this)*=x;}
    number operator/(number const &x)const{return number(*this)/=x;}
};
ostream& operator<<(ostream &, number const &);
bool operator<(const number& a, const number& b) {
  return a.p*b.q < b.p*a.q;
}
bool operator==(const number& a, const number& b) {
  return a.p*b.q == b.p*a.q;
}

number& number::operator+=(number const &x) {
  p*=x.q; p+=q*x.p; q*=x.q;
  return (*this);
}
number& number::operator-=(number const &x) {
  p*=x.q; p-=q*x.p; q*=x.q;
  return (*this);
}
number& number::operator*=(number const &x) {
  p*=x.p; q*=x.q;
  return (*this);
}
number& number::operator/=(number const &x) {
  p*=x.q; q*=x.p;
  if (x.p<0) {p=-p;q=-q;}
  return (*this);
}
ostream& operator<<(ostream &os, number const &x) {
  if (x.q==1) os << x.p ;
  else if (x.q==0) os << "undef" ;
  else os << '(' << x.p << '/' << x.q << ')';
  return os;
}

set<number> numbers(int from, int to) {
  set<number> n1,n2,n;
  set<number>::iterator i1,i2;

  number x=0; for (int i=from;i<=to;i++) {x*=10;x+=i;}
  n.insert(x);
  for (int i=from;i<to;i++) {
    n1=numbers(from,i);
    n2=numbers(i+1,to);
    for(i1=n1.begin(); i1!=n1.end(); ++i1)
      for(i2=n2.begin(); i2!=n2.end(); ++i2) {
        n.insert(*i1+*i2);
        n.insert(*i1-*i2);
        n.insert(*i1**i2);
        if ((*i2).p!=0) n.insert(*i1/(*i2));
      }
  }
  return n;
}

#undef int
int main() {
#define int long long int
  int s=0;

  set<number> n=numbers(1,9);
  set<number>::iterator i;

  for(i=n.begin(); i!=n.end(); ++i) {
    if ((*i).p<=0) continue;
    if ((*i).q==1)
      s+=(*i).p;
    else if ((*i).p%(*i).q==0)
      s+=(*i).p/(*i).q;
  }
  cout<<"\nsum: "<<s<<"\n";
}
