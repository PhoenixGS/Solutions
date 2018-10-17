#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

int n, m;
int knum;
unsigned short int ch[100005][95];
int f[100005];
int last[100005];
int value[100005];
char st[20000];
int anss;
int ans[100];
int cnt;

void add(char *st, int id)
{
	int u = 0;
	int n = strlen(st + 1);
	for (int i = 1; i <= n; i++)
	{
		if (! ch[u][st[i] - 32])
		{
			knum++;
			ch[u][st[i] - 32] = knum;
		}
		u = ch[u][st[i] - 32];
	}
	value[u] = id;
}

void getFail()
{
	std::queue<int> que;
	f[0] = 0;
	last[0] = 0;
	for (int i = 0; i < 95; i++)
	{
		int u = ch[0][i];
		if (u)
		{
			que.push(u);
			f[u] = 0;
			last[u] = 0;
		}
	}
	while (! que.empty())
	{
		int u = que.front();
		que.pop();
		for (int i = 0; i < 95; i++)
		{
			int v = ch[u][i];
			if (! v)
			{
				ch[u][i] = ch[f[u]][i];
				continue;
			}
			que.push(v);
			f[v] = ch[f[u]][i];
			last[v] = value[f[v]] ? f[v] : last[f[v]];
		}
	}
}

void solve(int k)
{
	while (k)
	{
		anss++;
		ans[anss] = value[k];
		k = last[k];
	}
}

void find(char *s)
{
	int u = 0;
	int n = strlen(s + 1);
	for (int i = 1; i <= n; i++)
	{
		u = ch[u][s[i] - 32];
		if (value[u])
		{
			solve(u);
		}
		else
		{
			if (last[u])
			{
				solve(last[u]);
			}
		}
	}
}

int main()
{
	while (scanf("%d", &n) == 1 && n)
	{
		knum = 0;
		memset(ch, 0, sizeof(ch));
		memset(value, 0, sizeof(value));
		memset(last, 0, sizeof(last));
		memset(f, 0, sizeof(f));
		for (int i = 1; i <= n; i++)
		{
			scanf("%s", st + 1);
			add(st, i);
		}
		getFail();
		scanf("%d", &m);
		cnt = 0;
		for (int i = 1; i <= m; i++)
		{
			scanf("%s", st + 1);
			anss = 0;
			find(st);
			if (anss)
			{
				std::sort(ans + 1, ans + anss + 1);
				printf("web %d:", i);
				for (int j = 1; j <= anss; j++)
				{
					printf(" %d", ans[j]);
				}
				printf("\n");
				cnt++;
			}
		}
		printf("total: %d\n", cnt);
	}
	return 0;
}
