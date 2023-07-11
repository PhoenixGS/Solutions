#include <cstdio>
#include <cmath>
#include <algorithm>

const double eps = 1e-9;
const int _n = 100 + 10;
int n;
double x[_n][_n];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n + 1; j++)
		{
			scanf("%lf", &x[i][j]);
		}
	}
	for (int i = 1; i <= n; i++)
	{
		int mx = i;
		for (int j = i + 1; j <= n; j++)
		{
			if (fabs(x[j][i]) > fabs(x[mx][i]))
			{
				mx = j;
			}
		}
		for (int j = 1; j <= n + 1; j++)
		{
			std::swap(x[i][j], x[mx][j]);
		}
		if (fabs(x[i][i]) < eps)
		{
			puts("No Solution");
			return 0;
		}
		for (int j = 1; j <= n; j++)
		{
			if (j != i)
			{
				double d = x[j][i] / x[i][i];
				for (int k = i; k <= n + 1; k++)
				{
					x[j][k] -= x[i][k] * d;
				}
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		printf("%.2f\n", x[i][n + 1] / x[i][i]);
	}
	return 0;
}
