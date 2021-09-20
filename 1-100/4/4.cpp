
#include <stdio.h>
#include <string.h>

int main(void)
{
    int x;
    int y;
    int z;
    int max = 0;
    char a[7];
    char b[7];

    for(x = 999 ; x > 99 ; x--)
    {
        for(y = 999 ; y > 99 ; y--)
        {
            z = x * y;
            sprintf(a, "%d", z);
            strcpy(b, a);
            _strrev(b);
            if(strcmp(a, b) == 0)
            {
                if(z > max)
                {
                    max = z;
                }
            }
        }
    }
    printf("Answer = %d\n", max);
    return 0;
}
