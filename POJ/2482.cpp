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

struct node
{
	int x, y, key;
};

const long long INF = (long long)1000000000 * 1000000000;
const int _n = 10000 + 10;
int n, W, H;
node x[_n];
int knum, root;
long long sum[70 * _n], maxx[70 * _n];
int ch[70 * _n][2];
long long ans;

bool comp(node x, node y)
{
	return x.x < y.x;
}

void pushup(int k)
{
	maxx[k] = std::max(maxx[ch[k][0]], maxx[ch[k][1]]) + sum[k];
}

void change(int &k, long long l, long long r, long long L, long long R, int delta)
{
	if (! k)
	{
		knum++;
		k = knum;
		sum[k] = maxx[k] = 0;
		ch[k][0] = ch[k][1] = 0;
	}
	if (L <= l && r <= R)
	{
		sum[k] += delta;
		maxx[k] += delta;
		return;
	}
	long long mid = (l + r) >> 1;
	if (L <= mid)
	{
		change(ch[k][0], l, mid, L, R, delta);
	}
	if (R > mid)
	{
		change(ch[k][1], mid + 1, r, L, R, delta);
	}
	pushup(k);
}

int main()
{
#ifdef debug
	freopen("2482.in", "r", stdin);
#endif
	while (scanf("%d%d%d", &n, &W, &H) == 3)
	{
		W -= 1;
		H -= 1;
		for (int i = 1; i <= n; i++)
		{
			x[i].x = read();
			x[i].y = read();
			x[i].key = read();
		}
		std::sort(x + 1, x + n + 1, comp);
		ans = 0;
		root = 0;
		knum = 0;
		int head = 1;
		for (int tail = 1; tail <= n; tail++)
		{
			change(root, -INF, INF, x[tail].y, (long long)x[tail].y + H, x[tail].key);
			while (head <= tail && x[tail].x - x[head].x > W)
			{
				change(root, -INF, INF, x[head].y, (long long)x[head].y + H, -x[head].key);
				head++;
			}
			ans = std::max(ans, maxx[root]);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
