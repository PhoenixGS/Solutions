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

const int M = 1004535809;
const int G = 3;
const int _m = 8000 + 10;
int n, m, key, c;
int pow[_m];
int nn, bit;
int rev[4 * _m];
int ans[4 * _m], tmp[4 * _m];

bool check(int G)
{
	for (int i = 1; i < m; i++)
	{
		pow[i] = -1;
	}
	pow[1] = 0;
	int tmp = 1;
	for (int i = 1; i < m - 1; i++)
	{
		tmp = (long long)tmp * G % m;
		pow[tmp] = i;
	}
	for (int i = 1; i < m; i++)
	{
		if (pow[i] == -1)
		{
			return false;
		}
	}
	return true;
}

int pow_mod(int x, int p, int M)
{
	p = (p % (M - 1) + (M - 1)) % (M - 1);
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
	freopen("3992.in", "r", stdin);
#endif
	scanf("%d%d%d%d", &n, &m, &key, &c);
	for (int i = 2; ; i++)
	{
		if (check(i))
		{
			break;
		}
	}
	nn = 1;
	bit = 0;
	while (nn <= 2 * m)
	{
		nn <<= 1;
		bit++;
	}
	getrev(bit);
	ans[0] = 1;
	for (int i = 1; i <= c; i++)
	{
		int x = read();
		if (! x)
		{
			continue;
		}
		(tmp[pow[x]] += 1) %= M;
	}
	while (n)
	{
		if (n & 1)
		{
			NTT(ans, nn, 1);
			NTT(tmp, nn, 1);
			for (int i = 0; i < nn; i++)
			{
				ans[i] = (long long)ans[i] * tmp[i] % M;
			}
			NTT(ans, nn, -1);
			NTT(tmp, nn, -1);
			for (int i = m - 1; i < nn; i++)
			{
				(ans[i % (m - 1)] += ans[i]) %= M;
				ans[i] = 0;
			}
		}
		NTT(tmp, nn, 1);
		for (int i = 0; i < nn; i++)
		{
			tmp[i] = (long long)tmp[i] * tmp[i] % M;
		}
		NTT(tmp, nn, -1);
		for (int i = m - 1; i < nn; i++)
		{
			(tmp[i % (m - 1)] += tmp[i]) %= M;
			tmp[i] = 0;
		}
		n >>= 1;
	}
	printf("%d\n", key == 0 ? 0 : ans[pow[key]]);
	return 0;
}
