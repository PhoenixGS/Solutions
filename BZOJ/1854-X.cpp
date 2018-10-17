#include <cstdio>
#include <algorithm>

int n;
int f[2000000];
int v[2000000];
int max[2000000];
int ans;

int findfather(int x)
{
	if (! f[x])
	{
		f[x] = x;
		max[x] = x;
	}
	return f[x] == x ? x : f[x] = findfather(f[x]);
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		int xx = findfather(x), yy = findfather(y);
		if (xx == yy)
		{
			v[xx] = true;
		}
		else
		{
			f[xx] = yy;
			v[yy] = v[xx] | v[yy];
			max[yy] = std::max(max[xx], max[yy]);
		}
	}
	for (ans = 1; ; ans++)
	{
		int xx = findfather(ans);
		if (! v[xx] && max[xx] == ans)
		{
			break;
		}
	}
	printf("%d\n", ans - 1);
	return 0;
}
