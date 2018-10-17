#include <cstdio>
#include <algorithm>

bool flag[10000005];
int mu[10000005];
int ff[10000005];
int ss[10000005];
int primenum;
int prime[10000005];
int T, n, m;

int main()
{
	mu[1] = 1;
	for (int i = 2; i <= 10000000; i++)
	{
		if (! flag[i])
		{
			primenum++;
			prime[primenum] = i;
			mu[i] = -1;
			ff[i] = 1;
		}
		for (int j = 1; j <= primenum && i * prime[j] <= 10000000; j++)
		{
			flag[i * prime[j]] = 1;
			if (i % prime[j] == 0)
			{
				mu[i * prime[j]] = 0;
				ff[i * prime[j]] = mu[i];
				break;
			}
			else
			{
				mu[i * prime[j]] = -mu[i];
				ff[i * prime[j]] = mu[i] - ff[i];
			}
		}
	}
	for (int i = 1; i <= 10000000; i++)
	{
		ss[i] = ss[i - 1] + ff[i];
	}
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &n, &m);
		int top = std::min(n, m);
		int pos = 0;
		long long ans = 0;
		for (int i = 1; i <= top; i = pos + 1)
		{
			pos = std::min(n / (n / i), m / (m / i));
			ans += (long long)(ss[pos] - ss[i - 1]) * (long long)(n / pos) * (long long)(m / pos);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
