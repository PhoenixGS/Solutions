#include <cstdio>
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

struct node
{
	int v, root;
	double cost;
};

const int INF = 1000000000;
const int _n = 100000 + 10;
int n;
int L, R;
int edgenum;
int vet[2 * _n], nextx[2 * _n], head[_n];
double ori[2 * _n], val[2 * _n];
int vis[_n];
int ROOT;
int S, root;
int f[_n];
int size[_n];
int SIZE[_n];
std::vector<node> vec[_n];
double MID;
int que[_n];
double now[_n], nex[_n];
double ans;

bool comp(node x, node y)
{
	return SIZE[x.root] < SIZE[y.root];
}

void add(int u, int v, int cost)
{
	edgenum++;
	vet[edgenum] = v;
	val[edgenum] = cost;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void getroot(int u, int father)
{
	size[u] = 1;
	f[u] = 0;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father && ! vis[v])
		{
			getroot(v, u);
			size[u] += size[v];
			f[u] = std::max(f[u], size[v]);
		}
	}
	f[u] = std::max(f[u], S - size[u]);
	if (f[u] < f[root])
	{
		root = u;
	}
}

void dfs(int u, int father)
{
	size[u] = 1;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father && ! vis[v])
		{
			dfs(v, u);
			size[u] += size[v];
		}
	}
}

void build(int u)
{
	SIZE[u] = S;
	vis[u] = 1;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		double cost = val[i];
		if (! vis[v])
		{
			dfs(v, 0);
		}
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		double cost = val[i];
		if (! vis[v])
		{
			S = size[v];
			root = 0;
			getroot(v, 0);
			vec[u].push_back((node){v, root, cost});
			build(root);
		}
	}
	std::sort(vec[u].begin(), vec[u].end(), comp);
}

void calc(int u, int father, double sum, int deep)
{
	nex[deep] = std::max(nex[deep], sum);
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		double cost = val[i] - MID;
		if (v != father && ! vis[v])
		{
			calc(v, u, sum + cost, deep + 1);
		}
	}
}

void solve(int u, int deep)
{
	vis[u] = 1;
	for (int i = 0; i <= SIZE[u]; i++)
	{
		now[i] = -INF;
	}
	now[0] = 0;
	for (int i = 0; i < (int)vec[u].size(); i++)
	{
		int v = vec[u][i].v;
		double cost = vec[u][i].cost - MID;
		int sz = SIZE[vec[u][i].root];
		if (! vis[v])
		{
			for (int j = 0; j <= sz; j++)
			{
				nex[j] = -INF;
			}
			nex[0] = 0;
			calc(v, 0, cost, 1);
			int head = 1;
			int tail = 0;
			int point = std::min(R, sz);
			for (int j = 0; j <= sz; j++)
			{
				while (point >= 0 && j + point >= L)
				{
					while (head <= tail && now[point] > now[que[tail]])
					{
						tail--;
					}
					tail++;
					que[tail] = point;
					point--;
				}
				while (head <= tail && que[head] + j > R)
				{
					head++;
				}
				if (head <= tail)
				{
					ans = std::max(ans, now[que[head]] + nex[j]);
				}
			}
			for (int j = 0; j <= sz; j++)
			{
				now[j] = std::max(now[j], nex[j]);
			}
		}
	}
	for (int i = 0; i < (int)vec[u].size(); i++)
	{
		int v = vec[u][i].root;
		if (! vis[v])
		{
			solve(v, deep + 1);
		}
	}
}

double check(double mid)
{
	MID = mid;
	for (int i = 1; i <= n; i++)
	{
		vis[i] = 0;
	}
	ans = (double)-INF;
	solve(ROOT, 1);
	return ans;
}

int main()
{
	n = read();
	L = read();
	R = read();
	for (int i = 1; i < n; i++)
	{
		int u, v, cost;
		u = read();
		v = read();
		cost = read();
		add(u, v, cost);
		add(v, u, cost);
	}
	f[0] = INF;
	S = n;
	root = 0;
	getroot(1, 0);
	ROOT = root;
	build(ROOT);
	double l = 0.0, r = 1000000.0;
	for (int T = 1; T <= 40; T++)
	{
		double mid = (l + r) / 2;
		if (check(mid) > 0.0)
		{
			l = mid;
		}
		else
		{
			r = mid;
		}
	}
	printf("%.3f\n", l);
	return 0;
}

