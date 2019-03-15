#include <cstdio>
#include <algorithm>
 
#define root ch[0][1]
 
int size[200000];
int rev[200000];
int ch[200000][2];
int fa[200000];
int n, m;
 
void pushup(int k)
{
    size[k] = size[ch[k][0]] + size[ch[k][1]] + 1;
}
 
void pushdown(int k)
{
    if (rev[k])
    {
        std::swap(ch[k][0], ch[k][1]);
        rev[ch[k][0]] ^= 1;
        rev[ch[k][1]] ^= 1;
        rev[k] = 0;
    }
}
 
inline void rotate(int k)
{
    int f = fa[k], ff = fa[f], w = ch[f][1] == k;
    ch[ff][ch[ff][1] == f] = k;
    fa[k] = ff;
    ch[f][w] = ch[k][w ^ 1];
    fa[ch[f][w]] = f;
    ch[k][w ^ 1] = f;
    fa[f] = k;
    pushup(f);
    pushup(k);
}
 
void splay(int x, int &k)
{
    while (x != k)
    {
        if (fa[x] != k)
        {
            if ((ch[fa[fa[x]]][0] == fa[fa[x]]) ^ (ch[fa[x]][0] == x))
            {
                rotate(x);
            }
            else
            {
                rotate(fa[x]);
            }
        }
        rotate(x);
    }
}
 
int find(int k, int rank)
{
    pushdown(k);
    int l = ch[k][0];
    int r = ch[k][1];
    if (size[l] + 1 == rank)
    {
        return k;
    }
    if (size[l] >= rank)
    {
        return find(l, rank);
    }
    else
    {
        return find(r, rank - size[l] - 1);
    }
}
 
void rever(int l, int r)
{
    int x = find(root, l);
    int y = find(root, r + 2);
    splay(x, root);
    splay(y, ch[x][1]);
    int z = ch[y][0];
    rev[z] ^= 1;
}
 
void build(int l, int r, int father, int &k)
{
    if (l > r)
    {
        return;
    }
    if (l == r)
    {
        fa[l] = father;
        size[l] = 1;
        k = l;
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid - 1, mid, ch[mid][0]);
    build(mid + 1, r, mid, ch[mid][1]);
    fa[mid] = father;
    pushup(mid);
    k = mid;
}
 
int main()
{
    scanf("%d%d", &n, &m);
    build(1, n + 2, 0, root);
    for (int i = 1; i <= m; i++)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        rever(l, r);
		for (int j = 1; j <= n; j++)
		{
			printf("%d ", find(root, j + 1) - 1);
		}
		printf("\n");
    }
    for (int i = 1; i <= n; i++)
    {
        printf("%d ", find(root, i + 1) - 1);
    }
    printf("\n");
    return 0;
}
