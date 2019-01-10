#include <cstdio>
#include <cstring>
#include <algorithm>

int n;
char s[2000000];
int fail[2000000], nextx[2000000];

void getfail()
{
	int j = 0;
	for (int i = 2; i <= n; i++)
	{
		while (j && s[j + 1] != s[i])
		{
			j = fail[j];
		}
		if (s[j + 1] == s[i])
		{
			j++;
		}
		fail[i] = j;
	}
}

void getnextx()
{
	nextx[1] = n;
	int pos = -1, last = -1;
	for (int i = 2; i <= n; i++)
	{
		int k = (pos == -1 || i > last) ? 0 : std::min(nextx[i - pos + 1], last - i + 1);
		while (k < n && s[k + 1] == s[i + k])
		{
			k++;
		}
		nextx[i] = k;
		if (i + nextx[i] - 1 > last)
		{
			pos = i;
			last = i + nextx[i] - 1;
		}
	}
}

void solve()
{
	scanf("%s", s + 1);
	n = strlen(s + 1);
	getfail();
	getnextx();
	int maxx = 0;
	int k = fail[n];
	for (; k * 3 > n; k = fail[k]);
	int l = k + 1;
	int r = n - k;
	for (int i = l; i <= r; i++)
	{
		maxx = std::max(maxx, nextx[i]);
	}
	if (maxx >= k)
	{
		if (k == 0)
		{
			puts("---");
			return;
		}
		for (int i = 1; i <= k; i++)
		{
			printf("%c", s[i]);
		}
		puts("");
		return;
	}
	for (; k; k = fail[k])
	{
		int ll = k + 1;
		int rr = n - k;
		for (int i = ll; i < l; i++)
		{
			maxx = std::max(maxx, nextx[i]);
		}
		for (int i = r + 1; i <= rr; i++)
		{
			maxx = std::max(maxx, nextx[i]);
		}
		l = ll;
		r = rr;
		if (maxx >= k)
		{
			if (k == 0)
			{
				puts("---");
				return;
			}
			for (int i = 1; i <= k; i++)
			{
				printf("%c", s[i]);
			}
			puts("");
			return;
		}
	}
	puts("---");
	return;
}

int main()
{
	freopen("fool.in", "r", stdin);
	freopen("fool.out", "w", stdout);
	int T;
	scanf("%d", &T);
	while (T--)
	{
		solve();
	}
	return 0;
}
