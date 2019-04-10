#include <cstdio>
#include <algorithm>

const int M = 998244353, G = 3;
const int _n = 100000 + 10;
int n;
int x[4 * _n], y[4 * _n];
int N, bit;
int rev[4 * _n];
int xx[4 * _n], yy[4 * _n];
int inv[4 * _n];

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

void poly_inv(int n, int *x, int *y)
{
	if (n == 1)
	{
		y[0] = pow_mod(x[0], M - 2, M);
		return;
	}
	poly_inv((n + 1) / 2, x, y);
	int N = 1;
	int bit = 0;
	while (N < 2 * n)
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

void poly_ln(int n, int *x, int *y)
{
	static int z[4 * _n];
	int N = 1;
	int bit = 0;
	while (N < 2 * n)
	{
		N <<= 1;
		bit++;
	}
	for (int i = 0; i < N; i++)
	{
		y[i] = z[i] = 0;
	}
	poly_inv(n, x, z);
	for (int i = 0; i < n - 1; i++)
	{
		y[i] = (long long)x[i + 1] * (i + 1) % M;
	}
	getrev(bit);
	NTT(y, N, 1);
	NTT(z, N, 1);
	for (int i = 0; i < N; i++)
	{
		y[i] = (long long)y[i] * z[i] % M;
	}
	NTT(y, N, -1);
	for (int i = N - 1; i >= 1; i--)
	{
		y[i] = (long long)y[i - 1] * inv[i] % M;
	}
	y[0] = 0;
}

void poly_exp(int n, int *x, int *y)
{
	static int z[4 * _n];
	if (n == 1)
	{
		y[0] = 1;
		return;
	}
	poly_exp((n + 1) / 2, x, y);
	int N = 1;
	int bit = 0;
	while (N < 2 * n)
	{
		N <<= 1;
		bit++;
	}
	for (int i = 0; i < N; i++)
	{
		z[i] = 0;
	}
	poly_ln(n, y, z);
	for (int i = 0; i < n; i++)
	{
		z[i] = (x[i] - z[i]) % M;
	}
	z[0] = (z[0] + 1) % M;
	for (int i = 0; i < N; i++)
	{
		xx[i] = yy[i] = 0;
	}
	for (int i = 0; i < n; i++)
	{
		xx[i] = y[i];
	}
	for (int i = 0; i < n; i++)
	{
		yy[i] = z[i];
	}
	getrev(bit);
	NTT(xx, N, 1);
	NTT(yy, N, 1);
	for (int i = 0; i < N; i++)
	{
		xx[i] = (long long)xx[i] * yy[i] % M;
	}
	NTT(xx, N, -1);
	for (int i = 0; i < n; i++)
	{
		y[i] = xx[i];
	}
}

int main()
{
	scanf("%d", &n);
	inv[0] = inv[1] = 1;
	for (int i = 2; i <= 4 * n; i++)
	{
		inv[i] = (long long)(M - M / i) * inv[M % i] % M;
	}
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &x[i]);
	}
	poly_exp(n, x, y);
	for (int i = 0; i < n; i++)
	{
		printf("%d ", (y[i] + M) % M);
	}
	puts("");
	return 0;
}


