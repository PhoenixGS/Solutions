#include <cstdio>
#include <algorithm>

const int _n = 100000 + 10;
int n, k;
int a[_n], b[_n];
double c[_n];

bool comp(double x, double y)
{
	return x > y;
}

bool check(double mid)
{
	for (int i = 1; i <= n; i++)
	{
		c[i] = a[i] - b[i] * mid;
	}
	std::sort(c + 1, c + n + 1, comp);
	double sum = 0.0;
	for (int i = 1; i <= k; i++)
	{
		sum += c[i];
	}
	return sum > 0.0;
}

int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
	}
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &b[i]);
	}
	double l = 0.0;
	double r = 1000000.0;
	for (int times = 1; times <= 60; times++)
	{
		double mid = (l + r) / 2;
		if (check(mid))
		{
			l = mid;
		}
		else
		{
			r = mid;
		}
	}
	printf("%.4f\n", l);
	return 0;
}
