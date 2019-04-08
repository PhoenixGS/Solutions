#include <cstdio>
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

const int _n = 200000 + 10;
int n;
int x[_n];
int edgenum;
int vet[2 * _n], nextx[2 * _n], head[_n];
int times;
int in[_n], out[_n];
int tag[4 * _n], maxx[4 * _n];
std::pair<int, int> z[_n];
int ans[_n];
long long anss;

bool comp(std::pair<int, int> x, std::pair<int, int> y)
{
    return x > y;
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

int query(int k, int l, int r, int L, int R)
{
    if (L <= l && r <= R)
    {
        return maxx[k];
    }
    int mid = (l + r) >> 1;
    int ans = 0;
    if (L <= mid)
    {
        ans = std::max(ans, query(k << 1, l, mid, L, R));
    }
    if (R > mid)
    {
        ans = std::max(ans, query(k << 1 | 1, mid + 1, r, L, R));
    }
    return ans + tag[k];
}

void change(int k, int l, int r, int L, int R)
{
    if (L <= l && r <= R)
    {
        tag[k]++;
        maxx[k]++;
        return;
    }
    int mid = (l + r) >> 1;
    if (L <= mid)
    {
        change(k << 1, l, mid, L, R);
    }
    if (R > mid)
    {
        change(k << 1 | 1, mid + 1, r, L, R);
    }
    maxx[k] = std::max(maxx[k << 1], maxx[k << 1 | 1]) + tag[k];
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        x[i] = read();
    }
    for (int i = 2; i <= n; i++)
    {
        int fa = read();
        add(fa, i);
        add(i, fa);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++)
    {
        z[i].first = x[i];
        z[i].second = i;
    }
    std::sort(z + 1, z + n + 1, comp);
    for (int i = 1; i <= n; i++)
    {
        int u = z[i].second;
        int k = query(1, 1, n, in[u], out[u]) + 1;
        ans[k] = std::max(ans[k], z[i].first);
        change(1, 1, n, in[u], out[u]);
    }
    anss = 0;
    for (int i = 1; i <= n; i++)
    {
        anss += ans[i];
    }
    printf("%lld\n", anss);
    return 0;
}

