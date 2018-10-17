#include <cstdio>
#include <algorithm>

int n;
long long ss;
long long x[200000];
long long v[200000];
long long s;
long long ans;

long long abss(long long x)
{
	return x < 0 ? -x : x;
}

int main()
{
	scanf("%d", &n);
	ss = 0;
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld", &x[i]);
		ss += x[i];
	}
	ss /= n;
	v[1] = 0;
	s = x[1];
	for (int i = 2; i <= n; i++)
	{
		v[i] = (i - 1) * ss - s;
		s += x[i];
	}
	std::sort(v + 1, v + n + 1);
	ans = 0;
	for (int i = 1; i <= n; i++)
	{
		ans += abss(v[(n + 1) / 2] - v[i]);
	}
	printf("%lld\n", ans);
	return 0;
}
