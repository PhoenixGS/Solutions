#include <cstdio>
#include <cmath>
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

struct QUES
{
	int l, r, L, R, id;
};

int n, m;
int x[200000];
QUES ques[1000005];
int cnt[200000];
int ss[2000], cc[200000];
int knumber;
int knum[200000];
int ans[1000005];

inline bool comp(QUES x, QUES y)
{
	if (knum[x.l] == knum[y.l])
	{
		if (knum[x.l] & 1)
		{
			return x.r < y.r;
		}
		else
		{
			return x.r > y.r;
		}
	}
	return knum[x.l] < knum[y.l];
}

inline void change(int pos, int delta)
{
	cc[pos] += delta;
	ss[knum[pos]] += delta;
}

inline int query(int l, int r)
{
	int ans = 0;
	if (knum[l] == knum[r])
	{
		for (int i = l; i <= r; i++)
		{
			ans += cc[i];
		}
		return ans;
	}
	int ll = knum[l] + 1;
	int rr = knum[r] - 1;
	for (int i = l; i <= (ll - 1) * knumber; i++)
	{
		ans += cc[i];
	}
	for (int i = ll; i <= rr; i++)
	{
		ans += ss[i];
	}
	for (int i = rr * knumber + 1; i <= r; i++)
	{
		ans += cc[i];
	}
	return ans;
}

inline void update(int pos, int cas)
{
	if (cas == 1)
	{
		if (cnt[x[pos]] == 0)
		{
			change(x[pos], 1);
		}
		cnt[x[pos]]++;
	}
	else
	{
		cnt[x[pos]]--;
		if (cnt[x[pos]] == 0)
		{
			change(x[pos], -1);
		}
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		x[i] = read();
	}
	for (int i = 1; i <= m; i++)
	{
		ques[i].l = read();
		ques[i].r = read();
		ques[i].L = read();
		ques[i].R = read();
		ques[i].id = i;
	}
	knumber = sqrt(n);
	for (int i = 1; i <= n; i++)
	{
		knum[i] = (i - 1) / knumber + 1;
	}
	std::sort(ques + 1, ques + m + 1, comp);
	int l = 1;
	int r = 0;
	for (int i = 1; i <= m; i++)
	{
		for (; r < ques[i].r; r++)
		{
			update(r + 1, 1);
		}
		for (; l > ques[i].l; l--)
		{
			update(l - 1, 1);
		}
		for (; r > ques[i].r; r--)
		{
			update(r, -1);
		}
		for (; l < ques[i].l; l++)
		{
			update(l, -1);
		}
		ans[ques[i].id] = query(ques[i].L, ques[i].R);
	}
	for (int i = 1; i <= m; i++)
	{
		printf("%d\n", ans[i]);
	}
	return 0;
}
