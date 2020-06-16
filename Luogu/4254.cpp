#include <cstdio>
#include <algorithm>

const int _n = 100000 + 10, _l = 50000 + 10;

struct func
{
	double k, b;
};

int n;
char op[10];
int fnum;
func f[_n];

double val(int x, int id)
{
	return f[id].k * x + f[id].b;
}

namespace seg
{
	int tag[4 * _l];

	void change(int k, int l, int r, int idx)
	{
		if (l == r)
		{
			if (val(l, idx) > val(l, tag[k]))
			{
				tag[k] = idx;
			}
			return;
		}
		int mid = (l + r) >> 1;
		if (f[idx].k > f[tag[k]].k)
		{
			if (val(mid, idx) > val(mid, tag[k]))
			{
				change(k << 1, l, mid, tag[k]);
				tag[k] = idx;
			}
			else
			{
				change(k << 1 | 1, mid + 1, r, idx);
			}
		}
		else
		{
			if (val(mid, idx) > val(mid, tag[k]))
			{
				change(k << 1 | 1, mid + 1, r, tag[k]);
				tag[k] = idx;
			}
			else
			{
				change(k << 1, l, mid, idx);
			}
		}
	}

	double query(int k, int l, int r, int pos)
	{
		if (l == r)
		{
			return val(pos, tag[k]);
		}
		int mid = (l + r) >> 1;
		double ans = val(pos, tag[k]);
		if (pos <= mid)
		{
			ans = std::max(ans, query(k << 1, l, mid, pos));
		}
		else
		{
			ans = std::max(ans, query(k << 1 | 1, mid + 1, r, pos));
		}
		return ans;
	}
}

using namespace seg;

void insert(double k, double b)
{
	fnum++;
	f[fnum].k = k;
	f[fnum].b = b;
	change(1, 1, 50000, fnum);
}

int main()
{
	scanf("%d", &n);
	while (n--)
	{
		scanf("%s", op + 1);
		if (op[1] == 'P')
		{
			double b, k;
			scanf("%lf%lf", &b, &k);
			b -= k;
			insert(k, b);
		}
		if (op[1] == 'Q')
		{
			int x;
			scanf("%d", &x);
			double ans = query(1, 1, 50000, x);
			printf("%d\n", (int)ans / 100);
		}
	}
	return 0;
}
