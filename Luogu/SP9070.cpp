#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

const int _n = 500000 + 10;
int n;
int x[_n];
int k[_n], que[_n];
double sq[_n], p[_n];

inline double get_f(int i, int j)
{
	return x[j] + sq[i - j];
}

int get_k(int j1, int j2)
{
	int l = j2;
	int r = (k[j1] ? k[j1] : n) + 1;
	while (l < r)
	{
		int mid = (l + r) >> 1;
		if (get_f(mid, j1) <= get_f(mid, j2))
		{
			r = mid;
		}
		else
		{
			l = mid + 1;
		}
	}
	return l;
}

void solve()
{
	int head = 1;
	int tail = 0;
	for (int i = 1; i <= n; i++)
	{
		while (head < tail && get_f(k[tail - 1], que[tail]) < get_f(k[tail - 1], i))
		{
			tail--;
		}
		k[tail] = get_k(que[tail], i);
		tail++;
		que[tail] = i;
		while (head < tail && k[head] <= i)
		{
			head++;
		}
		p[i] = std::max(p[i], get_f(i, que[head]));
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x[i]);
		sq[i] = sqrt(i);
	}
	solve();
	for (int i = 1; i <= n / 2; i++)
	{
		std::swap(x[i], x[n - i + 1]);
		std::swap(p[i], p[n - i + 1]);
	}
	memset(k, 0, sizeof(k));
	solve();
	for (int i = n; i >= 1; i--)
	{
		printf("%d\n", std::max((int)ceil(p[i]) - x[i], 0));
	}
	return 0;
}
