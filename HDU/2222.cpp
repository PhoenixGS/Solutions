#include <cstdio>
#include <cstring>
#include <queue>

int T;
int n;
char st[2000000];
int ch[500005][30];
int value[500005];
int f[500005];
int last[500005];
int knum;
int ans;

void add(char *st, int id)
{
	int u = 0;
	int n = strlen(st + 1);
	for (int i = 1; i <= n; i++)
	{
		if (! ch[u][st[i] - 'a'])
		{
			knum++;
			ch[u][st[i] - 'a'] = knum;
		}
		u = ch[u][st[i] - 'a'];
	}
	value[u]++;
}

void getFail()
{
	std::queue<int> que;
	f[0] = 0;
	last[0] = 0;
	for (int i = 0; i < 26; i++)
	{
		if (ch[0][i])
		{
			que.push(ch[0][i]);
			f[ch[0][i]] = 0;
			last[ch[0][i]] = 0;
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
		ans += value[k];
		value[k] = 0;
		k = last[k];
	}
}

void find(char *st)
{
	int u = 0;
	int n = strlen(st + 1);
	for (int i = 1; i <= n; i++)
	{
		u = ch[u][st[i] - 'a'];
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
	scanf("%d", &T);
	while (T--)
	{
		knum = 0;
		memset(ch, 0, sizeof(ch));
		memset(last, 0, sizeof(last));
		memset(f, 0, sizeof(f));
		memset(value, 0, sizeof(value));
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
		{
			scanf("%s", st + 1);
			add(st, i);
		}
		getFail();
		scanf("%s", st + 1);
		ans = 0;
		find(st);
		printf("%d\n", ans);
	}
	return 0;
}
