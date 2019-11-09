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
int n;

struct Treap
{
	int knum, root;
	int size[_n], tree[_n], rank[_n], ch[_n][2];

	int randx()
	{
		return ((rand() << 16) + rand());
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

	int find(int rk)
	{
		int now = root;
		while (size[ch[now][0]] + 1 != rk)
		{
			if (rk <= size[ch[now][0]])
			{
				now = ch[now][0];
			}
			else
			{
				rk -= size[ch[now][0]] + 1;
				now = ch[now][1];
			}
		}
		return now;
	}

	int merge(int x, int y)
	{
		if (! x || ! y)
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

	std::pair<int, int> split(int x, int k)
	{
		if (! x)
		{
			return std::make_pair(0, 0);
		}
		if (k <= size[ch[x][0]])
		{
			std::pair<int, int> tmp = split(ch[x][0], k);
			ch[x][0] = tmp.second;
			pushup(x);
			return std::make_pair(tmp.first, x);
		}
		else
		{
			std::pair<int, int> tmp = split(ch[x][1], k - size[ch[x][0]] - 1);
			ch[x][1] = tmp.first;
			pushup(x);
			return std::make_pair(x, tmp.second);
		}
	}

	void insert(int key)
	{
		int cnt = get(key);
		std::pair<int, int> tmp = split(root, cnt);
		root = merge(tmp.first, merge(newnode(key), tmp.second));
	}

	void del(int key)
	{
		int cnt = get(key);
		std::pair<int, int> tmp = split(root, cnt);
		root = merge(tmp.first, split(tmp.second, 1).second);
	}
}treap;

int main()
{
	scanf("%d", &n);
	while (n--)
	{
		int op;
		scanf("%d", &op);
		if (op == 1)
		{
			treap.insert(read());
		}
		if (op == 2)
		{
			treap.del(read());
		}
		if (op == 3)
		{
			printf("%d\n", treap.get(read()) + 1);
		}
		if (op == 4)
		{
			printf("%d\n", treap.tree[treap.find(read())]);
		}
		if (op == 5)
		{
			printf("%d\n", treap.tree[treap.find(treap.get(read()))]);
		}
		if (op == 6)
		{
			printf("%d\n", treap.tree[treap.find(treap.get(read() + 1) + 1)]);
		}
	}
	return 0;
}
