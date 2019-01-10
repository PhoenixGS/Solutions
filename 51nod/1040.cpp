#include <cstdio>
#include <cmath>

int n;

int phi(int x)
{
	int ans = x;
	int tmp = x;
	for (int i = 2; i <= sqrt(tmp); i++)
	{
		if (tmp % i == 0)
		{
			ans = ans / i * (i - 1);
			while (tmp % i == 0)
			{
				tmp = tmp / i;
			}
		}
	}
	if (tmp > 1)
	{
		ans = ans / tmp * (tmp - 1);
	}
	return ans;
}

int main()
{
	scanf("%d", &n);
	long long ans = 0;
	for (int i = 1; i <= sqrt(n); i++)
	{
		if (n % i == 0)
		{
			ans += (long long)i * phi(n / i);
			if (i * i != n)
			{
				ans += (long long)n / i * phi(i);
			}
		}
	}
	printf("%lld\n", ans);
	return 0;
}
