#include <cstdio>
#include <cstring>
#include <queue>

const int M = 10007;
const int _num = 6000 + 10, _m = 100 + 10;;
int n, m;
char s[200];
int num;
int ch[_num][26], suf[_num], danger[_num];
int f[_m][_num];
int ans;
std::queue<int> que;

void insert(char *s)
{
	int u = 0;
	int n = strlen(s + 1);
	for (int i = 1; i <= n; i++)
	{
		if (! ch[u][s[i] - 'A'])
		{
			num++;
			ch[u][s[i] - 'A'] = num;
		}
		u = ch[u][s[i] - 'A'];
	}
	danger[u] = 1;
}

void init()
{
	for (int i = 0; i < 26; i++)
	{
		if (ch[0][i])
		{
			que.push(ch[0][i]);
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
				ch[u][i] = ch[suf[u]][i];
				continue;
			}
			que.push(v);
			suf[v] = ch[suf[u]][i];
			danger[v] = danger[v] | danger[suf[v]];
		}
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%s", s + 1);
		insert(s);
	}
	init();
	f[0][0] = 1;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j <= num; j++)
		{
			for (int k = 0; k < 26; k++)
			{
				int v = ch[j][k];
				if (! danger[v])
				{
					(f[i + 1][v] += f[i][j]) %= M;
				}
			}
		}
	}
	ans = 1;
	for (int i = 1; i <= m; i++)
	{
		ans = (long long)ans * 26 % M;
	}
	for (int i = 0; i <= num; i++)
	{
		ans = (ans - f[m][i] + M) % M;
	}
	printf("%d\n", ans);
	return 0;
}
