#include <cstdio>

long long n, p;

int main()
{
	scanf("%lld%lld", &n, &p);
	long long ans = 1;
	for (long long i = 1; i <= n; i++)
	{
		ans = ans * i % p;
	}
	printf("%lld\n", ans);
	return 0;
}
