#include <cstdio>
#include <algorithm>

int n, m;
int phi[300000];
int primenum;
int prime[300000];
bool flag[300000];
long long s[300000];

int main()
{
	scanf("%d%d", &n, &m);
	phi[1] = 1;
	for (int i = 2; i <= 200000; i++)
	{
		if (! flag[i])
		{
			primenum++;
			prime[primenum] = i;
			phi[i] = i - 1;
		}
		for (int j = 1; j <= primenum && i * prime[j] <= 200000; j++)
		{
			flag[i * prime[j]] = 1;
			if (i % prime[j] == 0)
			{
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			}
			else
			{
				phi[i * prime[j]] = phi[i] * (prime[j] - 1);
			}
		}
	}
	for (int i = 1; i <= 200000; i++)
	{
		s[i] = s[i - 1] + phi[i];
	}
	int pos = 0;
	long long ans = 0;
	for (int i = 1; i <= std::min(n, m); i = pos + 1)
	{
		pos = std::min(n / (n / i), m / (m / i));
		ans += (long long)(s[pos] - s[i - 1]) * (long long)(n / i) * (long long)(m / i);
	}
	printf("%lld\n", ans * 2 - (long long)n * m);
	return 0;
}
