#include <cstdio>
#include <cstdlib>
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

namespace Treap
{
	int knum, root;
	int size[_n], rank[_n], tree[_n], tag[_n], ch[_n][2];

	int randx()
	{
		return (rand() << 16) + rand();
	}

	void pushup(int x)
	{
		size[x] = size[ch[x][0]] + size[ch[x][1]] + 1;
	}

	void pushdown(int x)
	{
		if (tag[x])
		{
			std::swap(ch[x][0], ch[x][1]);
			tag[ch[x][0]] ^= 1;
			tag[ch[x][1]] ^= 1;
			tag[x] = 0;
		}
	}

	int newnode(int x)
	{
		knum++;
		size[knum] = 1;
		rank[knum] = randx();
		tree[x] = x;
		return knum;
	}

	int merge(int x, int y)
	{
		if (x == 0 || y == 0)
		{
			return x + y;
		}
		pushdown(x);
		pushdown(y);
		if (rank[x] < rank[y])
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

	std::pair<int, int> split(int x, int sz)
	{
		if (! x)
		{
			return std::make_pair(0, 0);
		}
		pushdown(x);
		if (sz < size[ch[x][0]] + 1)
		{
			std::pair<int, int> tmp = split(ch[x][0], sz);
			ch[x][0] = tmp.second;
			pushup(x);
			return std::make_pair(tmp.first, x);
		}
		else
		{
			std::pair<int, int> tmp = split(ch[x][1], sz - size[ch[x][0]] - 1);
			ch[x][1] = tmp.first;
			pushup(x);
			return std::make_pair(x, tmp.second);
		}
	}

	void print(int x)
	{
		if (! x)
		{
			return;
		}
		pushdown(x);
		print(ch[x][0]);
		printf("%d ", tree[x]);
		print(ch[x][1]);
	}
}

using namespace Treap;

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		root = merge(root, newnode(i));
	}
	while (m--)
	{
		int l = read();
		int r = read();
		std::pair<int, int> ll = split(root, l - 1);
		std::pair<int, int> rr = split(ll.second, r - l + 1);
		int mid = rr.first;
		tag[mid] ^= 1;
		root = merge(ll.first, merge(mid, rr.second));
	}
	print(root);
	puts("");
	return 0;
}
