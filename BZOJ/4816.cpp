#include <cstdio>
#include <algorithm>

const int M = 1000000007;
int fx[2000000], fy[2000000];
int mu[2000000];
int flag[2000000];
int primenum;
int prime[2000000];
int g[2000000];
int sx[2000000], sy[2000000];
int n, m;
int T;

int pow_mod(int x, int p, int M)
{
	p = p % (M - 1);
	int ans = 1;
	int tmp = x % M;
	while (p)
	{
		if (p & 1)
		{
			ans = (long long)ans * tmp % M;
		}
		tmp = (long long)tmp * tmp % M;
		p >>= 1;
	}
	return ans;
}

int calc(int pos, int k)
{
	if (k == 0)
	{
		return 1;
	}
	return k == 1 ? fx[pos] : fy[pos];
}

int main()
{
	fx[0] = 0;
	fx[1] = 1;
	for (int i = 2; i <= 1000000; i++)
	{
		fx[i] = (fx[i - 2] + fx[i - 1]) % M;
	}
	for (int i = 1; i <= 1000000; i++)
	{
		fy[i] = pow_mod(fx[i], M - 2, M);
	}
	mu[1] = 1;
	for (int i = 2; i <= 1000000; i++)
	{
		if (! flag[i])
		{
			primenum++;
			prime[primenum] = i;
			mu[i] = -1;
		}
		for (int j = 1; j <= primenum && i * prime[j] <= 1000000; j++)
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
	g[1] = calc(1, mu[1]);
	for (int i = 2; i <= 1000000; i++)
	{
		g[i] = (long long)calc(1, mu[i]) * calc(i, mu[1]) % M;
	}
	for (int i = 2; i <= 1000000; i++)
	{
		for (int j = 2; i * j <= 1000000; j++)
		{
			g[i * j] = (long long)g[i * j] * calc(i, mu[j]) % M;
		}
	}
	sx[0] = 1;
	for (int i = 1; i <= 1000000; i++)
	{
		sx[i] = (long long)sx[i - 1] * g[i] % M;
	}
	sy[1000000] = pow_mod(sx[1000000], M - 2, M);
	for (int i = 999999; i >= 0; i--)
	{
		sy[i] = (long long)sy[i + 1] * g[i + 1] % M;
	}
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &n, &m);
		int pos = 0;
		int ans = 1;
		int top = std::min(n, m);
		for (int i = 1; i <= top; i = pos + 1)
		{
			pos = std::min(n / (n / i), m / (m / i));
			ans = (long long)ans * pow_mod((long long)sx[pos] % M * sy[i - 1] % M, (long long)(n / i) * (m / i) % (M - 1), M) % M;
		}
		printf("%d\n", ans);
	}
	return 0;
}
