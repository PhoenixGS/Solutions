#include <cstdio>
#include <algorithm>

int num;
int sum[4000000], ch[4000000][2];
long long ans, ansx, ansy;
int n;

void change(int &k, int l, int r, int pos, int delta)
{
	if (! k)
	{
		num++;
		k = num;
	}
	sum[k] += delta;
	if (l == r)
	{
		return;
	}
	int mid = l + r >> 1;
	if (pos <= mid)
	{
		change(ch[k][0], l, mid, pos, delta);
	}
	else
	{
		change(ch[k][1], mid + 1, r, pos, delta);
	}
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
	ansx += (long long)sum[ch[x][1]] * (long long)sum[ch[y][0]];
	ansy += (long long)sum[ch[x][0]] * (long long)sum[ch[y][1]];
	merge(ch[x][0], ch[y][0]);
	merge(ch[x][1], ch[y][1]);
	sum[x] += sum[y];
}

int solve()
{
	int x;
	scanf("%d", &x);
	if (x)
	{
		num++;
		int k = num;
		change(k, 1, n, x, 1);
		return k;
	}
	int l = solve();
	int r = solve();
	ansx = ansy = 0;
	merge(l, r);
	ans += std::min(ansx, ansy);
	return l;
}

int main()
{
	scanf("%d", &n);
	ans = 0;
	solve();
	printf("%lld\n", ans);
	return 0;
}
