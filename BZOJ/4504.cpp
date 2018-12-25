#include <cstdio>
#include <algorithm>
#include <queue>
#include <map>

#define mid ((l + r) >> 1)

long long read()
{
	char last = '+', ch = getchar();
	while (ch < '0' || ch > '9') last = ch, ch = getchar();
	long long tmp = 0;
	while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
	if (last == '-') tmp = -tmp;
	return tmp;
}

struct node
{
	long long key;
	int pos, l, r;
};

const long long INF = (long long)1000000000 * 1000000000;
const int _n = 100000 + 10, _k = 200000 + 10;
int n, k;
int x[_n];
int knum;
long long maxx[40 * _n], tag[40 * _n];
int idx[40 * _n], ch[40 * _n][2];
int root[_n];
std::priority_queue<node> heap;
std::map<int, int> pre;

bool operator < (node x, node y)
{
	return x.key < y.key;
}

void pushup(int k, int l, int r)
{
	if (l == r)
	{
		maxx[k] = tag[k];
		idx[k] = l;
		return;
	}
	if (maxx[ch[k][0]] > maxx[ch[k][1]])
	{
		maxx[k] = maxx[ch[k][0]];
		idx[k] = idx[ch[k][0]];
	}
	else
	{
		maxx[k] = maxx[ch[k][1]];
		idx[k] = idx[ch[k][1]];
	}
	maxx[k] = maxx[k] + tag[k];
}

void build(int &k, int l, int r)
{
	knum++;
	k = knum;
	if (l == r)
	{
		maxx[k] = tag[k] = 0;
		idx[k] = l;
		return;
	}
	build(ch[k][0], l, mid);
	build(ch[k][1], mid + 1, r);
	pushup(k, l, r);
}

void change(int &u, int v, int l, int r, int L, int R, int delta)
{
	knum++;
	u = knum;
	tag[u] = tag[v];
	ch[u][0] = ch[v][0];
	ch[u][1] = ch[v][1];
	maxx[u] = maxx[v];
	idx[u] = idx[v];
	if (L <= l && r <= R)
	{
		tag[u] += delta;
		maxx[u] += delta;
		return;
	}
	if (L <= mid)
	{
		change(ch[u][0], ch[v][0], l, mid, L, R, delta);
	}
	if (R > mid)
	{
		change(ch[u][1], ch[v][1], mid + 1, r, L, R, delta);
	}
	pushup(u, l, r);
}

std::pair<long long, int> query(int k, int l, int r, int L, int R)
{
	if (! k)
	{
		return std::make_pair(-INF, 0);
	}
	if (L <= l && r <= R)
	{
		return std::make_pair(maxx[k], idx[k]);
	}
	if (! (L <= mid))
	{
		std::pair<long long, int> t = query(ch[k][1], mid + 1, r, L, R);
		t.first += tag[k];
		return t;
	}
	if (! (R > mid))
	{
		std::pair<long long, int> t = query(ch[k][0], l, mid, L, R);
		t.first += tag[k];
		return t;
	}
	std::pair<long long, int> tl = query(ch[k][0], l, mid, L, R), tr = query(ch[k][1], mid + 1, r, L, R), t;
	t = std::max(tl, tr);
	t.first += tag[k];
	return t;
}

int main()
{
	n = read();
	k = read();
	for (int i = 1; i <= n; i++)
	{
		x[i] = read();
	}
	build(root[0], 1, n);
	for (int i = 1; i <= n; i++)
	{
		change(root[i], root[i - 1], 1, n, pre[x[i]] + 1, i, x[i]);
		pre[x[i]] = i;
	}
	for (int i = 1; i <= n; i++)
	{
		heap.push((node){query(root[i], 1, n, 1, i).first, i, 1, i});
	}
	for (int i = 1; i < k; i++)
	{
		node tmp = heap.top();
		heap.pop();
		int pos = query(root[tmp.pos], 1, n, tmp.l, tmp.r).second;
		if (tmp.l != pos)
		{
			heap.push((node){query(root[tmp.pos], 1, n, tmp.l, pos - 1).first, tmp.pos, tmp.l, pos - 1});
		}
		if (tmp.r != pos)
		{
			heap.push((node){query(root[tmp.pos], 1, n, pos + 1, tmp.r).first, tmp.pos, pos + 1, tmp.r});
		}
	}
	printf("%lld\n", heap.top().key);
	return 0;
}
