#include <cstdio>
#include <cstdlib>
#include <ctime>
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
int n;

namespace treap
{
	int root;
	int knum;
	int tree[_n], size[_n], rank[_n], ch[_n][2];

	inline int randx()
	{
		return (rand() << 16) + rand();
	}

	void pushup(int k)
	{
		size[k] = size[ch[k][0]] + size[ch[k][1]] + 1;
	}

	int newnode(int key)
	{
		knum++;
		size[knum] = 1;
		tree[knum] = key;
		rank[knum] = randx();
		return knum;
	}

	void print(int x)
	{
		if (! x)
		{
			return;
		}
		print(ch[x][0]);
		printf("%d ", tree[x]);
		print(ch[x][1]);
	}

	int get(int key)
	{
		int ans = 0;
		int now = root;
		while (now)
		{
			if (tree[now] < key)
			{
				ans += size[ch[now][0]] + 1;
				now = ch[now][1];
			}
			else
			{
				now = ch[now][0];
			}
		}
		return ans;
	}

	int merge(int x, int y)
	{
		if (x == 0 || y == 0)
		{
			return x + y;
		}
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

	int find(int sz)
	{
		int x = root;
		while (size[ch[x][0]] + 1 != sz)
		{
			if (sz < size[ch[x][0]] + 1)
			{
				x = ch[x][0];
			}
			else
			{
				sz -= size[ch[x][0]] + 1;
				x = ch[x][1];
			}
		}
		return x;
	}

	void insert(int key)
	{
		int k = get(key);
		std::pair<int, int> tmp = split(root, k);
		root = merge(tmp.first, merge(newnode(key), tmp.second));
	}
	
	void erase(int key)
	{
		int k = get(key);
		std::pair<int, int> tmp = split(root, k);
		root = merge(tmp.first, split(tmp.second, 1).second);
	}
}

int main()
{
#ifdef debug
	freopen("3224.in", "r", stdin);
#endif
	srand(time(NULL));
	scanf("%d", &n);
	while (n--)
	{
		int cas = read();
		if (cas == 1)
		{
			treap::insert(read());
		}
		if (cas == 2)
		{
			treap::erase(read());
		}
		if (cas == 3)
		{
			printf("%d\n", treap::get(read()) + 1);
		}
		if (cas == 4)
		{
			printf("%d\n", treap::tree[treap::find(read())]);
		}
		if (cas == 5)
		{
			printf("%d\n", treap::tree[treap::find(treap::get(read()))]);
		}
		if (cas == 6)
		{
			printf("%d\n", treap::tree[treap::find(treap::get(read() + 1) + 1)]);
		}
	}
	return 0;
}

