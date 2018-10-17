#include <cstdio>
#include <algorithm>

int n;
int cnt[2000];
int x[2000][2000];
int last;
int st[3000000], bel[3000000], nextx[3000000];
int *s, *belong;
int maxx[2000];
int ans;
int begin[2000];

void getfail()
{
	nextx[0] = nextx[1] = 0;
	int j = 0;
	for (int i = 2; i <= last; i++)
	{
		while (j && s[j + 1] != s[i])
		{
			j = nextx[j];
		}
		if (s[j + 1] == s[i])
		{
			j++;
		}
		nextx[i] = j;
		int pos = belong[i];
		maxx[pos] = std::max(maxx[pos], std::min(nextx[i], i - begin[pos] + 1));
	}
}

int main()
{
	s = st;
	belong = bel;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &cnt[i]);
		for (int j = 1; j <= cnt[i]; j++)
		{
			scanf("%d", &x[i][j]);
		}
		cnt[i]--;
		for (int j = 1; j <= cnt[i]; j++)
		{
			x[i][j] = x[i][j + 1] - x[i][j];
		}
	}
	last = 0;
	for (int i = 1; i <= n; i++)
	{
		begin[i] = last + 1;
		for (int j = 1; j <= cnt[i]; j++)
		{
			last++;
			s[last] = x[i][j];
			belong[last] = i;
		}
		last++;
		s[last] = -1000000000 - i;
	}
	ans = 0;
	while (cnt[1])
	{
		for (int j = 1; j <= n; j++)
		{
			maxx[j] = 0;
		}
		getfail();
		int tmp = 1000000000;
		for (int j = 2; j <= n; j++)
		{
			tmp = std::min(tmp, maxx[j]);
		}
		tmp = std::min(tmp, cnt[1]);
		ans = std::max(ans, tmp);
		s++;
		belong++;
		cnt[1]--;
		last--;
		for (int j = 2; j <= n; j++)
		{
			begin[j]--;
		}
	}
	printf("%d\n", ans + 1);
	return 0;
}
