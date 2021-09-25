const int maxn = 100000001;

int a[maxn];

int main()
{
    int n = 100000000;
    for (int i = 1; i <= n; i++)
        a[i] = i;
    long long ret = 0;
    for (int i = 1; i <= n; i++) {
        ret += (n / i - 1) * a[i];
        for (int j = i + i; j <= n; j += i)
            a[j] -= a[i];
    }
    printf("%lld\n", ret * 6);
}