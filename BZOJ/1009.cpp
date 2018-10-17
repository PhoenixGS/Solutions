#include <cstdio>
#include <cstring>
#include <queue>

int f[100];
int ch[100][20];
int ans[100][100];
int tmp[100][100];
int kk[100][100];
int n, m, M;
int knum;
int anss;
char st[10000];

void add(char *st)
{
	int u = 0;
	int n = strlen(st + 1);
	for (int i = 1; i <= n; i++)
	{
		if (! ch[u][st[i] - '0'])
		{
			knum++;
			ch[u][st[i] - '0'] = knum;
		}
		u = ch[u][st[i] - '0'];
	}
}

void getFail()
{
	std::queue<int> que;
	f[0] = 0;
	for (int i = 0; i < 10; i++)
	{
		if (ch[0][i])
		{
			f[ch[0][i]] = 0;
			que.push(ch[0][i]);
		}
	}
	while (! que.empty())
	{
		int u = que.front();
		que.pop();
		for (int i = 0; i < 10; i++)
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
	knum = 0;
	scanf("%d%d%d", &n, &m, &M);
	scanf("%s", st + 1);
	add(st);
	getFail();
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (ch[i][j] != m)
			{
				tmp[i][ch[i][j]]++;
			}
		}
	}
	for (int i = 0; i < m; i++)
	{
		ans[i][i] = 1;
	}
	while (n)
	{
		if (n & 1)
		{
			memset(kk, 0, sizeof(kk));
			for (int i = 0; i < m; i++)
			{
				for (int j = 0; j < m; j++)
				{
					for (int k = 0; k < m; k++)
					{
						kk[i][k] = ((long long)kk[i][k] + (long long)ans[i][j] * tmp[j][k]) % M;
					}
				}
			}
			for (int i = 0; i < m; i++)
			{
				for (int j = 0; j < m; j++)
				{
					ans[i][j] = kk[i][j];
				}
			}
		}
		memset(kk, 0, sizeof(kk));
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < m; j++)
			{
				for (int k = 0; k < m; k++)
				{
					kk[i][k] = ((long long)kk[i][k] + (long long)tmp[i][j] * tmp[j][k]) % M;
				}
			}
		}
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < m; j++)
			{
				tmp[i][j] = kk[i][j];
			}
		}
		n >>= 1;
	}
	anss = 0;
	for (int i = 0; i < m; i++)
	{
		(anss += ans[0][i]) %= M;
	}
	printf("%d\n", anss);
	return 0;
}
