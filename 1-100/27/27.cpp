#include &lt;iostream&gt;
using namespace std;
 
bool isPrime(int n)
{
    if(n<=1)
        return false;
        
    for(int p=2; p*p<=n; p++)
        if(n % p == 0)
                return false;
                
    return true;
}
 
int countPrimes(int a, int b)
{
    int c=0;
    for(int n=0; ; n++) {
        int p = n * (n + a) + b;
        if(!isPrime(p))
                break;
        c++;
    }
    return c;
}
 
int main(int argc, char *argv[])
{
    int m = 0;
    int ma, mb;

    for(int a=-999; a<=999; a++)
        for(int b=-999; b<=999; b++) {
                int c = countPrimes(a, b);
                if(c > m) {
                    m = c;
                    ma = a;
                    mb = b;
                }
        }
        
    cout << ma * mb << endl;
  
    return 0;
}
