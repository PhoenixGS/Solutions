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

const int _n = 200000 + 10;
int n;
int bit;
int tree[2 * _n];
int pos[_n], key[_n];
int ans[_n];

inline int lowbit(int x)
{
	return x & -x;
}

void add(int x, int delta)
{
	for (int i = x; i < (1 << bit); i += lowbit(i))
	{
		tree[i] += delta;
	}
}

int find(int key)
{
	int ans = 0;
	for (int i = bit - 1; i >= 0; i--)
	{
		if (tree[ans + (1 << i)] <= key)
		{
			ans += 1 << i;
			key -= tree[ans];
		}
	}
	return ans;
}

int main()
{
	while (scanf("%d", &n) == 1)
	{
		bit = 0;
		while ((1 << bit) <= n)
		{
			bit++;
		}
		for (int i = 1; i <= n; i++)
		{
			tree[i] = 0;
		}
		for (int i = 1; i <= n; i++)
		{
			add(i, 1);
		}
		for (int i = 1; i <= n; i++)
		{
			pos[i] = read();
			key[i] = read();
		}
		for (int i = n; i >= 1; i--)
		{
			int idx = find(pos[i]) + 1;
			ans[idx] = key[i];
			add(idx, -1);
		}
		for (int i = 1; i <= n; i++)
		{
			printf("%d ", ans[i]);
		}
		puts("");
	}
	return 0;
}
