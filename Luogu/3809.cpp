#include <cstdio>
#include <cstring>
#include <algorithm>

const int _n = 1000000 + 10;
int n;
char s[_n];

namespace suf
{
	int m;
	int sa[_n], rk[_n], tp[_n];
	int cnt[_n];
	
	void RadixSort()
	{
		for (int i = 0; i <= m; i++)
		{
			cnt[i] = 0;
		}
		for (int i = 1; i <= n; i++)
		{
			cnt[rk[tp[i]]]++;
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

	void SuffixSort()
	{
		m = 127;
		for (int i = 1; i <= n; i++)
		{
			rk[i] = s[i];
			tp[i] = i;
		}
		RadixSort();
		for (int w = 1, p = 0; w <= n; w <<= 1, m = p)
		{
			p = 0;
			for (int i = n - w + 1; i <= n; i++)
			{
				p++;
				tp[p] = i;
			}
			for (int i = 1; i <= n; i++)
			{
				if (sa[i] - w >= 1)
				{
					p++;
					tp[p] = sa[i] - w;
				}
			}
			RadixSort();
			std::swap(tp, rk);
			rk[sa[1]] = 1;
			for (int i = 2; i <= n; i++)
			{
				rk[sa[i]] = rk[sa[i - 1]] + ! (tp[sa[i]] == tp[sa[i - 1]] && tp[std::min(n + 1, sa[i] + w)] == tp[std::min(n + 1, sa[i - 1] + w)]);
			}
			p = rk[sa[n]];
		}
	}
}

int main()
{
	scanf("%s", s + 1);
	n = strlen(s + 1);
	suf::SuffixSort();
	for (int i = 1; i <= n; i++)
	{
		printf("%d ", suf::sa[i]);
	}
	puts("");
	return 0;
}
