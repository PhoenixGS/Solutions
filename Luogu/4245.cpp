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

const int G = 3;
const int MM[3] = {469762049, 998244353, 1004535809};
const int _n = 100000 + 10;
int M;
int n, m, p;
int nn, bit;
int x[4 * _n], y[4 * _n];
int xx[4 * _n], yy[4 * _n];
int rev[4 * _n];
int z[3][4 * _n];

inline long long mul(long long x, long long y, long long M)
{
	return (x * y - (long long)((long double)x / M * y) * M + M) % M;
}

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

long long extend_gcd(long long a, long long &x, long long b, long long &y)
{
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	long long d = extend_gcd(b, x, a % b, y);
	long long t = y;
	y = x - a / b * y;
	x = t;
	return d;
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
		for (int j = 0; j < n; j += (i << 1))
		{
			int w = 1;
			for (int k = 0; k < i; k++, w = (long long)w * wn % M)
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

int main()
{
#ifdef debug
	freopen("4245.in", "r", stdin);
#endif
	n = read();
	m = read();
	p = read();
	for (int i = 0; i <= n; i++)
	{
		x[i] = read();
	}
	for (int i = 0; i <= m; i++)
	{
		y[i] = read();
	}
	nn = 1;
	bit = 0;
	while (nn <= n + m)
	{
		nn <<= 1;
		bit++;
	}
	getrev(bit);
	for (int cas = 0; cas < 3; cas++)
	{
		for (int i = 0; i < nn; i++)
		{
			xx[i] = yy[i] = 0;
		}
		for (int i = 0; i <= n; i++)
		{
			xx[i] = x[i];
		}
		for (int i = 0; i <= m; i++)
		{
			yy[i] = y[i];
		}
		M = MM[cas];
		NTT(xx, nn, 1);
		NTT(yy, nn, 1);
		for (int i = 0; i < nn; i++)
		{
			xx[i] = (long long)xx[i] * yy[i] % M;
		}
		NTT(xx, nn, -1);
		for (int i = 0; i <= n + m; i++)
		{
			z[cas][i] = xx[i];
		}
	}
	long long t1, t2;
	long long d = extend_gcd(MM[0], t1, MM[1], t2);
	long long lcm = (long long)MM[0] / d * MM[1];
	long long cl = mul(t1, MM[0], lcm);
	long long k = pow_mod(lcm % MM[2], MM[2] - 2, MM[2]);
	for (int i = 0; i <= n + m; i++)
	{
		long long t = (z[0][i] + mul(z[1][i] - z[0][i], cl, lcm)) % lcm;
		t = (t + lcm) % lcm;
		long long v = (long long)(z[2][i] - t) % MM[2] * k % MM[2];
		v = (v + MM[2]) % MM[2];
		printf("%lld ", (lcm % p * v % p + t) % p);
	}
	puts("");
	return 0;
}
