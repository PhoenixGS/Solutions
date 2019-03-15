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

const int M = 998244353;
const int G = 3;
const int _n = 100000 + 10;
int n;
int x[4 * _n];
int ans[4 * _n];
int xx[4 * _n], yy[4 * _n];
int rev[4 * _n];

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
	for (int i = 0; i < (1 << bit); i++)
	{
		rev[i] = rev[i >> 1] >> 1 | ((i & 1) << (bit - 1));
	}
}

void NTT(int *x, int bit, int cas)
{
	int n = (1 << bit);

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

void solve(int n)
{
	if (n == 1)
	{
		ans[0] = 1 * pow_mod(x[0], M - 2, M);
//		printf("#%d\n%d\n", 1, ans[0]);
		return;
	}

	solve((n + 1) >> 1);

//	printf("#%d\n", n);

	int nn = 1, bit = 0;
	while (nn <= 2 * n)
	{
		nn <<= 1;
		bit++;
	}

	for (int i = 0; i < nn; i++)
	{
		xx[i] = yy[i] = 0;
	}
	for (int i = 0; i < n; i++)
	{
		xx[i] = x[i];
	}
	for (int i = 0; i < ((n + 1) >> 1); i++)
	{
		yy[i] = ans[i];
	}

/*	for (int i = 0; i < nn; i++)
	{
		printf("%d ", xx[i]);
	}
	puts("");*/

	getrev(bit);

/*	for (int i = 0; i < nn; i++)
	{
		printf("%d ", rev[i]);
	}
	puts("");*/

	NTT(xx, bit, 1);
	NTT(yy, bit, 1);
	for (int i = 0; i < nn; i++)
	{
//		xx[i] = (long long)xx[i] * yy[i] % M * yy[i] % M;
		xx[i] = (long long)xx[i] * yy[i] % M * yy[i] % M;
	}
	NTT(xx, bit, -1);
/*	for (int i = 0; i < nn; i++)
	{
		printf("%d ", xx[i]);
	}
	puts("");*/


	for (int i = 0; i < n; i++)
	{
		ans[i] = ((long long)2 * ans[i] - xx[i] + M) % M;
	}
/*	for (int i = 0; i < n; i++)
	{
		printf("%d ", ans[i]);
	}
	puts("");*/
}

int main()
{
	n = read();
	for (int i = 0; i < n; i++)
	{
		x[i] = read();
	}
	solve(n);
	for (int i = 0; i < n; i++)
	{
		printf("%d ", ans[i]);
	}
	puts("");
	return 0;
}
