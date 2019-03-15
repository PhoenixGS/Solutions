#include <cstdio>

const int M = 1000000007;
int flag[60000];
int ans[120000], tmp[120000];
int tmpx[120000], tmpy[120000];
int n, invn;
int t, m;

void print(int *x)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", x[i]);
	}
	puts("");
}

int pow_mod(int x, int p, int M)
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

void FWT(int *x)
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
				x[j + k + i] = (xx - yy + M) % M;
			}
		}
	}
}

void mul(int *x, int *y)
{
	for (int i = 0; i < n; i++)
	{
		x[i] = (long long)x[i] * y[i] % M;
	}
}

int main()
{
	flag[0] = 1;
	flag[1] = 1;
	for (int i = 2; i <= 50005; i++)
	{
		if (! flag[i])
		{
			for (int j = i + i; j <= 50005; j += i)
			{
				flag[j] = 1;
			}
		}
	}
	while (scanf("%d%d", &t, &m) != EOF)
	{
		n = 1;
		for (n = 1; n <= m; n <<= 1);
		invn = pow_mod(n, M - 2, M);
		for (int i = 0; i < n; i++)
		{
			ans[i] = 0;
			tmp[i] = 0;
		}
		ans[0] = 1;
		for (int i = 0; i <= m; i++)
		{
			tmp[i] = 1 - flag[i];
		}
		FWT(ans);
		FWT(tmp);
		while (t)
		{
			if (t & 1)
			{
				mul(ans, tmp);
			}
			mul(tmp, tmp);
			t >>= 1;
		}
		FWT(ans);
		for (int i = 0; i < n; i++)
		{
			ans[i] = (long long)ans[i] * invn % M;
		}
		printf("%d\n", ans[0]);
	}
	return 0;
}
