#include <cstdio>
#include <cmath>
#include <algorithm>

struct QUES
{
	int l, r, id, time;
};

struct CHANGES
{
	int pos, pre, now;
};

int n, m;
int x[20000], tmp[20000];
int cnt[2000000];
int anss[20000];
int ans;
int knumber;
int knum[20000];
QUES ques[20000];
CHANGES changes[20000];
int quesnum, changesnum;
int l, r;
char st[100];

inline bool comp(QUES x, QUES y)
{
	if (knum[x.l] != knum[y.l])
	{
		return knum[x.l] < knum[y.l];
	}
	if (knum[x.r] != knum[y.r])
	{
		if (knum[x.l] & 1)
		{
			return knum[x.r] < knum[y.r];
		}
		else
		{
			return knum[x.r] > knum[y.r];
		}
	}
	return x.time < y.time;
}

inline void change(int pos, int newvalue)
{
	if (l <= pos && pos <= r)
	{
		cnt[x[pos]]--;
		if (cnt[x[pos]] == 0)
		{
			ans--;
		}
		cnt[newvalue]++;
		if (cnt[newvalue] == 1)
		{
			ans++;
		}
	}
	x[pos] = newvalue;
}

inline void add(int pos)
{
	cnt[x[pos]]++;
	if (cnt[x[pos]] == 1)
	{
		ans++;
	}
}

inline void del(int pos)
{
	cnt[x[pos]]--;
	if (cnt[x[pos]] == 0)
	{
		ans--;
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x[i]);
		tmp[i] = x[i];
	}
	quesnum = changesnum = 0;
	for (int i = 1; i <= m; i++)
	{
		scanf("%s", st + 1);
		if (st[1] == 'Q')
		{
			quesnum++;
			scanf("%d%d", &ques[quesnum].l, &ques[quesnum].r);
			ques[quesnum].id = quesnum;
			ques[quesnum].time = changesnum;
		}
		else
		{
			int pos, newvalue;
			scanf("%d%d", &pos, &newvalue);
			changesnum++;
			changes[changesnum].pos = pos;
			changes[changesnum].pre = tmp[pos];
			changes[changesnum].now = newvalue;
			tmp[pos] = newvalue;
		}
	}
	knumber = pow(n, 0.57);
	for (int i = 1; i <= n; i++)
	{
		knum[i] = (i - 1) / knumber + 1;
	}
	std::sort(ques + 1, ques + quesnum + 1, comp);
	l = 1;
	r = 0;
	int changesnow = 0;
	ans = 0;
	for (int i = 1; i <= quesnum; i++)
	{
		while (changesnow < ques[i].time)
		{
			changesnow++;
			change(changes[changesnow].pos, changes[changesnow].now);
		}
		while (changesnow > ques[i].time)
		{
			change(changes[changesnow].pos, changes[changesnow].pre);
			changesnow--;
		}
		while (l > ques[i].l)
		{
			l--;
			add(l);
		}
		while (r < ques[i].r)
		{
			r++;
			add(r);
		}
		while (l < ques[i].l)
		{
			del(l);
			l++;
		}
		while (r > ques[i].r)
		{
			del(r);
			r--;
		}
		anss[ques[i].id] = ans;
	}
	for (int i = 1; i <= quesnum; i++)
	{
		printf("%d\n", anss[i]);
	}
	return 0;
}
