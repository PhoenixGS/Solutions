#include <cstdio>
#include <algorithm>

const int M = 20101009;
const int _x = 10000000 + 10;
int n, m;
int flag[_x], f[_x];
int primenum;
int prime[_x];
int ans;

int main()
{
	scanf("%d%d", &n, &m);
	f[1] = 1;
	for (int i = 2; i <= std::max(n, m); i++)
	{
		if (! flag[i])
		{
			primenum++;
			prime[primenum] = i;
			f[i] = 1 - i;
		}
		for (int j = 1; j <= primenum && i * prime[j] <= std::max(n, m); j++)
		{
			flag[i * prime[j]] = 1;
			if (i % prime[j] == 0)
			{
				f[i * prime[j]] = f[i];
				break;
			}
			else
			{
				f[i * prime[j]] = (1 - prime[j]) * f[i];
			}
		}
	}
	for (int i = 2; i <= std::max(n, m); i++)
	{
		f[i] = (f[i - 1] + (long long)i * f[i] % M) % M;
	}
	ans = 0;
	for (int i = 1, j = 0; i <= std::min(n, m); i = j + 1)
	{
		j = std::min(n / (n / i), m / (m / i));
		int sum1 = (long long)(n / i) * (n / i + 1) / 2 % M;
		int sum2 = (long long)(m / i) * (m / i + 1) / 2 % M;
		(ans += (long long)(f[j] - f[i - 1]) % M * sum1 % M * sum2 % M) %= M;
	}
	ans = (ans + M) % M;
	printf("%d\n", ans);
	return 0;
}
