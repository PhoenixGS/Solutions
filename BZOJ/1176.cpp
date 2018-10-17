#include <cstdio>
#include <cstring>
#include <algorithm>

struct node
{
	int cas;
	int x, y, delta;
	int id;
	int times;

	bool operator < (const node &y) const
	{
		return x < y.x;
	}
};

node x[400000], v[400000];
int bit[3000000], tim[3000000];
int last;
int ss, n;
int ans[300000];
int times;
int cas;
int ques;

int lowbit(int x)
{
	return x & -x;
}

void change(int x, int delta)
{
	for (int i = x; i <= n; i += lowbit(i))
	{
		if (tim[i] != times)
		{
			bit[i] = 0;
			tim[i] = times;
		}
		bit[i] += delta;
	}
}

int query(int x)
{
	int ans = 0;
	for (int i = x; i; i -= lowbit(i))
	{
		if (tim[i] == times)
		{
			ans += bit[i];
		}
	}
	return ans;
}

void CDQ(int l, int r)
{
	if (l == r)
	{
		return;
	}
	int mid = (l + r) >> 1;
	int k1 = l - 1;
	int k2 = mid;
	for (int i = l; i <= r; i++)
	{
		if (x[i].times <= mid)
		{
			k1++;
			v[k1] = x[i];
		}
		else
		{
			k2++;
			v[k2] = x[i];
		}
	}
	memcpy(x + l, v + l, sizeof(v[0]) * (r - l + 1));
	CDQ(l, mid);
	times++;
	int now = l;
	for (int i = mid + 1; i <= r; i++)
	{
		for (; x[now].x <= x[i].x && now <= mid; now++)
		{
			if (x[now].cas == 1)
			{
				change(x[now].y, x[now].delta);
			}
		}
		if (x[i].cas == 2)
		{
			ans[x[i].id] += x[i].delta * query(x[i].y);
		}
	}
	CDQ(mid + 1, r);
	k1 = l;
	k2 = mid + 1;
	for (int i = l; i <= r; i++)
	{
		if (k2 > r || k1 <= mid && x[k1] < x[k2])
		{
			v[i] = x[k1];
			k1++;
		}
		else
		{
			v[i] = x[k2];
			k2++;
		}
	}
	memcpy(x + l, v + l, sizeof(v[0]) * (r - l + 1));
}

int main()
{
	scanf("%d%d", &ss, &n);
	ques = 0;
	while (scanf("%d", &cas) == 1 && cas != 3)
	{
		if (cas == 1)
		{
			int xx, yy, delta;
			scanf("%d%d%d", &xx, &yy, &delta);
			last++;
			x[last].cas = 1;
			x[last].x = xx;
			x[last].y = yy;
			x[last].delta = delta;
			x[last].times = last;
		}
		else
		{
			int x1, y1, x2, y2;
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			ques++;
			last++;
			x[last].cas = 2;
			x[last].x = x2;
			x[last].y = y2;
			x[last].delta = 1;
			x[last].id = ques;
			x[last].times = last;
			last++;
			x[last].cas = 2;
			x[last].x = x1 - 1;
			x[last].y = y2;
			x[last].delta = -1;
			x[last].id = ques;
			x[last].times = last;
			last++;
			x[last].cas = 2;
			x[last].x = x2;
			x[last].y = y1 - 1;
			x[last].delta = -1;
			x[last].id = ques;
			x[last].times = last;
			last++;
			x[last].cas = 2;
			x[last].x = x1 - 1;
			x[last].y = y1 - 1;
			x[last].delta = 1;
			x[last].id = ques;
			x[last].times = last;
		}
	}
	std::sort(x + 1, x + last + 1);
	CDQ(1, last);
	for (int i = 1; i <= ques; i++)
	{
		printf("%d\n", ans[i]);
	}
	return 0;
}
