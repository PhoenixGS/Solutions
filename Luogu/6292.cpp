#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

long long read()
{
	char last = '+', ch = getchar();
	while (ch < '0' || ch > '9') last = ch, ch = getchar();
	long long tmp = 0;
	while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
	if (last == '-') tmp = -tmp;
	return tmp;
}

const int _n = 100000 + 10;
int n, m;
char s[_n];
int pos[_n];
std::vector<std::pair<int, int> > ques[_n];
long long ans[_n];

namespace SAM
{
	int knum, last;
	int pre[2 * _n], len[2 * _n], to[2 * _n][26];

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

	void init()
	{
		knum = 1;
		last = 1;
	}
}

namespace SEG
{
	long long sum[4 * _n], tag[4 * _n];

	void pushdown(int k, int l, int r)
	{
		if (tag[k])
		{
			int mid = (l + r) >> 1;
			sum[k << 1] += tag[k] * (mid - l + 1);
			tag[k << 1] += tag[k];
			sum[k << 1 | 1] += tag[k] * (r - mid);
			tag[k << 1 | 1] += tag[k];
			tag[k] = 0;
		}
	}

	void pushup(int k)
	{
		sum[k] = sum[k << 1] + sum[k << 1 | 1];
	}

	void change(int k, int l, int r, int L, int R, int cas)
	{
		if (L <= l && r <= R)
		{
			sum[k] += cas * (r - l + 1);
			tag[k] += cas;
			return;
		}
		int mid = (l + r) >> 1;
		pushdown(k, l, r);
		if (L <= mid)
		{
			change(k << 1, l, mid, L, R, cas);
		}
		if (R > mid)
		{
			change(k << 1 | 1, mid + 1, r, L, R, cas);
		}
		pushup(k);
	}

	long long query(int k, int l, int r, int L, int R)
	{
		if (L <= l && r <= R)
		{
			return sum[k];
		}
		int mid = (l + r) >> 1;
		long long ans = 0;
		pushdown(k, l, r);
		if (L <= mid)
		{
			ans += query(k << 1, l, mid, L, R);
		}
		if (R > mid)
		{
			ans += query(k << 1 | 1, mid + 1, r, L, R);
		}
		return ans;
	}
}

namespace LCT
{
	int fa[2 * _n], ch[2 * _n][2], tag[2 * _n], val[2 * _n];
	int top;
	int stack[2 * _n];

	bool isroot(int x)
	{
		return ch[fa[x]][0] != x && ch[fa[x]][1] != x;
	}

	void pushdown(int x)
	{
		if (tag[x])
		{
			if (ch[x][0])
			{
				val[ch[x][0]] = tag[ch[x][0]] = tag[x];
			}
			if (ch[x][1])
			{
				val[ch[x][1]] = tag[ch[x][1]] = tag[x];
			}
			tag[x] = 0;
		}
	}

	void rotate(int x)
	{
		int y = fa[x];
		int z = fa[y];
		int w = ch[y][1] == x;
		if (! isroot(y))
		{
			ch[z][ch[z][1] == y] = x;
		}
		fa[x] = z;
		ch[y][w] = ch[x][w ^ 1];
		fa[ch[y][w]] = y;
		ch[x][w ^ 1] = y;
		fa[y] = x;
//		pushup(y);
//		pushup(x);
	}

	void splay(int x)
	{
		top = 0;
		top++;
		stack[top] = x;
		for (int i = x; ! isroot(i); i = fa[i])
		{
			top++;
			stack[top] = fa[i];
		}
		while (top)
		{
			pushdown(stack[top]);
			top--;
		}
		while (! isroot(x))
		{
			int y = fa[x];
			int z = fa[y];
			if (! isroot(y))
			{
				if ((ch[z][1] == y) ^ (ch[y][1] == x))
				{
					rotate(x);
				}
				else
				{
					rotate(y);
				}
			}
			rotate(x);
		}
	}

	void access(int x, int pos)
	{
		int top = 0;
		for (int i = x, t = 0; i; t = i, i = fa[i])
		{
			splay(i);
			int pp = val[i];
			if (pp != 0)
			{
				SEG::change(1, 1, n, pp - SAM::len[i] + 1, pp - SAM::len[fa[i]], -1);
			}
			ch[i][1] = t;
//			pushup(i);
			top = i;
		}
		val[top] = tag[top] = pos;
		SEG::change(1, 1, n, 1, pos, 1);
	}

	void init()
	{
		for (int i = 1; i <= SAM::knum; i++)
		{
			fa[i] = SAM::pre[i];
			val[i] = tag[i] = 0;
		}
	}
}

int main()
{
	SAM::init();

	scanf("%s", s + 1);
	n = strlen(s + 1);
	for (int i = 1; i <= n; i++)
	{
		SAM::extend(s[i] - 'a');
		pos[i] = SAM::last;
	}
	scanf("%d", &m);
	for (int i = 1; i <= m; i++)
	{
		int l = read();
		int r = read();
		ques[r].push_back(std::make_pair(l, i));
	}
	LCT::init();
	for (int i = 1; i <= n; i++)
	{
		LCT::access(pos[i], i);
		for (int j = 0; j < (int)ques[i].size(); j++)
		{
			ans[ques[i][j].second] = SEG::query(1, 1, n, ques[i][j].first, i);
		}
	}
	for (int i = 1; i <= m; i++)
	{
		printf("%lld\n", ans[i]);
	}
	return 0;
}


