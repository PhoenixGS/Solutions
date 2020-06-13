#include <cstdio>
#include <cstring>
#include <algorithm>

const int _n = 1000000 + 10;
int n;
char s[_n];

namespace suf
{
	int zz;
	int sa[_n], rank[_n], tp[_n], cnt[_n];

	void Sort()
	{
		for (int i = 0; i <= zz; i++)
		{
			cnt[i] = 0;
		}
		for (int i = 1; i <= n; i++)
		{
			cnt[rank[tp[i]]]++;
		}
		for (int i = 1; i <= zz; i++)
		{
			cnt[i] += cnt[i - 1];
		}
		for (int i = n; i >= 1; i--)
		{
			sa[cnt[rank[tp[i]]]--] = tp[i];
		}
	}

	int cmp(int *f, int x, int y, int w)
	{
		return f[x] == f[y] && f[x + w] == f[y + w];
	}

	void Suffix()
	{
		for (int i = 1; i <= n; i++)
		{
			rank[i] = s[i];
			tp[i] = i;
		}
		zz = 127;
		Sort();
		for (int w = 1, p = 1, i; w < n; w <<= 1, zz = p)
		{
			for (p = 0, i = n - w + 1; i <= n; i++)
			{
				p++;
				tp[p] = i;
			}
			for (int i = 1; i <= n; i++)
			{
				if (sa[i] - w > 0)
				{
					p++;
					tp[p] = sa[i] - w;
				}
			}
			Sort();
			std::swap(rank, tp);
			rank[sa[1]] = p = 1;
			for (int i = 2; i <= n; i++)
			{
				rank[sa[i]] = cmp(tp, sa[i - 1], sa[i], w) ? p : ++p;
			}
		}
	}
}

int main()
{
	scanf("%s", s + 1);
	n = strlen(s + 1);
	suf::Suffix();
	for (int i = 1; i <= n; i++)
	{
		printf("%d ", suf::sa[i]);
	}
	puts("");
	return 0;
}
