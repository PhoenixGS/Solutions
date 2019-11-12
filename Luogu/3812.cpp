#include <cstdio>

int n;
long long f[100];

void add(long long x)
{
	for (int i = 50; i >= 0; i--)
	{
		if (x & (1ll << i))
		{
			if (f[i])
			{
				x = x ^ f[i];
			}
			else
			{
				f[i] = x;
				break;
			}
		}
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		long long x;
		scanf("%lld", &x);
		add(x);
	}
	long long ans = 0;
	for (int i = 50; i >= 0; i--)
	{
		if (! (ans & (1ll << i)) && f[i])
		{
			ans = ans ^ f[i];
		}
	}
	printf("%lld\n", ans);
	return 0;
}
