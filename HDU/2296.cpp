#include <cstdio>
#include <cstring>
#include <string>
#include <queue>
#include <iostream>

int T;
int knum;
int n, m;
int ch[2000][30];
int key[2000];
int fail[2000];
int value[2000];
int val[2000];
int f[60][2000];
std::string s[60][2000];
int ans;
std::string anss;
char st[2000];

std::string check(std::string x, std::string y)
{
	if (x.length() != y.length())
	{
		return x.length() < y.length() ? x : y;
	}
	return x < y ? x : y;
}

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
	key[u] = id;
}

void getFail()
{
	std::queue<int> que;
	fail[0] = 0;
	value[0] = 0;
	for (int i = 0; i < 26; i++)
	{
		if (ch[0][i])
		{
			fail[ch[0][i]] = 0;
			value[ch[0][i]] = key[ch[0][i]] ? val[key[ch[0][i]]] : 0;
			que.push(ch[0][i]);
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
			value[v] = value[fail[v]] + key[v] ? val[key[v]] : 0;
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
		memset(f, 0, sizeof(f));
		memset(value, 0, sizeof(value));
		memset(key, 0, sizeof(key));
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= m; i++)
		{
			scanf("%s", st + 1);
			add(st, i);
		}
		for (int i = 1; i <= m; i++)
		{
			scanf("%d", &val[i]);
		}
		getFail();
		ans = 0;
		anss = "";
		for (int i = 0; i <= n; i++)
		{
			for (int j = 0; j <= knum; j++)
			{
				f[i][j] = -1;
				s[i][j] = "";
			}
		}
		f[0][0] = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j <= knum; j++)
			{
				if (f[i][j] != -1)
				{
					for (int k = 0; k < 26; k++)
					{
						if (f[i][j] + value[ch[j][k]] >= f[i + 1][ch[j][k]])
						{
							char tt = 'a' + k;
							if (f[i][j] + value[ch[j][k]] > f[i + 1][ch[j][k]])
							{
								f[i + 1][ch[j][k]] = f[i][j] + value[ch[j][k]];
								s[i + 1][ch[j][k]] = s[i][j] + tt;
							}
							else
							{
								s[i + 1][ch[j][k]] = check(s[i + 1][ch[j][k]], s[i][j] + tt);
							}
							if (f[i + 1][ch[j][k]] > ans)
							{
								ans = f[i + 1][ch[j][k]];
								anss = s[i + 1][ch[j][k]];
							}
							else
							{
								if (f[i + 1][ch[j][k]] == ans)
								{
									anss = check(anss, s[i + 1][ch[j][k]]);
								}
							}
						}
					}
				}
			}
		}
		std::cout << anss << std::endl;
	}
	return 0;
}
