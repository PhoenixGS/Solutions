#include <cstdio>
#include <queue>

long long read()
{
	char last = '+', ch = getchar();
	while (ch < '0' || ch > '9') last = ch, ch = getchar();
	long long tmp = 0;
	while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
	if (last == '-') tmp = -tmp;
	return tmp;
}

const int _n = 500000 + 10;
int n, k;
long long x[_n];
int knum;
int root[_n], now[_n];
int size[40 * _n], ch[40 * _n][2];
std::priority_queue<std::pair<long long, int> > heap;
long long ans;

void add(int u, int &v, long long key, int pos)
{
	knum++;
	v = knum;
	size[v] = size[u];
	ch[v][0] = ch[u][0];
	ch[v][1] = ch[u][1];
	if (pos == -1)
	{
		size[v]++;
		return;
	}
	if (key & (1ll << pos))
	{
		add(ch[u][1], ch[v][1], key, pos - 1);
	}
	else
	{
		add(ch[u][0], ch[v][0], key, pos - 1);
	}
	size[v] = size[ch[v][0]] + size[ch[v][1]];
}

inline long long find(int u, int rk, long long key)
{
	long long ans = 0;
	for (int i = 31; i >= 0; i--)
	{
		int w = ((key >> i) & 1ll);
		if (rk <= size[ch[u][w ^ 1]])
		{
			ans += (1ll << i);
			u = ch[u][w ^ 1];
		}
		else
		{
			rk -= size[ch[u][w ^ 1]];
			u = ch[u][w];
		}
	}
	return ans;
}

int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++)
	{
		x[i] = read();
		x[i] = x[i] ^ x[i - 1];
	}
	for (int i = 1; i <= n; i++)
	{
		add(root[i - 1], root[i], x[i - 1], 31);
	}
	for (int i = 1; i <= n; i++)
	{
		now[i] = 1;
		heap.push(std::make_pair(find(root[i], now[i], x[i]), i));
	}
	ans = 0;
	while (k--)
	{
		std::pair<long long, int> z = heap.top();
		heap.pop();
		ans += z.first;
		now[z.second]++;
		if (now[z.second] <= z.second)
		{
			heap.push(std::make_pair(find(root[z.second], now[z.second], x[z.second]), z.second));
		}
	}
	printf("%lld\n", ans);
	return 0;
}
