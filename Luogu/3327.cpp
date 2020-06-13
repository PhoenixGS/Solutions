#include <cstdio>
#include <algorithm>

const int _n = 50000 + 10;
int T, n, m;
int flag[_n], mu[_n], s[_n];
int primenum;
int prime[_n];
long long f[_n];
long long ans;

int main()
{
	mu[1] = 1;
	for (int i = 2; i <= 50000; i++)
	{
		if (! flag[i])
		{
			primenum++;
			prime[primenum] = i;
			mu[i] = -1;
		}
		for (int j = 1; j <= primenum && i * prime[j] <= 50000; j++)
		{
			flag[i * prime[j]] = 1;
			if (i % prime[j] == 0)
			{
				mu[i * prime[j]] = 0;
			}
			else
			{
				mu[i * prime[j]] = -mu[i];
			}
		}
	}
	for (int i = 1; i <= 50000; i++)
	{
		s[i] = s[i - 1] + mu[i];
	}
	for (int i = 1; i <= 50000; i++)
	{
		for (int d = 1, nxt; d <= i; d = nxt + 1)
		{
			nxt = i / (i / d);
			f[i] = f[i] + (long long)(i / d) * (nxt - d + 1);
		}
	}
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &n, &m);
		ans = 0;
		for (int d = 1, nxt; d <= std::min(n, m); d = nxt + 1)
		{
			nxt = std::min(n / (n / d), m / (m / d));
			ans = ans + (long long)(s[nxt] - s[d - 1]) * f[n / d] * f[m / d];
		}
		printf("%lld\n", ans);
	}
	return 0;
}
