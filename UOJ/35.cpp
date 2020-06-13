void rsort()
{
	for (int i = 0; i <= m; i++)
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
	for (int w = 1, p = 0; w <= n && p < n; w <<= 1, m = p)
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

}
