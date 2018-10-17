#include <cstdio>
#include <cmath>
#include <algorithm>

const int M = 998244353, G = 3;
int n, m;
int bit;
int x[300000], y[300000];
int rev[300000];

void get_rev(int bit)
{
	for (int i = 0; i < (1 << bit); i++)
	{
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
	}
}

long long pow_mod(long long x, long long p, long long M)
{
	p = (p % (M - 1) + (M - 1)) % (M - 1);
	long long ans = 1;
	long long tmp = x;
	while (p)
	{
		if (p & 1)
		{
			ans = ans * tmp % M;
		}
		tmp = tmp * tmp % M;
		p >>= 1;
	}
	return ans;
}

void NTT(int *x, int n, int cas)
{
	for (int i = 0; i < n; i++)
	{
		if (i < rev[i])
		{
			std::swap(x[i], x[rev[i]]);
		}
	}
	for (int i = 1; i < n; i <<= 1)
	{
		int wn = pow_mod(G, cas * (M - 1) / (i << 1), M);
		for (int j = 0; j < n; j += (i << 1))
		{
			int w = 1;
			for (int k = 0; k < i; k++, w = (long long)w * wn % M)
			{
				int xx = x[j + k];
				int yy = (long long)w * x[j + k + i] % M;
//				printf("VV%d %d %d %d\n", cas, w, xx, yy);
				x[j + k] = (xx + yy) % M;
				x[j + k + i] = ((xx - yy) % M + M) % M;
			}
		}
	}
	if (cas == -1)
	{
		int invn = pow_mod(n, M - 2, M);
		for (int i = 0; i < n; i++)
		{
			x[i] = (long long)x[i] * invn % M;
		}
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i <= n; i++)
	{
		scanf("%d", &x[i]);
	}
	for (int i = 0; i <= m; i++)
	{
		scanf("%d", &y[i]);
	}
	m = n + m;
	bit = 0;
	for (n = 1; n <= m; n <<= 1)
	{
		bit++;
	}
	get_rev(bit);
	NTT(x, n, 1);
	NTT(y, n, 1);
	for (int i = 0; i < n; i++)
	{
		x[i] = (long long)x[i] * y[i] % M;
	}
	NTT(x, n, -1);
	for (int i = 0; i <= m; i++)
	{
		printf("%d ", x[i]);
	}
	puts("");
	return 0;
}

