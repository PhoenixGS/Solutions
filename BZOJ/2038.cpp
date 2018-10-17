#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long ll;

struct T
{
    int l, r, id;
    ll up, down;
};

int n, m;
int c[60000];
T x[60000];
ll s[60000];
int knumber;
int knum[60000];
ll ans;

bool comp(T x, T y)
{
    if (knum[x.l] == knum[y.l])
    {
        if (knum[x.l] & 1)
		{
			return x.r < y.r;
		}
		else
		{
			return x.r > y.r;
		}
    }
    return knum[x.l] < knum[y.l];
}

bool comp_id(T x, T y)
{
    return x.id < y.id;
}

ll gcd(ll x, ll y)
{
    return y == 0 ? x : gcd(y, x % y);
}

void update(int x, int add)
{
    ans -= s[c[x]] * s[c[x]];
    s[c[x]] += add;
    ans += s[c[x]] * s[c[x]];
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &c[i]);
    }
    knumber = int(sqrt(n));
    for (int i = 1; i <= n; i++)
    {
        knum[i] = (i - 1) / knumber + 1;
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &x[i].l, &x[i].r);
        x[i].id = i;
    }
    sort(x + 1, x + m + 1, comp);
    ans = 0;
    for (int i = 1, l = 1, r = 0; i <= m; i++)
    {
        for (; r < x[i].r; r++)
        {
            update(r + 1, 1);
        }
        for (; r > x[i].r; r--)
        {
            update(r, -1);
        }
        for (; l < x[i].l; l++)
        {
            update(l, -1);
        }
        for (; l > x[i].l; l--)
        {
            update(l - 1, 1);
        }
        if (x[i].l == x[i].r)
        {
            x[i].up = 0;
            x[i].down = 1;
            continue;
        }
        x[i].up = ans - (x[i].r - x[i].l + 1);
        x[i].down = (ll)(x[i].r - x[i].l + 1) * (x[i].r - x[i].l);
        ll tmp = gcd(x[i].up, x[i].down);
        x[i].up /= tmp;
        x[i].down /= tmp;
    }
    sort(x + 1, x + m + 1, comp_id);
    for (int i = 1; i <= m; i++)
    {
        printf("%lld/%lld\n", x[i].up, x[i].down);
    }
    return 0;
}

