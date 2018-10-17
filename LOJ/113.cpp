#include <cstdio>

int n;
long long v[100];
long long ans;

void insert(long long x)
{
	for (int i = 51; i >= 0; i--)
	{
		if ((1ll << i) & x)
		{
			if (v[i])
			{
				x = x ^ v[i];
			}
			else
			{
				v[i] = x;
				return;
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
		insert(x);
	}
	ans = 0;
	for (int i = 51; i >= 0; i--)
	{
		if ((ans ^ v[i]) > ans)
		{
			ans = ans ^ v[i];
		}
	}
	printf("%lld\n", ans);
	return 0;
}
