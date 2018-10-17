#include <cstdio>
#include <algorithm>

struct EDGE
{
	int u, v, cost;
};

struct QUES
{
	int v, x, k, id;
};

const int INF = 1000000000;
int n, m, k;
EDGE edge[1000000];
QUES ques[1000000];
int f[200000];
int num;
int sum[5000000], ch[5000000][2];
int root[200000];
int ans[1000000];

bool edgecomp(EDGE x, EDGE y)
{
	return x.cost < y.cost;
}

bool quescomp(QUES x, QUES y)
{
	return x.x < y.x;
}

int findfather(int x)
{
	return f[x] == x ? x : f[x] = findfather(f[x]);
}

void pushup(int k)
{
	sum[k] = sum[ch[k][0]] + sum[ch[k][1]];
}

void change(int &k, int l, int r, int pos)
{
	if (! k)
	{
		num++;
		k = num;
	}
	if (l == r)
	{
		sum[k]++;
		return;
	}
	int mid = l + r >> 1;
	if (pos <= mid)
	{
		change(ch[k][0], l, mid, pos);
	}
	else
	{
		change(ch[k][1], mid + 1, r, pos);
	}
	pushup(k);
}

void merge(int &x, int y)
{
	if (! y)
	{
		return;
	}
	if (! x)
	{
		x = y;
		return;
	}
	merge(ch[x][0], ch[y][0]);
	merge(ch[x][1], ch[y][1]);
	sum[x] += sum[y];
}

int query(int k, int l, int r, int rank)
{
	if (l == r)
	{
		return l;
	}
	int mid = l + r >> 1;
	if (rank <= sum[ch[k][1]])
	{
		return query(ch[k][1], mid + 1, r, rank);
	}
	else
	{
		return query(ch[k][0], l, mid, rank - sum[ch[k][1]]);
	}
}

int main()
{
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		change(root[i], 0, INF, x);
		f[i] = i;
	}
	for (int i = 1; i <= m; i++)
	{
		scanf("%d%d%d", &edge[i].u, &edge[i].v, &edge[i].cost);
	}
	for (int i = 1; i <= k; i++)
	{
		scanf("%d%d%d", &ques[i].v, &ques[i].x, &ques[i].k);
		ques[i].id = i;
	}
	std::sort(edge + 1, edge + m + 1, edgecomp);
	std::sort(ques + 1, ques + k + 1, quescomp);
	int now = 1;
	for (int i = 1; i <= k; i++)
	{
		while (now <= m && edge[now].cost <= ques[i].x)
		{
			int xx = findfather(edge[now].u);
			int yy = findfather(edge[now].v);
			if (xx != yy)
			{
				f[xx] = yy;
				merge(root[yy], root[xx]);
			}
			now++;
		}
		if (ques[i].k > sum[root[findfather(ques[i].v)]])
		{
			ans[ques[i].id] = -1;
		}
		else
		{
			ans[ques[i].id] = query(root[findfather(ques[i].v)], 0, INF, ques[i].k);
		}
	}
	for (int i = 1; i <= k; i++)
	{
		printf("%d\n", ans[i]);
	}
	return 0;
}
