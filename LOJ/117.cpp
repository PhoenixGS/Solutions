#include <cstdio>
#include <queue>

long long read()
{
	char last = '+', ch = getchar();
	while (ch < '0' || ch > '9') last = ch, ch = getchar();
	long long tmp = 0;
	while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
	if (last == '-') tmp = -tmp;
	return tmp;
}

const int INF = 1000000000;
const long long IINF = (long long)1000000000 * 1000000000;
const int _n = 60000 + 10, _m = 400200 + 10;
int n, m, s, t;
int uu[_m], vv[_m];
long long lo[_m], up[_m];
long long in[_n], out[_n];
int edgenum;
int vet[4 * _m], nextx[4 * _m], head[_n], cur[_n];
long long val[4 * _m];
int dis[_n];
std::queue<int> que;
int S, T;
long long sum;

void add(int u, int v, long long cost)
{
    edgenum++;
    vet[edgenum] = v;
    val[edgenum] = cost;
    nextx[edgenum] = head[u];
    head[u] = edgenum;
}

bool bfs()
{
    for (int i = 1; i <= n + 2; i++)
    {
        dis[i] = INF;
    }
    dis[S] = 0;
    que.push(S);
    while (! que.empty())
    {
        int u = que.front();
        que.pop();
        for (int i = head[u]; i; i = nextx[i])
        {
            int v = vet[i];
            long long cost = val[i];
            if (cost != 0 && dis[v] == INF)
            {
                dis[v] = dis[u] + 1;
                que.push(v);
            }
        }
    }
    return dis[T] != INF;
}

long long flow(int u, long long maxflow)
{
    if (u == T)
    {
        return maxflow;
    }
    long long ans = 0;
    for (int i = cur[u]; i; i = nextx[i])
    {
        int v = vet[i];
        long long cost = val[i];
        if (cost != 0 && dis[u] + 1 == dis[v])
        {
            long long f = flow(v, std::min(cost, maxflow - ans));
            val[i] -= f;
            val[i ^ 1] += f;
            ans += f;
            cur[u] = i;
            if (ans == maxflow)
            {
                break;
            }
        }
    }
    if (ans < maxflow)
    {
        dis[u] = INF;
    }
    return ans;
}

long long maxflow()
{
    long long ans = 0;
    while (bfs())
    {
        for (int i = 1; i <= n + 2; i++)
        {
            cur[i] = head[i];
        }
        ans += flow(S, IINF);
    }
    return ans;
}

int main()
{
    edgenum = 1;
    scanf("%d%d%d%d", &n, &m, &s, &t);
	add(t, s, IINF);
	add(s, t, 0);
    for (int i = 1; i <= m; i++)
    {
        uu[i] = read();
        vv[i] = read();
        lo[i] = read();
        up[i] = read();
        out[uu[i]] += lo[i];
        in[vv[i]] += lo[i];
        add(uu[i], vv[i], up[i] - lo[i]);
        add(vv[i], uu[i], 0);
    }
	int now = edgenum;
    S = n + 1;
    T = n + 2;
    for (int u = 1; u <= n; u++)
    {
        if (in[u] > out[u])
        {
            sum += in[u] - out[u];
            add(S, u, in[u] - out[u]);
            add(u, S, 0);
        }
        if (in[u] < out[u])
        {
            add(u, T, out[u] - in[u]);
            add(T, u, 0);
        }
    }
    if (maxflow() != sum)
    {
        puts("please go home to sleep");
	}
	else
	{
		long long ans = val[3];
		val[2] = 0;
		val[3] = 0;
		for (int i = now + 1; i <= edgenum; i++)
		{
			val[i] = 0;
		}
		S = t;
		T = s;
		printf("%lld\n", ans - maxflow());
    }
	return 0;
}

