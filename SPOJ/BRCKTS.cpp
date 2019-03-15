#include <cstdio>
#include <algorithm>

const int INF = 1e9;
int n, m;
char st[40000];
int s[40000];
int minx[200000];
int tag[200000];
int cnt;

void pushdown(int k)
{
	if (tag[k])
	{
		minx[k << 1] += tag[k];
		tag[k << 1] += tag[k];
		minx[k << 1 | 1] += tag[k];
		tag[k << 1 | 1] += tag[k];
		tag[k] = 0;
	}
}

void pushup(int k)
{
	minx[k] = std::min(minx[k << 1], minx[k << 1 | 1]);
}

void build(int k, int l, int r)
{
	if (l == r)
	{
		minx[k] = s[l];
		tag[k] = 0;
		return;
	}
	int mid = (l + r) >> 1;
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
	pushup(k);
}

void change(int k, int l, int r, int L, int R, int delta)
{
	if (L <= l && r <= R)
	{
		minx[k] += delta;
		tag[k] += delta;
		return;
	}
	pushdown(k);
	int mid = (l + r) >> 1;
	if (L <= mid)
	{
		change(k << 1, l, mid, L, R, delta);
	}
	if (R > mid)
	{
		change(k << 1 | 1, mid + 1, r, L, R, delta);
	}
	pushup(k);
}

int main()
{
	for (int T = 1; T <= 10; T++)
	{
		printf("Test %d:\n", T);
		scanf("%d", &n);
		scanf("%s", st + 1);
		s[0] = 0;
		for (int i = 1; i <= n; i++)
		{
			s[i] = s[i - 1] + (st[i] == '(' ? 1 : -1);
		}
		for (int i = 1; i <= 4 * n; i++)
		{
			minx[i] = INF;
			tag[i] = 0;
		}
		cnt = s[n];
		build(1, 1, n);
		scanf("%d", &m);
		for (int i = 1; i <= m; i++)
		{
			int pos;
			scanf("%d", &pos);
			if (pos)
			{
				if (st[pos] == '(')
				{
					change(1, 1, n, pos, n, -2);
					st[pos] = ')';
					cnt -= 2;
				}
				else
				{
					change(1, 1, n, pos, n, 2);
					st[pos] = '(';
					cnt += 2;
				}
			}
			else
			{
				puts((cnt == 0 && minx[1] >= 0) ? "YES" : "NO");
			}
		}
	}
	return 0;
}
