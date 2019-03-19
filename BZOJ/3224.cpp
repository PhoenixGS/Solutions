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
int n;
int root, knum;
int size[_n], tree[_n], rank[_n], ch[_n][2];

int randx()
{
	return (rand() << 16) + rand();
}

void pushup(int k)
{
	size[k] = size[ch[k][0]] + size[ch[k][1]] + 1;
}

int get(int key)
{
	int now = root;
	int ans = 0;
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

int newnode(int key)
{
	knum++;
	size[knum] = 1;
	tree[knum] = key;
	rank[knum] = randx();
	return knum;
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

int find(int k)
{
	int now = root;
	while (size[ch[now][0]] + 1 != k)
	{
		if (k <= size[ch[now][0]])
		{
			now = ch[now][0];
		}
		else
		{
			k -= size[ch[now][0]] + 1;
			now = ch[now][1];
		}
	}
	return now;
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

int main()
{
#ifdef debug
	freopen("3224.in", "r", stdin);
#endif
	scanf("%d", &n);
	while (n--)
	{
		int cas = read();
		if (cas == 1)
		{
			insert(read());
		}
		if (cas == 2)
		{
			erase(read());
		}
		if (cas == 3)
		{
			printf("%d\n", get(read()) + 1);
		}
		if (cas == 4)
		{
			printf("%d\n", tree[find(read())]);
		}
		if (cas == 5)
		{
			printf("%d\n", tree[find(get(read()))]);
		}
		if (cas == 6)
		{
			printf("%d\n", tree[find(get(read() + 1) + 1)]);
		}
	}
	return 0;
}
