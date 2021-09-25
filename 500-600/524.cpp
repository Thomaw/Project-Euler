long long id(const int *a, int n)
{
    long long f[n];

    f[0] = 1;
    for (int i = 1; i < n; i++)
        f[i] = f[i - 1] * i;

    long long res = 1;

    for (int i = 0; i < n; i++)
    {
        int k = 0;
        for (int j = i; j < n; j++)
            k += a[j] < a[i];

        res += k * f[n - i - 1];
    }

    return res;
}

int main()
{
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 26, 25, 27, 28, 30, 32, 34, 36, 38, 40, 39, 42, 45, 43, 41, 37, 35, 33, 31, 29, 44};

    cout << id(a, 45) << endl;

    return 0;
}