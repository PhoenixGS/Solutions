#include <cstdio>
#include <cstring>
#include <algorithm>

const int _n = 100000 + 10;
int n, m;
char s[_n];
int sa[_n], rk[_n], tp[_n], h[_n], cnt[_n];

void rsort()
{
	for (int i = 1; i <= m; i++)
	{
		cnt[i] = 0;
	}
	for (int i = 1; i <= n; i++)
	{
		cnt[rk[i]]++;
	}
	for (int i = 1; i <= m; i++)
	{
		cnt[i] += cnt[i - 1];
	}
	for (int i = n; i >= 1; i--)
	{
		sa[cnt[rk[tp[i]]]--] = tp[i];
	}
}

void ssort()
{
	for (int i = 1; i <= n; i++)
	{
		rk[i] = s[i];
		tp[i] = i;
	}
	rsort();
	for (int w = 1, p = 0; p < n && w <= n; m = p, w <<= 1)
	{
		p = 0;
		for (int i = n - w + 1; i <= n; i++)
		{
			tp[++p] = i;
		}
		for (int i = 1; i <= n; i++)
		{
			if (sa[i] > w)
			{
				tp[++p] = sa[i] - w;
			}
		}
		rsort();
		std::swap(rk, tp);
		rk[sa[1]] = p = 1;
		for (int i = 2; i <= n; i++)
		{
			if (tp[sa[i]] == tp[sa[i - 1]] && tp[std::min(n + 1, sa[i] + w)] == tp[std::min(n + 1, sa[i - 1] + w)])
			{
				rk[sa[i]] = p;
			}
			else
			{
				rk[sa[i]] = ++p;
			}
		}
	}
}

int main()
{
	scanf("%s", s + 1);
	n = strlen(s + 1);
	m = 127;
	ssort();
	for (int i = 1, j, k = 0; i <= n; i++)
	{
		for (k = k ? k - 1 : k, j = sa[rk[i] - 1]; s[i + k] == s[j + k]; k++);
		h[rk[i]] = k;
	}
	for (int i = 1; i <= n; i++)
	{
		printf("%d ", sa[i]);
	}
	puts("");
	for (int i = 2; i <= n; i++)
	{
		printf("%d ", h[i]);
	}
	puts("");
	return 0;
}
