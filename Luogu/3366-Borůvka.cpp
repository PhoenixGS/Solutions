#include <cstdio>

long long read()
{
	char last = '+', ch = getchar();
	while (ch < '0' || ch > '9') last = ch, ch = getchar();
	long long tmp = 0;
	while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
	if (last == '-') tmp = -tmp;
	return tmp;
}

const int _n = 5000 + 10, _m = 200000 + 10;
int n, m;
int uuu[_m], vvv[_m], www[_m];
int f[_n];
int pick[_n];
int used[_m];

bool check(int x, int y)
{
	if (y == 0)
	{
		return true;
	}
	if (www[x] < www[y] || (www[x] == www[y] && x < y))
	{
		return true;
	}
	else
	{
		return false;
	}
}

int findfather(int x)
{
	return f[x] == x ? x : f[x] = findfather(f[x]);
}

void Boruvka()
{
	for (int i = 1; i <= n; i++)
	{
		f[i] = i;
	}
	int cnt = 0;
	int ans = 0;
	bool F = true;
	while (F)
	{
		F = false;
		for (int i = 1; i <= n; i++)
		{
			pick[i] = 0;
		}
		for (int i = 1; i <= m; i++)
		{
			if (! used[i])
			{
				int xx = findfather(uuu[i]);
				int yy = findfather(vvv[i]);
				if (xx != yy)
				{
					if (check(i, pick[xx]))
					{
						pick[xx] = i;
					}
					if (check(i, pick[yy]))
					{
						pick[yy] = i;
					}
				}
			}
		}
		for (int i = 1; i <= n; i++)
		{
			if (pick[i] != 0 && ! used[pick[i]])
			{
				F = true;
				cnt++;
				ans += www[pick[i]];
				used[pick[i]] = 1;
				int xx = findfather(uuu[pick[i]]);
				int yy = findfather(vvv[pick[i]]);
				f[xx] = yy;
			}
		}
	}
	if (cnt == n - 1)
	{
		printf("%d\n", ans);
	}
	else
	{
		puts("orz");
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
	{
		uuu[i] = read();
		vvv[i] = read();
		www[i] = read();
	}
	Boruvka();
	return 0;
}
