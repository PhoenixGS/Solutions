#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

int n;
char st[200][100];
char s[2000000];
int knum;
int ch[20000][26], idx[20000], f[20000], sum[20000], deg[20000];
int ansn;
int ans[20000];

void add(char *s, int pos)
{
	int u = 0;
	int len = strlen(s + 1);
	for (int i = 1; i <= len; i++)
	{
		if (! ch[u][s[i] - 'a'])
		{
			knum++;
			ch[u][s[i] - 'a'] = knum;
		}
		u = ch[u][s[i] - 'a'];
	}
	idx[u] = pos;
}

void getFail()
{
	std::queue<int> que;
	f[0] = 0;
	for (int i = 0; i < 26; i++)
	{
		int u = ch[0][i];
		if (u)
		{
			f[u] = 0;
			que.push(u);
		}
	}
	while (! que.empty())
	{
		int u = que.front();
		que.pop();
		for (int i = 0; i < 26; i++)
		{
			int v = ch[u][i];
			if (! v)
			{
				ch[u][i] = ch[f[u]][i];
				continue;
			}
			f[v] = ch[f[u]][i];
			que.push(v);
		}
	}
}

int main()
{
	while (scanf("%d", &n) == 1 && n)
	{
		for (int i = 0; i <= knum; i++)
		{
			for (int j = 0; j < 26; j++)
			{
				ch[i][j] = 0;
			}
			sum[i] = idx[i] = f[i] = 0;
			deg[i] = 0;
		}
		knum = 0;
		for (int i = 1; i <= n; i++)
		{
			scanf("%s", st[i] + 1);
			add(st[i], i);
		}
		getFail();
		scanf("%s", s + 1);
		int len = strlen(s + 1);
		int now = 0;
		for (int i = 1; i <= len; i++)
		{
			now = ch[now][s[i] - 'a'];
			sum[now]++;
		}
		for (int i = 1; i <= knum; i++)
		{
			deg[f[i]]++;
		}
		std::queue<int> que;
		for (int i = 1; i <= knum; i++)
		{
			if (deg[i] == 0)
			{
				que.push(i);
			}
		}
		while (! que.empty())
		{
			int u = que.front();
			que.pop();
			if (f[u])
			{
				sum[f[u]] += sum[u];
				deg[f[u]]--;
				if (deg[f[u]] == 0)
				{
					que.push(f[u]);
				}
			}
		}
		int maxx = 0;
		for (int i = 1; i <= knum; i++)
		{
			if (idx[i])
			{
				maxx = std::max(maxx, sum[i]);
			}
		}
		printf("%d\n", maxx);
		ansn = 0;
		for (int i = 1; i <= knum; i++)
		{
			if (sum[i] == maxx && idx[i])
			{
				ansn++;
				ans[ansn] = idx[i];
			}
		}
		std::sort(ans + 1, ans + ansn + 1);
		for (int i = 1; i <= ansn; i++)
		{
			printf("%s\n", st[ans[i]] + 1);
		}
	}
	return 0;
}
