#include <cstdio>
#include <cstring>

int knum;
char st[10000];
int ch[1000000][26];
int tot[1000000];
int n;

void add(int k, char *st)
{
	if (st[1] == '\0')
	{
		return;
	}
	if (! ch[k][st[1] - 'a'])
	{
		knum++;
		ch[k][st[1] - 'a'] = knum;
	}
	tot[ch[k][st[1] - 'a']]++;
	add(ch[k][st[1] - 'a'], st + 1);
}

int query(int k, char *st)
{
	if (st[1] == '\0')
	{
		return tot[k];
	}
	if (! ch[k][st[1] - 'a'])
	{
		return 0;
	}
	return query(ch[k][st[1] - 'a'], st + 1);
}

int main()
{
	knum = 0;
	while (1)
	{
		gets(st + 1);
		n = strlen(st + 1);
		if (n == 0)
		{
			break;
		}
		add(0, st);
	}
	while (scanf("%s", st + 1) != EOF)
	{
		printf("%d\n", query(0, st));
	}
	return 0;
}
