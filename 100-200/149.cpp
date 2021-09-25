#include <stdio.h>

long long Tbl[2000][2000];
long long recupCol(int ind)
{
     return ind/2000;
}
long long recupLin(int ind)
{
     return ind%2000;
}
long long Generate(int ind)
{
     long long k = ((long long)ind);
     if (ind <= 55) return  ((100003 - 200003*k + 300007*k*k*k) % 1000000) - 500000;
     return ((Tbl[recupLin(ind-24)][recupCol(ind-24)] + Tbl[recupLin(ind-55)][recupCol(ind-55)] + 1000000) % 1000000) - 500000;
}
void MakeGrille()
{
     for (int ind = 0 ; ind < 4000000 ; ind++)
         Tbl[recupLin(ind)][recupCol(ind)] = Generate(ind);
}
int main()
{
    MakeGrille();
    
    long long max = 0;
    for (int col = 0 ; col < 2000 ; col++)
    {
        long long cur1 = 0, cur2 = 0;
        for (int lin = 0 ; lin < 2000 ; lin++)
        {
            cur1 = (cur1+Tbl[col][lin] >? 0);
            cur2 = (cur2+Tbl[lin][col] >? 0);
            max >?= (cur1 >? cur2);
        }
    }
    
    printf("%llu\n", max);
    return 0;
}