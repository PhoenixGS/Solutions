#include <cstdio>

int check(long long M)
{
	


int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		x[i] = read();
	}
	long long l = -INF;
	long long r = INF;
	while (l < r)
	{
		long long mid = (l + r) >> 1;
		if (check(mid) >= need)
		{
			r = mid;
		}
		else
		{
			l = mid + 1;
		}
	}
	printf("%lld\n", ans + l * need);
	return 0;
}
		
