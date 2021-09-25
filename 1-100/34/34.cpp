
unsigned long factorial(unsigned long num)
{
    int i;
    unsigned long returned = num;

    if (num == 0) return 1;

    for (i = returned-1; i != 0; i--)
    {
        returned *= i;
    }
    return returned;
}

int main(void)
{
    int k = 0;
    unsigned long i, sum = 0, finalsum = 0;
    char number[15], digit[2] = "";

    for (i = 3; i < 50000; i++)
    {
        snprintf(number, 15, "%ld", i);

        while (number[k] != '\0')
        {
            digit[0] = number[k];
            sum += factorial(strtoul(digit, NULL, 10));
            k++;
        }
        if (sum == i)
            finalsum += i;
        k = 0;
        sum = 0;
    }

    printf("%ld\n", finalsum);

    return 0;
}
