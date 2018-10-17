#include <cstdio>
#include <cstdlib>
#include <map>

int size[200000], ch[200000][2], key[200000], fix[200000];
int root;
int n;
int num;

void pushup(int k)
{
	size[k] = size[ch[k][0]] + size[ch[k][1]] + 1;
}

int merge(int x, int y)
{
	if (! x || ! y)
	{
		return x ^ y;
	}
	if (fix[x] < fix[y])
	{
		ch[x][1] = merge(ch[x][1], y);
		pushup(x);
		return x;
	}
	else
	{
		ch[y][0] = merge(x, ch[y][0]);
		pushup(y);
		return y;
	}
}

std::pair<int, int> split(int x, int rank)
{
	if (! x)
	{
		return std::make_pair(0, 0);
	}
	std::pair<int, int> tmp;
	if (size[ch[x][0]] >= rank)
	{
		tmp = split(ch[x][0], rank);
		ch[x][0] = tmp.second;
		pushup(x);
		tmp.second = x;
	}
	else
	{
		tmp = split(ch[x][1], rank - size[ch[x][0]] - 1);
		ch[x][1] = tmp.first;
		pushup(x);
		tmp.first = x;
	}
	return tmp;
}

int findkth(int x, int k)
{
	std::pair<int, int> tmpx = split(x, k - 1);
	std::pair<int, int> tmpy = split(tmpx.second, 1);
	int ans = key[tmpy.first];
	root = merge(tmpx.first, merge(tmpy.first, tmpy.second));
	return ans;
}

int getkthlast(int x, int k)
{
	if (! x)
	{
		return 0;
	}
	if (k < key[x])
	{
		return getkthlast(ch[x][0], k);
	}
	else
	{
		return getkthlast(ch[x][1], k) + size[ch[x][0]] + 1;
	}
}

int getkthfirst(int x, int k)
{
	return getkthlast(x, k - 1) + 1;
}

void insert(int x)
{
	int k = getkthlast(root, x);
	std::pair<int, int> tmp = split(root, k);
	num++;
	key[num] = x;
	fix[num] = rand();
	size[num] = 1;
	root = merge(merge(tmp.first, num), tmp.second);
}

void deletex(int x)
{
	int k = getkthlast(root, x);
	if (findkth(root, k) != x)
	{
		return;
	}
	std::pair<int, int> tmpx = split(root, k - 1);
	std::pair<int, int> tmpy = split(tmpx.second, 1);
	root = merge(tmpx.first, tmpy.second);
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		int cas;
		scanf("%d", &cas);
		if (cas == 1)
		{
			int x;
			scanf("%d", &x);
			insert(x);
		}
		if (cas == 2)
		{
			int x;
			scanf("%d", &x);
			deletex(x);
		}
		if (cas == 3)
		{
			int x;
			scanf("%d", &x);
			printf("%d\n", getkthfirst(root, x));
		}
		if (cas == 4)
		{
			int x;
			scanf("%d", &x);
			printf("%d\n", findkth(root, x));
		}
		if (cas == 5)
		{
			int x;
			scanf("%d", &x);
			printf("%d\n", findkth(root, getkthfirst(root, x) - 1));
		}
		if (cas == 6)
		{
			int x;
			scanf("%d", &x);
			printf("%d\n", findkth(root, getkthlast(root, x) + 1));
		}
	}
	return 0;
}
