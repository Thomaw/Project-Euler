
#include <cstdio>

long long c[27][27];
long long cnt[27];

int main()
{
	for (int i = 0; i <= 26; i++)
	{
		c[i][0] = c[i][i] = 1;
		for (int j = 1; j < i; j++)
			c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
	}
	long long ans = 0;
	for (int i = 1; i <= 26; i++)
	{
		cnt[i] = 0;
		for (int j = 1; j < i; j++)
			for (int k = j + 1; k <= i; k++)
				cnt[i] += 1ll << (k - j - 1);
		ans >?= cnt[i] * c[26][i];
	}
	printf("%I64d\n", ans);
	return 0;
}