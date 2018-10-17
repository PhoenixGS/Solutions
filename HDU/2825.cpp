#include <cstdio>
#include <queue>
#include <cstring>

int knum;
int ch[2000][30];
int fail[2000];
int value[2000];
int f[30][110][1030];
const int M = 20090717;
char st[1000];
int ans;
int n, m, k;

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
	value[u] = 1 << (id - 1);
}

void getFail()
{
	std::queue<int> que;
	fail[0] = 0;
	for (int i = 0; i < 26; i++)
	{
		if (ch[0][i])
		{
			que.push(ch[0][i]);
			fail[ch[0][i]] = 0;
		}
	}
	while (! que.empty())
	{
		int u = que.front();
		que.pop();
		for (int i = 0; i < 26; i++)
		{
			if (! ch[u][i])
			{
				ch[u][i] = ch[fail[u]][i];
				continue;
			}
			int v = ch[u][i];
			que.push(v);
			fail[v] = ch[fail[u]][i];
			value[v] = value[v] | value[fail[v]];
		}
	}
}

int lowbit(int x)
{
	return x & -x;
}

int count(int x)
{
	int cnt = 0;
	while (x)
	{
		cnt++;
		x -= lowbit(x);
	}
	return cnt;
}

int main()
{
	while (scanf("%d%d%d", &n, &m, &k) == 3 && (n || m || k))
	{
		knum = 0;
		memset(ch, 0, sizeof(ch));
		memset(fail, 0, sizeof(fail));
		memset(f, 0, sizeof(f));
		memset(value, 0, sizeof(value));
		for (int i = 1; i <= m; i++)
		{
			scanf("%s", st + 1);
			add(st, i);
		}
		getFail();
		f[0][0][0] = 1;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j <= knum; j++)
			{
				for (int cas = 0; cas < (1 << m); cas++)
				{
					if (f[i][j][cas] > 0)
					{
						for (int k = 0; k < 26; k++)
						{
							(f[i + 1][ch[j][k]][cas | value[ch[j][k]]] += f[i][j][cas]) %= M;
						}
					}
				}
			}
		}
		ans = 0;
		for (int cas = 0; cas < (1 << m); cas++)
		{
			if (count(cas) >= k)
			{
				for (int i = 0; i <= knum; i++)
				{
					(ans += f[n][i][cas]) %= M;
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
