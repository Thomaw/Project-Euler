int main(void)
{
    int64_t fib[91];

    int64_t power_10_2n[MAX_POW];

    int offset[10];

    reportTimes(0);

    for(int n = 0; n <= 9; n++)
        offset[n] = ((n + 1) * (n + 2) - 2)/ 2;

    fib[0] = 0;
    fib[1] = 1;
    for(int n = 2; n <= 90; n++)
        fib[n] = fib[n - 1] + fib[n - 2];

    power_10_2n[0] = 10;
    for(int n = 1; n < MAX_POW; n++)
        power_10_2n[n] = (power_10_2n[n - 1] * power_10_2n[n - 1]) % MOD;

    int64_t sum = 0;
    for(int n = 2; n <= 90; n++) {
        int64_t nm9 = fib[n] % 9;
        int64_t nd9 = fib[n] / 9;
        int64_t exponent = 1;
        for(int indx = 0; nd9; indx++) {
            if(nd9 & 0x01)
                exponent = (exponent * power_10_2n[indx]) % MOD;
            nd9 >>= 1;
        }
        sum += ((exponent * (6 + offset[nm9])) % MOD) - (fib[n] % MOD) - 6;
        while(sum < 0)
            sum += MOD;

        sum %= MOD;
    }

    printf("%lld %s\n", sum, (sum == 922058210) ? "✓" : "❌");

    reportTimes(1);
}
