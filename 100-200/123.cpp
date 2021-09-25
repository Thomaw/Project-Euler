#include<iostream>
#include<cmath>
#include<vector>

using namespace std;

void eratosthenes(vector<long long> &primes);

int main()
{
  long long stopcond = 10;
  for(int pow=2;pow<=10;++pow) stopcond*=10;//Too big for a constant!

  vector<long long> p; 
  eratosthenes(p);
  long long pos=1;
  for(vector<long long>::iterator i = p.begin(); i!=p.end(); i+=2,pos+=2){
    if( (long long)( (2 * pos * (*i)) ) > stopcond){
      cout << pos << endl;
      break;
    }
  }
  return 0;
}

//Populate the passed vector with prime numbers
void eratosthenes(vector<long long> &primes)
{
  bool sieve[1000001]={1,1};//set 0 and 1 to not be prime
                            //n.b. we are using true to indicate not prime
                            //to save some time on the iitialisation
  //Sieve for the primes
  for(long a = 2;a<sqrt(1000000);++a){
    if(!sieve[a]){
      for(long b = a*2;b<1000001;b+=a) sieve[b]=true;
    }
  }
  //push the primes onto the vector
  for(long a = 0; a< 1000001;++a){
    if(!sieve[a]) primes.push_back(a);
  }
  
}