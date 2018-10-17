#include <cstdio>
#include <cstring>
#include <queue>

int n;
char st[1005][60];
int ch[60000][30];
int value[60000];
int f[60000];
int last[60000];
int ans[2000];
char s[3000000];
int knum;

void add(char *st, int id)
{
	int u = 0;
	int n = strlen(st + 1);
	for (int i = 1; i <= n; i++)
	{
		if (! ch[u][st[i] - 'A'])
		{
			knum++;
			ch[u][st[i] - 'A'] = knum;
		}
		u = ch[u][st[i] - 'A'];
	}
	value[u] = id;
}

void getFail()
{
	std::queue<int> que;
	f[0] = 0;
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
		ans[value[k]]++;
		k = last[k];
	}
}

void find(char *s)
{
	int u = 0;
	int n = strlen(s + 1);
	for (int i = 1; i <= n; i++)
	{
		if (s[i] >= 'A' && s[i] <= 'Z')
		{
			u = ch[u][s[i] - 'A'];
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
		else
		{
			u = 0;
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
		memset(ans, 0, sizeof(ans));
		for (int i = 1; i <= n; i++)
		{
			scanf("%s", st[i] + 1);
			add(st[i], i);
		}
		getFail();
		scanf("%s", s + 1);
		find(s);
		for (int i = 1; i <= n; i++)
		{
			if (ans[i])
			{
				printf("%s: %d\n", st[i] + 1, ans[i]);
			}
		}
	}
	return 0;
}
