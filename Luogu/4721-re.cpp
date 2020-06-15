#include <cstdio>
#include <algorithm>

long long read()
{
    char last = '+', ch = getchar();
    while (ch < '0' || ch > '9') last = ch, ch = getchar();
    long long tmp = 0;
    while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
    if (last == '-') tmp = -tmp;
    return tmp;
}

const int M = 998244353, G = 3;
const int _n = 100000 + 10;
int n;
int f[4 * _n], g[4 * _n];
int xx[4 * _n], yy[4 * _n];
int rev[4 * _n];

inline int pow_mod(int x, int p, int M)
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
		for (int j = 0; j < n; j += i << 1)
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

void solve(int l, int r)
{
	if (l == r)
	{
		return;
	}
	int mid = (l + r) >> 1;
	solve(l, mid);
	int N = 1;
	int bit = 0;
	while (N <= (r - l + 1) * 2 - 1)
	{
		N <<= 1;
		bit++;
	}
	for (int i = 0; i < N; i++)
	{
		xx[i] = 0;
		yy[i] = 0;
	}
	for (int i = l; i <= r; i++)
	{
		xx[i - l] = g[i - l];
	}
	for (int i = l; i <= mid; i++)
	{
		yy[i - l] = f[i];
	}
	getrev(bit);
	NTT(xx, N, 1);
	NTT(yy, N, 1);
	for (int i = 0; i < N; i++)
	{
		xx[i] = (long long)xx[i] * yy[i] % M;
	}
	NTT(xx, N, -1);
	for (int i = mid + 1; i <= r; i++)
	{
		f[i] = (f[i] + xx[i - l]) % M;
	}
	solve(mid + 1, r);
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i < n; i++)
	{
		scanf("%d", &g[i]);
	}
	f[0] = 1;
	int nn = 1;
	while (nn < n)
	{
		nn <<= 1;
	}
	solve(0, nn - 1);
	for (int i = 0; i < n; i++)
	{
		printf("%d ", f[i]);
	}
	puts("");
	return 0;
}
