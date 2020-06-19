#include <cstdio>
#include <cstring>
#include <algorithm>

const int _n = 20000000 + 10;
int n, m;
char s[_n], t[_n];
int z[_n], ex[_n];

inline void getnext(char *s)
{
	z[1] = n;
	for (int i = 2, l = 0, r = 0; i <= n; i++)
	{
		if (i <= r)
		{
			z[i] = std::min(z[i - l + 1], r - i + 1);
		}
		while (i + z[i] <= n && s[i + z[i]] == s[1 + z[i]])
		{
			z[i]++;
		}
		if (i + z[i] - 1 > r)
		{
			l = i;
			r = i + z[i] - 1;
		}
	}
}

inline void exkmp(char *t)
{
	for (int i = 1, l = 0, r = 0; i <= m; i++)
	{
		if (i <= r)
		{
			ex[i] = std::min(z[i - l + 1], r - i + 1);
		}
		while (i + ex[i] <= m && t[i + ex[i]] == s[1 + ex[i]])
		{
			ex[i]++;
		}
		if (i + ex[i] - 1 > r)
		{
			l = i;
			r = i + ex[i] - 1;
		}
	}
}

int main()
{
	scanf("%s", t + 1);
	scanf("%s", s + 1);
	n = strlen(s + 1);
	m = strlen(t + 1);
	getnext(s);
	exkmp(t);
	long long ans = 0;
	for (int i = 1; i <= n; i++)
	{
		ans = ans ^ ((long long)i * (z[i] + 1));
	}
	printf("%lld\n", ans);
	ans = 0;
	for (int i = 1; i <= m; i++)
	{
		ans = ans ^ ((long long)i * (ex[i] + 1));
	}
	printf("%lld\n", ans);
	return 0;
}
