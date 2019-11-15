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

const int _n = 100000 + 10;
int n, m;
int key[_n], f[_n], left[_n], right[_n], dis[_n], del[_n];

int findfather(int x)
{
	return f[x] == 0 ? x : f[x] = findfather(f[x]);
}

int merge(int x, int y)
{
	if (x == 0 || y == 0)
	{
		return x + y;
	}
	if (key[x] > key[y] || (key[x] == key[y] && x > y))
	{
		std::swap(x, y);
	}
	right[x] = merge(right[x], y);
	if (dis[left[x]] < dis[right[x]])
	{
		std::swap(left[x], right[x]);
	}
	f[left[x]] = f[right[x]] = x;
	dis[x] = dis[right[x]] + 1;
	return x;
}

int dele(int x)
{
	int l = left[x];
	int r = right[x];
	f[l] = f[r] = 0;
	del[x] = 1;
	f[x] = merge(l, r);
	return key[x];
}

int main()
{
	n = read();
	m = read();
	for (int i = 1; i <= n; i++)
	{
		key[i] = read();
		left[i] = right[i] = dis[i] = 0;
	}
	while (m--)
	{
		int op = read();
		if (op == 1)
		{
			int x = read();
			int y = read();
			if (del[x] || del[y])
			{
				continue;
			}
			int xx = findfather(x);
			int yy = findfather(y);
			if (xx != yy)
			{
				merge(xx, yy);
			}
		}
		else
		{
			int x;
			scanf("%d", &x);
			if (del[x])
			{
				printf("-1\n");
				continue;
			}
			int xx = findfather(x);
			printf("%d\n", dele(xx));
		}
	}
	return 0;
}


