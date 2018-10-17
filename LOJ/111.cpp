#include <cstdio>
#include <cstring>
#include <algorithm>

const int _n = 1000000 + 10;
int n, m;
char s[_n];
int x[_n];
int SA[_n], rank[_n], tp[_n];
int cnt[_n];

bool cmp(int i, int j, int w)
{
	return tp[i] == tp[j] && tp[i + w] == tp[j + w];
}

void sort(int w)
{
	for (int i = 0; i <= m; i++)
	{
		cnt[i] = 0;
	}
	for (int i = 1; i <= n; i++)
	{
		cnt[rank[tp[i]]]++;
	}
	for (int i = 1; i <= m; i++)
	{
		cnt[i] += cnt[i - 1];
	}
	for (int i = n; i >= 1; i--)
	{
		SA[cnt[rank[tp[i]]]--] = tp[i];
	}
	std::swap(rank, tp);
	rank[SA[1]] = 1;
	for (int i = 2; i <= n; i++)
	{
		rank[SA[i]] = rank[SA[i - 1]] + 1 - cmp(SA[i - 1], SA[i], w);
	}
	m = rank[SA[n]];
}

void Suffix()
{
	for (int i = 1; i <= n; i++)
	{
		rank[i] = x[i];
		tp[i] = i;
	}
	m = 127;
	sort(0);
	for (int w = 1; m < n; w <<= 1)
	{
		int p = 0;
		for (int i = n - w + 1; i <= n; i++)
		{
			p++;
			tp[p] = i;
		}
		for (int i = 1; i <= n; i++)
		{
			if (SA[i] > w)
			{
				p++;
				tp[p] = SA[i] - w;
			}
		}
		sort(w);
	}
}

int main()
{
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for (int i = 1; i <= n; i++)
	{
		x[i] = s[i];
	}
	Suffix();
	for (int i = 1; i <= n; i++)
	{
		printf("%d ", SA[i]);
	}
	puts("");
	return 0;
}
