#include <cstdio>

const int _n = 100000 + 10, _m = 200000 + 10;
int n, m;
int knum;
int root[_m];
int tree[2 * 20 * _m], size[2 * 20 * _m], ch[2 * 20 * _m][2];

void build(int &k, int l, int r)
{
	knum++;
	k = knum;
	if (l == r)
	{
		tree[k] = l;
		size[k] = 1;
		return;
	}
	int mid = (l + r) >> 1;
	build(ch[k][0], l, mid);
	build(ch[k][1], mid + 1, r);
}

int query(int k, int l, int r, int pos)
{
	if (l == r)
	{
		return k;
	}
	int mid = (l + r) >> 1;
	if (pos <= mid)
	{
		return query(ch[k][0], l, mid, pos);
	}
	else
	{
		return query(ch[k][1], mid + 1, r, pos);
	}
}

void change(int &k, int l, int r, int pos, int newvalue)
{
	knum++;
	ch[knum][0] = ch[k][0];
	ch[knum][1] = ch[k][1];
	tree[knum] = tree[k];
	size[knum] = size[k];
	k = knum;
	if (l == r)
	{
		tree[k] = newvalue;
		return;
	}
	int mid = (l + r) >> 1;
	if (pos <= mid)
	{
		change(ch[k][0], l, mid, pos, newvalue);
	}
	else
	{
		change(ch[k][1], mid + 1, r, pos, newvalue);
	}
}

void changes(int &k, int l, int r, int pos)
{
	knum++;
	ch[knum][0] = ch[k][0];
	ch[knum][1] = ch[k][1];
	tree[knum] = tree[k];
	size[knum] = size[k];
	k = knum;
	if (l == r)
	{
		size[k]++;
		return;
	}
	int mid = (l + r) >> 1;
	if (pos <= mid)
	{
		changes(ch[k][0], l, mid, pos);
	}
	else
	{
		changes(ch[k][1], mid + 1, r, pos);
	}
}

int findfather(int idx, int x)
{
	int k = query(root[idx], 1, n, x);
	return tree[k] == x ? k : findfather(idx, tree[k]);
}

int main()
{
	scanf("%d%d", &n, &m);
	build(root[0], 1, n);
	for (int i = 1; i <= m; i++)
	{
		int op;
		scanf("%d", &op);
		if (op == 1)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			root[i] = root[i - 1];
			int xx = findfather(i, x);
			int yy = findfather(i, y);
			if (tree[xx] != tree[yy])
			{
				int xs = size[xx];
				int ys = size[yy];
				if (xs < ys)
				{
					change(root[i], 1, n, tree[xx], tree[yy]);
				}
				else
				{
					change(root[i], 1, n, tree[yy], tree[xx]);
					if (xs == ys)
					{
						changes(root[i], 1, n, tree[xx]);
					}
				}
			}
		}
		if (op == 2)
		{
			int pos;
			scanf("%d", &pos);
			root[i] = root[pos];
		}
		if (op == 3)
		{
			root[i] = root[i - 1];
			int x, y;
			scanf("%d%d", &x, &y);
			int xx = findfather(i, x);
			int yy = findfather(i, y);
			printf("%d\n", xx == yy);
		}
	}
	return 0;
}
