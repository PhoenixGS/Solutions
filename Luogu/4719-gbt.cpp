#include <cstdio>

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		x[i] = read();
	}
	for (int i = 1; i < n; i++)
	{
		int u, v;
		u = read();
		v = read();
		add(u, v);
		add(v, u);
	}
	while (m--)
	{
		int pos = read();
		int newvalue = read();

	}
}
