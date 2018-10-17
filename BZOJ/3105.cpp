#include <cstdio>
#include <algorithm>
#include <functional>

int n;
int x[1000];
int v[1000];
long long s, ans;

int add(int x)
{
	for (int i = 30; i >= 0; i--)
	{
		if (x & (1 << i))
		{
			if (v[i])
			{
				x = x ^ v[i];
			}
			else
			{
				v[i] = x;
				return true;
			}
		}
	}
	return false;
}

int main()
{
	scanf("%d", &n);
	s = 0;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x[i]);
		s += x[i];
	}
	std::sort(x + 1, x + n + 1, std::greater<int>());
	ans = 0;
	for (int i = 1; i <= n; i++)
	{
		if (add(x[i]))
		{
			ans += x[i];
		}
	}
	if (! ans)
	{
		puts("-1");
	}
	else
	{
		printf("%lld\n", s - ans);
	}
	return 0;
}
