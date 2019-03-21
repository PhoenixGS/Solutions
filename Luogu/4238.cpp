#include <cstdio>
#include <algorithm>

const int M = 998244353, G = 3;
const int _n = 100000 + 10;
int n;
int x[6 * _n], y[6 * _n];
int N, bit;
int rev[6 * _n];
int xx[6 * _n], yy[6 * _n];

int pow_mod(int x, int p, int M)
{
	p = (p % (M - 1) + M - 1) % (M - 1);
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

void getrev(int bit)
{
	rev[0] = 0;
	for (int i = 1; i < (1 << bit); i++)
	{
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
	}
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
			for (int k = 0, w = 1; k < i; k++, w = (long long)w * wn % M)
			{
				int xx = x[j + k];
				int yy = (long long)w * x[j + k + i] % M;
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

void solve(int n)
{
	if (n == 1)
	{
		y[0] = pow_mod(x[0], M - 2, M);
		return;
	}
	solve((n + 1) / 2);
	N = 1;
	bit = 0;
	while (N < 3 * n)
	{
		N <<= 1;
		bit++;
	}
	for (int i = 0; i < N; i++)
	{
		xx[i] = yy[i] = 0;
	}
	for (int i = 0; i < n; i++)
	{
		xx[i] = x[i];
	}
	for (int i = 0; i < (n + 1) / 2; i++)
	{
		yy[i] = y[i];
	}
	getrev(bit);
	NTT(xx, N, 1);
	NTT(yy, N, 1);
	for (int i = 0; i < N; i++)
	{
		xx[i] = (long long)xx[i] * yy[i] % M * yy[i] % M;
	}
	NTT(xx, N, -1);
	for (int i = 0; i < n; i++)
	{
		y[i] = ((long long)2 * y[i] % M - xx[i]) % M;
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &x[i]);
	}
	solve(n);
	for (int i = 0; i < n; i++)
	{
		printf("%d ", (y[i] + M) % M);
	}
	puts("");
	return 0;
}
