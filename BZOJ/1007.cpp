#include <cstdio>
#include <algorithm>

struct LINE
{
	int k, b, id;
};

const double eps = 1e-7;
int n;
LINE x[60000];
int top;
int stack[60000];
int ans[60000];

double abss(double x)
{
	return x > 0 ? x : -x;
}

bool comp(LINE x, LINE y)
{
	return y.k - x.k > eps || abss(y.k - x.k) < eps && y.b - x.b > eps;
}

double calcpoint(LINE x, LINE y)
{
	return (double)(y.b - x.b) / (double)(x.k - y.k);
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%d", &x[i].k, &x[i].b);
		x[i].id = i;
	}
	std::sort(x + 1, x + n + 1, comp);
	top = 0;
	for (int i = 1; i <= n; i++)
	{
		while (top && ((abss(x[i].k - x[stack[top]].k) < eps && x[i].b - x[stack[top]].b > eps)))
		{
			top--;
		}
		while (top > 1 && (abss(x[i].k - x[stack[top]].k) > eps && (! (calcpoint(x[stack[top]], x[i]) - calcpoint(x[stack[top - 1]], x[stack[top]]) > eps))))
		{
			top--;
		}
		top++;
		stack[top] = i;
	}
	for (int i = 1; i <= top; i++)
	{
		ans[x[stack[i]].id] = 1;
	}
	for (int i = 1; i <= n; i++)
	{
		if (ans[i])
		{
			printf("%d ", i);
		}
	}
	puts("");
	return 0;
}
