#include <cstdio>

int n;
double x[2000000];
int cnt[2000000];
double ans;

int main()
{
	scanf("%d", &n);
	n = 1 << n;
	for (int i = 0; i < n; i++)
	{
		scanf("%lf", &x[i]);
	}
	for (int i = 1; i < n; i <<= 1)
	{
		for (int j = 0; j < n; j += (i << 1))
		{
			for (int k = 0; k < i; k++)
			{
				x[j + k + i] += x[j + k];
			}
		}
	}
	ans = 0.0;
	cnt[0] = 0;
	for (int i = 1; i < n; i++)
	{
		cnt[i] = cnt[i >> 1] + (i & 1);
		ans = ans + (cnt[i] % 2 == 0 ? -1 : 1) * 1.0 / (1.0 - x[n - 1 - i]);
	}
	printf("%.8f\n", ans);
	return 0;
}
