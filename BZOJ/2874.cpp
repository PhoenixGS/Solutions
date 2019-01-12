#include <cstdio>
#include <algorithm>
#include <iostream>

long long read()
{
	char last = '+', ch = getchar();
	while (ch < '0' || ch > '9') last = ch, ch = getchar();
	long long tmp = 0;
	while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
	if (last == '-') tmp = -tmp;
	return tmp;
}

struct changes
{
	int x, y, s;
};

const int A = 0, D = 100000000 + 10;
const int _k = 40000 + 10;
int n, m, k, q;
int last;
changes v[4 * _k];
int cnt;
int z[4 * _k];
int knum;
int root[4 * _k];
unsigned long long sum[4 * 30 * _k], sumx[4 * 30 * _k], sumy[4 * 30 * _k], sumxy[4 * 30 * _k];
int ch[4 * 30 * _k][2];
unsigned long long lastans;

bool comp(changes x, changes y)
{
	return x.x < y.x;
}

void pushup(int k)
{
	sum[k] = sum[ch[k][0]] + sum[ch[k][1]];
	sumx[k] = sumx[ch[k][0]] + sumx[ch[k][1]];
	sumy[k] = sumy[ch[k][0]] + sumy[ch[k][1]];
	sumxy[k] = sumxy[ch[k][0]] + sumxy[ch[k][1]];
}

void change(int &k, int l, int r, unsigned long long x, unsigned long long y, unsigned long long delta)
{
	knum++;
	sum[knum] = sum[k];
	sumx[knum] = sumx[k];
	sumy[knum] = sumy[k];
	sumxy[knum] = sumxy[k];
	ch[knum][0] = ch[k][0];
	ch[knum][1] = ch[k][1];
	k = knum;
	if (l == r)
	{
		sum[k] += delta;
		sumx[k] += delta * x;
		sumy[k] += delta * y;
		sumxy[k] += delta * x * y;
		return;
	}
	int mid = (l + r) >> 1;
	if (y <= mid)
	{
		change(ch[k][0], l, mid, x, y, delta);
	}
	else
	{
		change(ch[k][1], mid + 1, r, x, y, delta);
	}
	pushup(k);
}

unsigned long long query(int k, int l, int r, unsigned long long x, unsigned long long y)
{
	if (1 <= l && r <= y)
	{
		return sum[k] * (x * y + x + y + 1ull) - sumx[k] * (y + 1) - sumy[k] * (x + 1) + sumxy[k];
	}
	unsigned long long ans = 0;
	int mid = (l + r) >> 1;
	if (1 <= mid)
	{
		ans += query(ch[k][0], l, mid, x, y);
	}
	if (y > mid)
	{
		ans += query(ch[k][1], mid + 1, r, x, y);
	}
	return ans;
}

unsigned long long calc(int xx, int yy)
{
	int xxx = std::upper_bound(z + 1, z + cnt + 1, xx) - z - 1;
	return query(root[xxx], A, D, xx, yy);
}

int main()
{
	std::ios::sync_with_stdio(false);
#ifdef debug
	freopen("2874.in", "r", stdin);
#endif
	scanf("%d%d%d%d", &n, &m, &k, &q);
	for (int i = 1; i <= k; i++)
	{
		int x1, x2, y1, y2, s;
		x1 = read();
		x2 = read();
		y1 = read();
		y2 = read();
		s = read();
		last++;
		v[last].x = x1;
		v[last].y = y1;
		v[last].s = s;
		last++;
		v[last].x = x1;
		v[last].y = y2 + 1;
		v[last].s = -s;
		last++;
		v[last].x = x2 + 1;
		v[last].y = y1;
		v[last].s = -s;
		last++;
		v[last].x = x2 + 1;
		v[last].y = y2 + 1;
		v[last].s = s;
	}
	std::sort(v + 1, v + last + 1, comp);
	cnt = 1;
	z[cnt] = 0;
	root[cnt] = root[cnt - 1];
	for (int i = 1; i <= last; i++)
	{
		if (v[i].x != v[i - 1].x)
		{
			cnt++;
			z[cnt] = v[i].x;
			root[cnt] = root[cnt - 1];
		}
		change(root[cnt], A, D, v[i].x, v[i].y, v[i].s);
	}
	cnt++;
	z[cnt] = n + 1;
	root[cnt] = root[cnt - 1];
	while (q--)
	{
		int xx = read();
		int yy = read();
		int x1, x2, y1, y2;
		x1 = lastans % n + 1;
		x2 = (xx + lastans % n) % n + 1;
		y1 = lastans % m + 1;
		y2 = (yy + lastans % m) % m + 1;
		if (x1 > x2)
		{
			std::swap(x1, x2);
		}
		if (y1 > y2)
		{
			std::swap(y1, y2);
		}
		lastans = calc(x2, y2) - calc(x1 - 1, y2) + calc(x1 - 1, y1 - 1) - calc(x2, y1 - 1);
		std::cout << lastans << std::endl;
	}
	return 0;
}
