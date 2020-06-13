#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>

long long read()
{
	char last = '+', ch = getchar();
	while (ch < '0' || ch > '9') last = ch, ch = getchar();
	long long tmp = 0;
	while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
	if (last == '-') tmp = -tmp;
	return tmp;
}

const int _n = 200000 + 10;
int T;
int n, na, nb, m;
char s[_n];
int tot;
int edgenum;
int vet[6 * _n], nextx[6 * _n], head[6 * _n];
int lst[_n];
int in[6 * _n];
int flag[6 * _n];
long long f[6 * _n];
int lx[2 * _n], rx[2 * _n];
int fa[2 * _n][22];
std::queue<int> que;
std::vector<std::pair<int, int> > vec[2 * _n];

namespace SAM
{
	int knum, last;
	int len[2 * _n], pre[2 * _n], to[2 * _n][26];

	void init()
	{
		for (int i = 1; i <= knum; i++)
		{
			len[i] = pre[i] = 0;
			for (int j = 0; j < 26; j++)
			{
				to[i][j] = 0;
			}
		}
		knum = 1;
		last = 1;
	}

	void extend(int c)
	{
		knum++;
		int u = last;
		int v = knum;
		last = knum;
		len[v] = len[u] + 1;
		for (; u && ! to[u][c]; u = pre[u])
		{
			to[u][c] = v;
		}
		if (! u)
		{
			pre[v] = 1;
			return;
		}
		int w = to[u][c];
		if (len[u] + 1 == len[w])
		{
			pre[v] = w;
			return;
		}
		knum++;
		int neww = knum;
		pre[neww] = pre[w];
		len[neww] = len[u] + 1;
		for (int i = 0; i < 26; i++)
		{
			to[neww][i] = to[w][i];
		}
		pre[w] = pre[v] = neww;
		for (; u && to[u][c] == w; u = pre[u])
		{
			to[u][c] = neww;
		}
	}
}

using namespace SAM;

bool comp(std::pair<int, int> x, std::pair<int, int> y)
{
	return x.first < y.first || (x.first == y.first && x.second > y.second);
}

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
	in[v]++;
}

void append(int idx)
{
	int now = lst[rx[idx]];
	for (int i = 20; i >= 0; i--)
	{
		if (len[fa[now][i]] >= rx[idx] - lx[idx] + 1)
		{
			now = fa[now][i];
		}
	}
	vec[now].push_back(std::make_pair(rx[idx] - lx[idx] + 1, idx));
}

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%s", s + 1);
		n = strlen(s + 1);

		//init
		for (int i = 1; i <= knum; i++)
		{
			vec[i].clear();
		}
		for (int i = 1; i <= tot; i++)
		{
			in[i] = f[i] = flag[i] = 0;
		}
		init();
		tot = 0;
		edgenum = 0;
		memset(head, 0, sizeof(head));

		for (int i = n; i >= 1; i--)
		{
			extend(s[i] - 'a');
			lst[n - i + 1] = last;
//			printf("?%d %d\n", n - i + 1, last);
		}
/*		for (int i = 1; i <= knum; i++)
		{
			printf("..%d %d\n", i, pre[i]);
		}*/
		for (int i = 1; i <= knum; i++)
		{
			fa[i][0] = pre[i];
		}
		for (int j = 1; j <= 20; j++)
		{
			for (int i = 1; i <= knum; i++)
			{
				fa[i][j] = fa[fa[i][j - 1]][j - 1];
			}
		}

		scanf("%d", &na);
		for (int i = 1; i <= na; i++)
		{
			rx[i] = n - read() + 1;
			lx[i] = n - read() + 1;
			append(i);
		}
		scanf("%d", &nb);
		for (int i = 1; i <= nb; i++)
		{
			rx[na + i] = n - read() + 1;
			lx[na + i] = n - read() + 1;
			append(na + i);
		}

		tot = na + nb + knum;
		for (int i = 1; i <= knum; i++)
		{
			std::sort(vec[i].begin(), vec[i].end(), comp);
			int nxt = na + nb + i;
			for (int j = (int)vec[i].size() - 1; j >= 0; j--)
			{
				if (vec[i][j].second <= na)
				{
					tot++;
					add(nxt, tot);
					add(vec[i][j].second, tot);
					nxt = tot;
				}
				else
				{
					add(nxt, vec[i][j].second);
				}
			}
			if (i != 1)
			{
				add(nxt, na + nb + pre[i]);
			}
		}

		scanf("%d", &m);
		for (int i = 1; i <= m; i++)
		{
			int u = read();
			int v = read();
			add(na + v, u);
		}

		for (int i = 1; i <= tot; i++)
		{
			if (! in[i])
			{
				que.push(i);
			}
		}
		while (! que.empty())
		{
			int u = que.front();
			que.pop();
			flag[u] = 1;
			if (1 <= u && u <= na)
			{
				f[u] += rx[u] - lx[u] + 1;
			}
			for (int i = head[u]; i; i = nextx[i])
			{
				int v = vet[i];
				f[v] = std::max(f[v], f[u]);
				in[v]--;
				if (! in[v])
				{
					que.push(v);
				}
			}
		}

		int fff = false;
		long long ans = 0;
		for (int i = 1; i <= tot; i++)
		{
			if (flag[i] == 0)
			{
				fff = true;
				break;
			}
			ans = std::max(ans, f[i]);
		}
		if (fff)
		{
			puts("-1");
		}
		else
		{
			printf("%lld\n", ans);
		}
	}
	return 0;
}

		

