#include <cstdio>
#include <cmath>
#include <algorithm>

struct QUES
{
	int l, r, id, time;
};

struct CHANGES
{
	int pos, oldvalue, newvalue;
};

int n, m;
int x[20000], tmp[20000];
char cas[100];
int quesnum, changesnum;
QUES ques[20000];
CHANGES changes[20000];
int knumber;
int knum[20000];
int cnt[2000000];
int anss[20000];
int l, r;
int ans;

bool comp(QUES x, QUES y)
{
	if (knum[x.l] != knum[y.l])
	{
		return knum[x.l] < knum[y.l];
	}
	if (knum[x.r] != knum[y.r])
	{
		return knum[x.r] < knum[y.r];
	}
	return x.time < y.time;
}

void change(int pos, int newvalue)
{
	if (l <= pos && pos <= r)
	{
		cnt[x[pos]]--;
		if (cnt[x[pos]] == 0)
		{
			ans--;
		}
		if (cnt[newvalue] == 0)
		{
			ans++;
		}
		cnt[newvalue]++;
	}
	x[pos] = newvalue;
}

void add(int pos)
{
	if (cnt[x[pos]] == 0)
	{
		ans++;
	}
	cnt[x[pos]]++;
}

void del(int pos)
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
	for (int i = 1; i <= m; i++)
	{
		scanf("%s", cas + 1);
		if (cas[1] == 'Q')
		{
			quesnum++;
			scanf("%d%d", &ques[quesnum].l, &ques[quesnum].r);
			ques[quesnum].id = quesnum;
			ques[quesnum].time = changesnum;
		}
		else
		{
			changesnum++;
			scanf("%d%d", &changes[changesnum].pos, &changes[changesnum].newvalue);
			changes[changesnum].oldvalue = tmp[changes[changesnum].pos];
			tmp[changes[changesnum].pos] = changes[changesnum].newvalue;
		}
	}
	knumber = sqrt(n);
	for (int i = 1; i <= n; i++)
	{
		knum[i] = (i - 1) / knumber + 1;
	}
	std::sort(ques + 1, ques + quesnum + 1, comp);
	l = 1;
	r = 0;
	int nowtime = 0;
	for (int i = 1; i <= quesnum; i++)
	{
		while (nowtime < ques[i].time)
		{
			nowtime++;
			change(changes[nowtime].pos, changes[nowtime].newvalue);
		}
		while (nowtime > ques[i].time)
		{
			change(changes[nowtime].pos, changes[nowtime].oldvalue);
			nowtime--;
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
