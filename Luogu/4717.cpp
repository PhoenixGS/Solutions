#include <cstdio>

long long read()
{
	char last = '+', ch = getchar();
	while (ch < '0' || ch > '9') last = ch, ch = getchar();
	long long tmp = 0;
	while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
	if (last == '-') tmp = -tmp;
	return tmp;
}

const int M = 998244353, inv2 = (M + 1) / 2;
const int _n = 300000 + 10;
int n;
int x[_n], y[_n];
int xx[_n], yy[_n];

namespace opor
{
	void FWT(int *x, int n)
	{
		for (int i = 1; i < n; i <<= 1)
		{
			for (int j = 0; j < n; j += (i << 1))
			{
				for (int k = 0; k < i; k++)
				{
					int xx = x[j + k];
					int yy = x[j + k + i];
					x[j + k] = xx;
					x[j + k + i] = (xx + yy) % M;
				}
			}
		}
	}

	void DFWT(int *x, int n)
	{
		for (int i = 1; i < n; i <<= 1)
		{
			for (int j = 0; j < n; j += (i << 1))
			{
				for (int k = 0; k < i; k++)
				{
					int xx = x[j + k];
					int yy = x[j + k + i];
					x[j + k] = xx;
					x[j + k + i] = ((yy - xx) % M + M) % M;
				}
			}
		}
	}
}

namespace opand
{
	void FWT(int *x, int n)
	{
		for (int i = 1; i < n; i <<= 1)
		{
			for (int j = 0; j < n; j += (i << 1))
			{
				for (int k = 0; k < i; k++)
				{
					int xx = x[j + k];
					int yy = x[j + k + i];
					x[j + k] = (xx + yy) % M;
					x[j + k + i] = yy;
				}
			}
		}
	}

	void DFWT(int *x, int n)
	{
		for (int i = 1; i < n; i <<= 1)
		{
			for (int j = 0; j < n; j += (i << 1))
			{
				for (int k = 0; k < i; k++)
				{
					int xx = x[j + k];
					int yy = x[j + k + i];
					x[j + k] = ((xx - yy) % M + M) % M;
					x[j + k + i] = yy;
				}
			}
		}
	}
}

namespace opxor
{
	void FWT(int *x, int n)
	{
		for (int i = 1; i < n; i <<= 1)
		{
			for (int j = 0; j < n; j += (i << 1))
			{
				for (int k = 0; k < i; k++)
				{
					int xx = x[j + k];
					int yy = x[j + k + i];
					x[j + k] = (xx + yy) % M;
					x[j + k + i] = ((xx - yy) % M + M) % M;
				}
			}
		}
	}

	void DFWT(int *x, int n)
	{
		for (int i = 1; i < n; i <<= 1)
		{
			for (int j = 0; j < n; j += (i << 1))
			{
				for (int k = 0; k < i; k++)
				{
					int xx = x[j + k];
					int yy = x[j + k + i];
					x[j + k] = (long long)(xx + yy) * inv2 % M;
					x[j + k + i] = ((long long)(xx - yy) * inv2 % M + M) % M;
				}
			}
		}
	}
}

int main()
{
	scanf("%d", &n);
	int N = 1 << n;
	int bit = n;
	for (int i = 0; i < (1 << n); i++)
	{
		x[i] = read();
	}
	for (int i = 0; i < (1 << n); i++)
	{
		y[i] = read();
	}
	for (int i = 0; i < (1 << n); i++)
	{
		xx[i] = x[i];
		yy[i] = y[i];
	}
	opor::FWT(xx, N);
	opor::FWT(yy, N);
	for (int i = 0; i < (1 << n); i++)
	{
		xx[i] = (long long)xx[i] * yy[i] % M;
	}
	opor::DFWT(xx, N);
	for (int i = 0; i < (1 << n); i++)
	{
		printf("%d ", xx[i]);
	}
	puts("");
	for (int i = 0; i < (1 << n); i++)
	{
		xx[i] = x[i];
		yy[i] = y[i];
	}
	opand::FWT(xx, N);
	opand::FWT(yy, N);
	for (int i = 0; i < (1 << n); i++)
	{
		xx[i] = (long long)xx[i] * yy[i] % M;
	}
	opand::DFWT(xx, N);
	for (int i = 0; i < (1 << n); i++)
	{
		printf("%d ", xx[i]);
	}
	puts("");
	for (int i = 0; i < (1 << n); i++)
	{
		xx[i] = x[i];
		yy[i] = y[i];
	}
	opxor::FWT(xx, N);
	opxor::FWT(yy, N);
	for (int i = 0; i < (1 << n); i++)
	{
		xx[i] = (long long)xx[i] * yy[i] % M;
	}
	opxor::DFWT(xx, N);
	for (int i = 0; i < (1 << n); i++)
	{
		printf("%d ", xx[i]);
	}
	puts("");
	return 0;
}
