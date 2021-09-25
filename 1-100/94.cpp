#include <iostream>
#include <cmath>

bool isSquare(unsigned long x);


int main()
{
  unsigned long totalP = 0;
  unsigned long MAX = 1000000000 / 3;

  for(long x = 4; x < MAX; x += 2) {
    unsigned long t1 = (3 * x + 2) * (x + 2);
    unsigned long t2 = (3 * x - 2) * (x - 2);
    
    if(isSquare(t1)) {
      unsigned long p = 3 * x + 2;
      totalP += p;
    }
    if(isSquare(t2)) {
      unsigned long p = 3 * x - 2;
      totalP += p;
    }
  }

  std::cout << totalP << std::endl;
}


bool isSquare(unsigned long x)
{
  unsigned long root = sqrt(x);
  return x == root * root;
}