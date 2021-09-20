unsigned long solve(int a[MAX][MAX])
{
    unsigned int i, j, best[MAX][MAX];
    unsigned long max;

    best[0][0] = a[0][0];
    for (i = 1; i < MAX; i++)
    {
        best[i][0] = a[i][0] + best[i-1][0];
        for (j = 1; j < i ; j++)
            best[i][j] = a[i][j] + fmax(best[i-1][j], best[i-1][j-1]);
        best[i][i] = a[i][i] + best[i-1][i-1];
    }
    max = best[MAX - 1][0];
    for (i = 1; i < MAX; i++)
        if (best[MAX - 1][i] > max)
            max = best[MAX - 1][i];
    return max;
}
