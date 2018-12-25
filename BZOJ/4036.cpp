#include <cstdio>

const double eps = 1e-7;
const int _N = 2000000 + 10;
int n;
double x[_N];
int bit[_N];
double ans;

double abss(double x)
{
	return x < 0 ? -x : x;
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < (1 << n); i++)
	{
		scanf("%lf", &x[i]);
	}
	for (int i = 1; i < (1 << n); i++)
	{
		bit[i] = bit[i >> 1] + (i & 1);
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < (1 << n); j++)
		{
			if (j & (1 << i))
			{
				x[j] = x[j] + x[j ^ (1 << i)];
			}
		}
	}
	ans = 0.0;
	for (int i = 0; i < (1 << n) - 1; i++)
	{
		if (abss(x[i] - 1.0) < eps)
		{
			puts("INF");
			return 0;
		}
		ans += (((n - bit[i] + 1) & 1) ? -1 : 1) * 1.0 / (1.0 - x[i]);
	}
	printf("%.10f\n", ans);
	return 0;
}
