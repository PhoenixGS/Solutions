#include <cstdio>
#include <algorithm>
#include <vector>

#define mid (l + r >> 1)

long long read()
{
	char last = '+', ch = getchar();
	while (ch < '0' || ch > '9') last = ch, ch = getchar();
	long long tmp = 0;
	while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
	if (last == '-') tmp = -tmp;
	return tmp;
}

struct QUES
{
	long long x;
	int pos, id;
};

int n, m;
long long c0;
int edgenum;
int vet[600000], nextx[600000], head[600000];
long long ans;
int times;
int in[600000], out[600000];
long long kk[600000], cc[600000];
int point[3000000];
std::vector<int> stack[3000000];
std::vector<int> vector;
std::vector<int> vec[600000];
int last;
int idx[600000];
QUES ques[600000];
long long anss[600000];

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

bool idcomp(int x, int y)
{
	return kk[x] > kk[y] || kk[x] == kk[y] && cc[x] > cc[y];
}

bool quescomp(QUES x, QUES y)
{
	return x.x < y.x;
}

long long up(int x, int y)
{
	return cc[x] - cc[y];
}

long long down(int x, int y)
{
	return kk[y] - kk[x];
}

bool check(int x, int y, int z)
{
	return up(x, y) * down(y, z) >= up(y, z) * down(x, y);
}

long long calcval(int x, long long key)
{
	return kk[x] * key + cc[x];
}

void dfs(int u)
{
	times++;
	in[u] = times;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		dfs(v);
	}
	out[u] = times;
}

void maintain(int k, int id)
{
	while ((int)stack[k].size() > 1 && check(stack[k][stack[k].size() - 2], stack[k][stack[k].size() - 1], id))
//	while ((int)stack[k].size() > 1 && calcpoint(stack[k][stack[k].size() - 2], stack[k][stack[k][stack[k].size() - 1]]) - calcpoint(stack[k][stack[k].size() - 1], id) > eps)
	{
		stack[k].pop_back();
	}
	stack[k].push_back(id);
}

void change(int k, int l, int r, int L, int R, int id)
{
	if (L <= l && r <= R)
	{
		maintain(k, id);
		return;
	}
	if (L <= mid)
	{
		change(k << 1, l, mid, L, R, id);
	}
	if (R > mid)
	{
		change(k << 1 | 1, mid + 1, r, L, R, id);
	}
}

void solve(int k, long long key)
{
	for (int &i = point[k]; i < (int)stack[k].size() - 1 && calcval(stack[k][i], key) > calcval(stack[k][i + 1], key); i++);
	if (point[k] < (int)stack[k].size())
	{
		ans = std::min(ans, calcval(stack[k][point[k]], key));
	}
}

void query(int k, int l, int r, int pos, long long key)
{
	solve(k, key);
	if (l == r)
	{
		return;
	}
	if (pos <= mid)
	{
		query(k << 1, l, mid, pos, key);
	}
	else
	{
		query(k << 1 | 1, mid + 1, r, pos, key);
	}
}

int main()
{
	n = read();
	m = read();
	c0 = read();
	last = 0;
	for (int i = 2; i <= n; i++)
	{
		int cas;
		cas = read();
		if (cas == 0)
		{
			int father;
			father = read();
			father++;
			add(father, i);
			int id;
			long long x, y, z, c;
			id = read();
			x = read();
			y = read();
			z = read();
			c = read();
			id++;
			kk[id] = -2 * x;
			cc[id] = x * x + c;
			vec[id].push_back(i);
			last++;
			idx[last] = id;
			if (id == 83681)
			{puts("XXXX");}
		}
		else
		{
			int father;
			father = read();
			father++;
			add(father, i);
			int id;
			id = read();
			id++;
			vec[id].push_back(i);
		}
	}
	dfs(1);
	std::sort(idx + 1, idx + last + 1, idcomp);
	for (int i = 1; i <= last; i++)
	{
		printf("%d %lld %lld\n", idx[i], kk[idx[i]], cc[idx[i]]);
	}
	for (int i = 1; i <= last; i++)
	{
		printf("V%d\n", idx[i]);
		vector.clear();
		for (int j = 0; j < (int)vec[idx[i]].size(); j++)
		{
			vector.push_back(in[vec[idx[i]][j]]);
			vector.push_back(out[vec[idx[i]][j]] + 1);
		}
		std::sort(vector.begin(), vector.end());
		for (int j = 0; j < (int)vector.size(); j += 2)
		{
			if (vector[j] <= vector[j + 1] - 1)
			{
				printf("%d %d %d\n", vector[j], vector[j + 1] - 1, idx[i]);
				change(1, 1, times, vector[j], vector[j + 1] - 1, idx[i]);
			}
		}
	}
	for (int i = 1; i <= m; i++)
	{
		ques[i].pos = read();
		ques[i].x = read();
		ques[i].pos++;
		ques[i].id = i;
	}
	std::sort(ques + 1, ques + m + 1, quescomp);
	for (int i = 1; i <= m; i++)
	{
		ans = c0;
		query(1, 1, times, in[ques[i].pos], ques[i].x);
		ans += ques[i].x * ques[i].x;
		anss[ques[i].id] = ans;
	}
	for (int i = 1; i <= m; i++)
	{
		printf("%lld\n", anss[i]);
	}
	return 0;
}
