#include <cstdio>
#include <algorithm>

int n;
int a, b, d;
bool flag[100000];
int primenum, prime[100000];
int mu[100000], sum[100000];

int main()
{
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
	mu[1] = 1;
	for (int i = 1; i <= 50000; i++)
	{
		sum[i] = sum[i - 1] + mu[i];
	}
	scanf("%d", &n);
	while (n--)
	{
		scanf("%d%d%d", &a, &b, &d);
		a = a / d;
		b = b / d;
		int top = std::min(a, b);
		long long ans = 0;
		int pos = 0;
		for (int i = 1; i <= top; i = pos + 1)
		{
			pos = std::min(a / (a / i), b / (b / i));
			ans += (long long)(sum[pos] - sum[i - 1]) * (a / i) * (b / i);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
