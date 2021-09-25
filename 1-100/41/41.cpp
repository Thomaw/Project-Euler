#include <iostream>

using namespace std;

bool IsPrime(int n)
{
	if (n % 2 == 0)
		return (n == 2);

	for (int d = 3; d * d < n; d += 2)
		if (n % d == 0)
			return false;

	return true;
}

bool Perm(int num, bool digitUsed[], int stage)
{
     if (stage == 7)
     {
        if (IsPrime(num))
        {
           cout << "FOUND " << num << endl;
           return true;
        }
     }
     else
     {
         for (int c = 7; c > 0; c--)
         {       
             if (!digitUsed[c])
             {
                 if (!( (stage == 6) && ( (c == 2) || (c == 4) || (c == 5) || (c == 6) ) ))
                 {
                     digitUsed[c] = true;
                     
                     if (Perm(num * 10 + c, digitUsed, stage + 1))
                         return true;
                        
                     digitUsed[c] = false;
                 }
             }
         }
     }
         
     return false;
}

void Problem41()
{
    bool digitUsed[8];
    for (int i = 0; i < 8; i++)
        digitUsed[i] = false;
        
    Perm(0, digitUsed, 0);
}
