#include <cstdio>
#include <algorithm>
 
using namespace std;
 
int edgenum;
int vet[60005];
int nextx[60005];
int head[30005];
int sz[30005];
int deep[30005];
int fa[30005];
int last;
int pos[30005];
int top[30005];
int maxx[70005];
int sumx[70005];
int ch[30005];
char st[30];
int M;
int n;
int x[30005];
int q;
 
void add(int u, int v)
{
    edgenum++;
    vet[edgenum] = v;
    nextx[edgenum] = head[u];
    head[u] = edgenum;
}
 
void dfs1(int u)
{
    sz[u] = 1;
    int k = 0;
    for (int i = head[u]; i; i = nextx[i])
    {
        int v = vet[i];
        if (v != fa[u])
        {
            deep[v] = deep[u] + 1;
            fa[v] = u;
            dfs1(v);
            sz[u] += sz[v];
            if (sz[v] > sz[k])
            {
                k = v;
            }
        }
    }
    ch[u] = k;
}
 
void dfs2(int u, int chain)
{
    last++;
    pos[u] = last;
    top[u] = chain;
    if (ch[u] == 0)
    {
        return;
    }
    dfs2(ch[u], chain);
    for (int i = head[u]; i; i = nextx[i])
    {
        int v = vet[i];
        if (v != fa[u] && v != ch[u])
        {
            dfs2(v, v);
        }
    }
}
 
void update(int x, int newvalue)
{
    x += M;
    maxx[x] = newvalue;
    sumx[x] = newvalue;
    while (x > 1)
    {
        x >>= 1;
        maxx[x] = max(maxx[x << 1], maxx[x << 1 | 1]);
        sumx[x] = sumx[x << 1] + sumx[x << 1 | 1];
    }
}
 
int query_max(int l, int r)
{
    int maxxx = -1000000000;
    l = l + M - 1;
    r = r + M + 1;
    for (; l ^ r ^ 1; l >>= 1, r >>= 1)
    {
        if (~ l & 1)
        {
            maxxx = max(maxxx, maxx[l ^ 1]);
        }
        if (r & 1)
        {
            maxxx = max(maxxx, maxx[r ^ 1]);
        }
    }
    return maxxx;
}
 
int query_sum(int l, int r)
{
    int sum = 0;
    l = l + M - 1;
    r = r + M + 1;
    for (; l ^ r ^ 1; l >>= 1, r >>= 1)
    {
        if (~ l & 1)
        {
            sum += sumx[l ^ 1];
        }
        if (r & 1)
        {
            sum += sumx[r ^ 1];
        }
    }
    return sum;
}
 
int solve_max(int xx, int yy)
{
    int maxxx = -1000000000;
    while (top[xx] != top[yy])
    {
        if (deep[top[xx]] < deep[top[yy]])
        {
            swap(xx, yy);
        }
        maxxx = max(maxxx, query_max(pos[top[xx]], pos[xx]));
        xx = fa[top[xx]];
    }
    if (pos[xx] > pos[yy])
    {
        swap(xx, yy);
    }
    maxxx = max(maxxx, query_max(pos[xx], pos[yy]));
    return maxxx;
}
 
int solve_sum(int xx, int yy)
{
    int sum = 0;
    while (top[xx] != top[yy])
    {
        if (deep[top[xx]] < deep[top[yy]])
        {
            swap(xx, yy);
        }
        sum += query_sum(pos[top[xx]], pos[xx]);
        xx = fa[top[xx]];
    }
    if (pos[xx] > pos[yy])
    {
        swap(xx, yy);
    }
    sum += query_sum(pos[xx], pos[yy]);
    return sum;
}
 
int main()
{
    edgenum = 0;
    last = 0;
    scanf("%d", &n);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &x[i]);
    }
    deep[1] = 0;
    dfs1(1);
    dfs2(1, 1);
    M = 1;
    for (; M < n + 2; M <<= 1);
    for (int i = 1; i <= n; i++)
    {
        update(pos[i], x[i]);
    }
    scanf("%d", &q);
    for (int i = 1; i <= q; i++)
    {
        scanf("%s", st);
        if (st[0] == 'C')
        {
            int x, newvalue;
            scanf("%d%d", &x, &newvalue);
            update(pos[x], newvalue);
        }
        else
        {
            int xx, yy;
            scanf("%d%d", &xx, &yy);
            if (st[1] == 'M')
            {
                printf("%d\n", solve_max(xx, yy));
            }
            else
            {
                printf("%d\n", solve_sum(xx, yy));
            }
        }
    }
    return 0;
}
