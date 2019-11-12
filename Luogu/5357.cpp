#include <cstdio>
#include <cstring>

int n;
char s[2000000 + 10];
int knum;
int ch[200000 + 10][26], f[200000 + 10], sum[200000 + 10];
int head, tail;
int que[200000 + 10];
int pos[200000 + 10];

void add(char *s, int idx)
{
	int len = strlen(s + 1);
	int u = 0;
	for (int i = 1; i <= len; i++)
	{
		int c = s[i] - 'a';
		if (! ch[u][c])
		{
			knum++;
			ch[u][c] = knum;
		}
		u = ch[u][c];
	}
	pos[idx] = u;
}

void getfail()
{
	head = 1;
	tail = 0;
	f[0] = 0;
	for (int i = 0; i < 26; i++)
	{
		if (ch[0][i])
		{
			f[ch[0][i]] = 0;
			tail++;
			que[tail] = ch[0][i];
		}
	}
	while (head <= tail)
	{
		int u = que[head];
		head++;
		for (int i = 0; i < 26; i++)
		{
			int v = ch[u][i];
			if (! v)
			{
				ch[u][i] = ch[f[u]][i];
				continue;
			}
			f[v] = ch[f[u]][i];
			tail++;
			que[tail] = v;
		}
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%s", s + 1);
		add(s, i);
	}
	getfail();
	scanf("%s", s + 1);
	int u = 0;
	int len = strlen(s + 1);
	for (int i = 1; i <= len; i++)
	{
		int c = s[i] - 'a';
		u = ch[u][c];
		sum[u]++;
	}
	for (int i = tail; i > 0; i--)
	{
		sum[f[que[i]]] += sum[que[i]];
	}
	for (int i = 1; i <= n; i++)
	{
		printf("%d\n", sum[pos[i]]);
	}
	return 0;
}

