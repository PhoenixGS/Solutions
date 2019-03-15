#include <cstdio>

const int M = 1000000007;
const int _n = 200000 + 10;
int n, m;
int nn, bit;
int flag[_n];
int primenum;
int prime[_n];
int f[_n];
int inv2;

inline int pow_mod(int x, int p, int M)
{
	int ans = 1;
	int tmp = x;
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

void FWT(int *x, int bit)
{
	for (int i = 0; i < bit; i++)
	{
		for (int j = 0; j < (1 << bit); j++)
		{
			if (j & (1 << i))
			{
				int xx = x[j - (1 << i)];
				int yy = x[j];
				x[j - (1 << i)] = (xx + yy) % M;
				x[j] = ((long long)xx - yy + M) % M;
			}
		}
	}
}

void DFWT(int *x, int bit)
{
	for (int i = 0; i < bit; i++)
	{
		for (int j = 0; j < (1 << bit); j++)
		{
			if (j & (1 << i))
			{
				int xx = x[j - (1 << i)];
				int yy = x[j];
				x[j - (1 << i)] = ((long long)xx + yy) % M * inv2 % M;
				x[j] = ((long long)xx - yy + M) % M * inv2 % M;
			}
		}
	}
}
	

int main()
{
	inv2 = pow_mod(2, M - 2, M);
	for (int i = 2; i <= 50000; i++)
	{
		if (! flag[i])
		{
			primenum++;
			prime[primenum] = i;
		}
		for (int j = 1; j <= primenum && i * prime[j] <= 50000; j++)
		{
			flag[i * prime[j]] = 1;
			if (i % prime[j] == 0)
			{
				break;
			}
		}
	}
	while (scanf("%d%d", &m, &n) == 2)
	{
		nn = 1;
		bit = 0;
		while (nn <= n)
		{
			nn <<= 1;
			bit++;
		}
		for (int i = 0; i < nn; i++)
		{
			f[i] = 0;
		}
		for (int i = 2; i <= n; i++)
		{
			f[i] = 1 - flag[i];
		}
		FWT(f, bit);
		for (int i = 0; i < nn; i++)
		{
			f[i] = pow_mod(f[i], m, M);
		}
		DFWT(f, bit);
		printf("%d\n", f[0]);
	}
	return 0;
}
