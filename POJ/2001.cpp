#include <cstdio>

int knum;
int n;
char st[1005][30];
int ch[30000][30];
int tot[30000];

void add(int k, char *st)
{
	tot[k]++;
	if (st[1] == '\0')
	{
		return;
	}
	if (! ch[k][st[1] - 'a'])
	{
		knum++;
		ch[k][st[1] - 'a'] = knum;
	}
	add(ch[k][st[1] - 'a'], st + 1);
}

void query(int k, char *st)
{
	if (st[1] == '\0' || tot[k] == 1)
	{
		return;
	}
	printf("%c", st[1]);
	query(ch[k][st[1] - 'a'], st + 1);
}

int main()
{
	knum = 0;
	n = 0;
	while (scanf("%s", st[++n] + 1) != EOF)
	{
		add(0, st[n]);
	}
	for (int i = 1; i <= n; i++)
	{
		printf("%s ", st[i] + 1);
		query(0, st[i]);
		printf("\n");
	}
	return 0;
}
