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

const int M = 1000000009;
const int _b = 20 + 3, _n = 2000000 + 10;
int bit, n;
int cnt[_n];
int x[_b][_n], y[_b][_n], z[_b][_n];

void FWT(int *x, int n, int cas)
{
	for (int i = 1; i < n; i <<= 1)
	{
		for (int j = 0; j < n; j += (i << 1))
		{
			for (int k = 0; k < i; k++)
			{
				if (cas == 1)
				{
					x[j + k + i] = (x[j + k + i] + x[j + k]) % M;
				}
				else
				{
					x[j + k + i] = (x[j + k + i] - x[j + k] + M) % M;
				}
			}
		}
	}
}

int main()
{
	scanf("%d", &bit);
	n = 1 << bit;
	cnt[0] = 0;
	for (int i = 1; i < n; i++)
	{
		cnt[i] = cnt[i >> 1] + (i & 1);
	}
	for (int i = 0; i < n; i++)
	{
		x[cnt[i]][i] = read();
	}
	for (int i = 0; i < n; i++)
	{
		y[cnt[i]][i] = read();
	}
	for (int i = 0; i <= bit; i++)
	{
		FWT(x[i], n, 1);
		FWT(y[i], n, 1);
	}
	for (int i = 0; i <= bit; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			for (int k = 0; k < n; k++)
			{
				z[i][k] = (z[i][k] + (long long)x[j][k] * y[i - j][k] % M) % M;
			}
		}
	}
	for (int i = 0; i <= bit; i++)
	{
		FWT(z[i], n, -1);
	}
	for (int i = 0; i < n; i++)
	{
		printf("%d ", z[cnt[i]][i]);
	}
	puts("");
	return 0;
}
