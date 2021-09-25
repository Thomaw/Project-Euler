#include <stdio.h>
bool isB1(int nb, int min)
{
     if (nb == 0) return true;
     if (nb%10 < min) return false;
     return isB1(nb/10, nb%10);     
}
bool isB2(int nb, int max)
{
     if (nb == 0) return true;
     if (nb%10 > max) return false;
     return isB2(nb/10, nb%10);     
}
int main()
{
    int nbB = 1;
    int ind = 1;
    while (nbB*100 != ind)
    {
        ind++;
        if (isB1(ind, 0) || isB2(ind, 9)) nbB++;
    }
    printf("%d\n", ind);
    return 0;
}