#include <iostream>
int i,j,k,n;
#define B(x,b) x&1<<b
#define N(a,b) (B(i,a)&&B(j,b)) | (B(i,b)&&B(j,a))
#define M(c) (N(c,6)||N(c,9))
#define c(b) (k=b-(b>>1&0xdb6db6db)-(b>>2&0x49249249),\
(k+(k>>3)&0xc71c71c7)%63==6)

int main()
{
  while(i++<1024)
    for(j=i;j<1024;++j)
      n+=c(i)&&c(j)&&
        N(0,1)&&
        N(0,4)&&
        M(0)&&  // 09 or 06.
        M(1)&&  // 16 or 19.
        N(2,5)&&
        M(3)&&  // 36 or 39.
        M(4)&&  // Checks both 49 and 64 :-D.
        N(8,1);
  std::cout << n;
}