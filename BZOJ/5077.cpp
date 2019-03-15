#include <cstdio>
#include <algorithm>
#include <vector>

#define top (int)fun[k].size()

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
	int id, pos;
	long long x0;
}; 

const long long INF = (long long)1000000000 * 1000000000;
const int _n = 500000 + 10;
long long dust;
int n, m;
int edgenum;
int vet[2 * _n], nextx[2 * _n], head[_n];
int times;
int in[_n], out[_n];
long long xx[_n], cc[_n];
int pos[_n];
int idx[_n];
std::vector<int> vec[_n];
std::vector<int> fun[8 * _n];
int point[8 * _n];
int last;
node ques[_n];
long long ans[_n];

bool comp(int x, int y)
{
	return xx[x] > xx[y] || (xx[x] == xx[y] && cc[x] > cc[y]);
}

bool compques(node x, node y)
{
	return x.x0 < y.x0;
}

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void dfs(int u, int father)
{
	times++;
	in[u] = times;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			dfs(v, u);
		}
	}
	out[u] = times;
}

long long up(int ix, int iy)
{
	return cc[iy] - cc[ix];
}

long long down(int ix, int iy)
{
	return xx[ix] - xx[iy];
}

void update(int k, int id)
{
//	while (top >= 2 && calc(fun[k][top - 1], fun[k][top]) > calc(fun[k][top], id))
	while (top >= 2 && up(fun[k][top - 2], fun[k][top - 1]) * down(fun[k][top - 1], id) >= up(fun[k][top - 1], id) * down(fun[k][top - 2], fun[k][top - 1]))
	{
		fun[k].pop_back();
	}
	fun[k].push_back(id);
}

long long value(int id, long long x0)
{
	return xx[id] * x0 + cc[id];
}

long long calc(int k, long long x0)
{
	/*
	if (top == 0)
	{
		return INF;
	}
	int l = 0;
	int r = top - 1;
	while (l < r)
	{
		int mid = (l + r) >> 1;
//		if ((double)x0 < calc(fun[k][mid], fun[k][mid + 1]))
		if (x0 * down(fun[k][mid], fun[k][mid + 1]) <= up(fun[k][mid], fun[k][mid + 1]))
		{
			r = mid;
		}
		else
		{
			l = mid + 1;
		}
	}
	return x0 * xx[fun[k][l]] + cc[fun[k][l]];
	*/
//	for (int &i = point[k]; i < (int)fun[k].size() - 1 && x0 * down(fun[k][i], fun[k][i + 1]) > up(fun[k][i], fun[k][i + 1]); i++);
	for (int &i = point[k]; i < (int)fun[k].size() - 1 && value(fun[k][i], x0) > value(fun[k][i + 1], x0); i++);
	return (point[k] < (int)fun[k].size()) ? ((long long)x0 * xx[fun[k][point[k]]] + cc[fun[k][point[k]]]) : INF;
}

void change(int k, int l, int r, int L, int R, int id)
{
	if (l > r)
	{
		return;
	}
	if (L <= l && r <= R)
	{
		update(k, id);
		return;
	}
	int mid = (l + r) >> 1;
	if (L <= mid)
	{
		change(k << 1, l, mid, L, R, id);
	}
	if (R > mid)
	{
		change(k << 1 | 1, mid + 1, r, L, R, id);
	}
}

long long query(int k, int l, int r, int pos, long long x0)
{
	long long ans = calc(k, x0);
	if (l == r)
	{
		return ans;
	}
	int mid = (l + r) >> 1;
	if (pos <= mid)
	{
		ans = std::min(ans, query(k << 1, l, mid, pos, x0));
	}
	else
	{
		ans = std::min(ans, query(k << 1 | 1, mid + 1, r, pos, x0));
	}
	return ans;
}

int main()
{
	n = read();
	m = read();
	cc[1] = read();
	pos[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		int cas = read();
		if (cas == 0)
		{
			int father = read();
			father++;
			add(i, father);
			add(father, i);
			pos[i] = read();
			pos[i]++;
			xx[pos[i]] = read();
			dust = read();
			dust = read();
			cc[pos[i]] = read();
			cc[pos[i]] = cc[pos[i]] + xx[pos[i]] * xx[pos[i]];
			xx[pos[i]] = -2 * xx[pos[i]];
		}
		else
		{
			int father = read();
			father++;
			add(i, father);
			add(father, i);
			pos[i] = read();
			pos[i]++;
		}
	}
	dfs(1, 0);
	for (int i = 1; i <= n; i++)
	{
		vec[pos[i]].push_back(in[i]);
		vec[pos[i]].push_back(out[i] + 1);
	}
	for (int i = 1; i <= n; i++)
	{
		idx[i] = i;
	}
	std::sort(idx + 1, idx + n + 1, comp);
	for (int i = 1; i <= n; i++)
	{
		int id = idx[i];
		std::sort(vec[id].begin(), vec[id].end());
		for (int j = 0; j < (int)vec[id].size(); j += 2)
		{
			if (vec[id][j] <= vec[id][j + 1] - 1)
			{
				change(1, 1, n, vec[id][j], vec[id][j + 1] - 1, id);
			}
		}
	}
	while (m--)
	{
		int id = read();
		id++;
		long long x0 = read();
		last++;
		ques[last].id = id;
		ques[last].x0 = x0;
		ques[last].pos = last;
	}
	std::sort(ques + 1, ques + last + 1, compques);
	for (int i = 1; i <= last; i++)
	{
		ans[ques[i].pos] = query(1, 1, n, in[ques[i].id], ques[i].x0) + ques[i].x0 * ques[i].x0;
	}
	for (int i = 1; i <= last; i++)
	{
		printf("%lld\n", ans[i]);
	}
	return 0;
}
