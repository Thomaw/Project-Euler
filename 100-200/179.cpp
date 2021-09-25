int n[SZ + 1];

int main (int argc, char *argv[])
{

    int i, j;
    for (i = 0; i <= SZ; i++)
        n[i] = 1;

    for (i = 2; i <= SZ; i++)
        for (j = i; j <= SZ; j += i)
            n[j] += 1;

    j = 0;
    for (i = 1; i < SZ; i++)
        if (n[i] == n[i + 1])
            j++;

    printf ("Answer = %d\n", j);
    return 0;
}