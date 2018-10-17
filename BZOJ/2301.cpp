#include <cstdio>
#include <algorithm>

int mu[60000], ss[60000];
int primenum;
int prime[60000];
int flag[60000];
int n;
int a, b, c, d, k;

long long calc(int n, int m)
{
	if (n > m)
	{
		std::swap(n, m);
	}
	long long ans = 0;
	int pos = 0;
	for (int i = 1; i <= n; i = pos + 1)
	{
		pos = std::min(n / (n / i), m / (m / i));
		ans += (long long)(ss[pos] - ss[i - 1]) * (long long)(n / i) * (long long)(m / i);
	}
	return ans;
}

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
				break;
			}
			else
			{
				mu[i * prime[j]] = -mu[i];
			}
		}
	}
	for (int i = 1; i <= 50000; i++)
	{
		ss[i] = ss[i - 1] + mu[i];
	}
	scanf("%d", &n);
	while (n--)
	{
		scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
		a--;
		c--;
		a /= k;
		b /= k;
		c /= k;
		d /= k;
		long long ans = calc(b, d) - calc(a, d) - calc(b, c) + calc(a, c);
		printf("%lld\n", ans);
	}
	return 0;
}
