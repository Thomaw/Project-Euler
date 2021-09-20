#include < iostream >

using std::cout;
using std::cin;

int main()
{
int summa=1;

for(int i=2, b=2, x=3; i<=501; i++, b+=2)
{
  summa=(4*x)+(6*b)+summa;
  x=x+(4*b)+2;
}

cout << "summa: " << summa;
cin.ignore();
cin.get();
return 0;
}
