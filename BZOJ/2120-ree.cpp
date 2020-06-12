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
	int l, r, times, idx;
};

struct CHANGES
{
	int pos, pre, now;
};

const int _n = 10000 + 10, _m = 10000 + 10;
int n, m;
char s[10];
int x[_n], tmp[_n];
int z[1000000 + 10];
int quesnum;
QUES ques[_m];
int changesnum;
CHANGES changes[_m];
int ll, rr;
int knumber;
int knum[_n];
int ans[_m];
int anss;

bool comp(QUES x, QUES y)
{
	return knum[x.l] < knum[y.l] || (knum[x.l] == knum[y.l] && knum[x.r] < knum[y.r]) || (knum[x.l] == knum[y.l] && knum[x.r] == knum[y.r] && x.times < y.times);
}

void change(int pos, int newvalue)
{
	if (ll <= pos && pos <= rr)
	{
		z[x[pos]]--;
		if (z[x[pos]] == 0)
		{
			anss--;
		}
		x[pos] = newvalue;
		if (z[x[pos]] == 0)
		{
			anss++;
		}
		z[x[pos]]++;
	}
	else
	{
		x[pos] = newvalue;
	}
}

void add(int pos)
{
	if (z[x[pos]] == 0)
	{
		anss++;
	}
	z[x[pos]]++;
}

void del(int pos)
{
	z[x[pos]]--;
	if (z[x[pos]] == 0)
	{
		anss--;
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		x[i] = read();
		tmp[i] = x[i];
	}
	for (int i = 1; i <= m; i++)
	{
		scanf("%s", s + 1);
		if (s[1] == 'Q')
		{
			quesnum++;
			ques[quesnum].l = read();
			ques[quesnum].r = read();
			ques[quesnum].times = changesnum;
			ques[quesnum].idx = quesnum;
		}
		else
		{
			changesnum++;
			int pos = read();
			changes[changesnum].pos = pos;
			changes[changesnum].pre = tmp[pos];
			tmp[pos] = read();
			changes[changesnum].now = tmp[pos];
		}
	}
	knumber = pow(n, (double)2 / 3);
	for (int i = 1; i <= n; i++)
	{
		knum[i] = (i - 1) / knumber + 1;
	}
	std::sort(ques + 1, ques + quesnum + 1, comp);
	ll = 1;
	rr = 0;
	int times = 0;
	for (int i = 1; i <= quesnum; i++)
	{
		while (times < ques[i].times)
		{
			times++;
			change(changes[times].pos, changes[times].now);
		}
		while (times > ques[i].times)
		{
			change(changes[times].pos, changes[times].pre);
			times--;
		}
		while (ll > ques[i].l)
		{
			ll--;
			add(ll);
		}
		while (rr < ques[i].r)
		{
			rr++;
			add(rr);
		}
		while (ll < ques[i].l)
		{
			del(ll);
			ll++;
		}
		while (rr > ques[i].r)
		{
			del(rr);
			rr--;
		}
		ans[ques[i].idx] = anss;
	}
	for (int i = 1; i <= quesnum; i++)
	{
		printf("%d\n", ans[i]);
	}
	return 0;
}
