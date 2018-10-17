#include <cstdio>
#include <algorithm>

int n, m;
int root[200000], rev[200000];
int tag[1000000];
int num;
int ch[10000000][2], sum[10000000];

void pushup(int k)
{
	if (k)
	{
		sum[k] = sum[ch[k][0]] + sum[ch[k][1]];
	}
}

void change(int &u, int l, int r, int pos, int delta)
{
	num++;
	u = num;
	sum[u] = delta;
	if (l == r)
	{
		return;
	}
	int mid = l + r >> 1;
	if (pos <= mid)
	{
		change(ch[u][0], l, mid, pos, delta);
	}
	else
	{
		change(ch[u][1], mid + 1, r, pos, delta);
	}
}

int query(int k, int l, int r, int rank)
{
	if (l == r)
	{
		return l;
	}
	int mid = l + r >> 1;
	if (rank <= sum[ch[k][0]])
	{
		return query(ch[k][0], l, mid, rank);
	}
	else
	{
		return query(ch[k][1], mid + 1, r, rank - sum[ch[k][0]]);
	}
}

std::pair<int, int> split(int x, int rank)
{
	if (! x)
	{
		return std::make_pair(0, 0);
	}
	if (rank <= sum[ch[x][0]])
	{
		std::pair<int, int> tmp = split(ch[x][0], rank);
		num++;
		ch[num][0] = tmp.first;
		ch[x][0] = tmp.second;
		sum[num] = rank;
		sum[x] = sum[x] - rank;
		return std::make_pair(num, x);
	}
	else
	{
		std::pair<int, int> tmp = split(ch[x][1], rank - sum[ch[x][0]]);
		num++;
		ch[num][1] = tmp.second;
		ch[x][1] = tmp.first;
		sum[num] = sum[x] - rank;
		sum[x] = rank;
		return std::make_pair(x, num);
	}
}

std::pair<int, int> split(int x, int rank, int cas)
{
	std::pair<int, int> ans;
	if (cas)
	{
		ans = split(x, sum[x] - rank);
		std::swap(ans.first, ans.second);
		return ans;
	}
	else
	{
		ans = split(x, rank);
		return ans;
	}
}

void merge(int &x, int y)
{
	if (! y)
	{
		return;
	}
	if (! x)
	{
		x = y;
		return;
	}
	sum[x] += sum[y];
	merge(ch[x][0], ch[y][0]);
	merge(ch[x][1], ch[y][1]);
}

void pushdownbelong(int k)
{
	if (tag[k])
	{
		tag[k << 1] = tag[k << 1 | 1] = tag[k];
		tag[k] = 0;
	}
}

void buildbelong(int k, int l, int r)
{
	tag[k] = 0;
	if (l == r)
	{
		tag[k] = l;
		return;
	}
	int mid = l + r >> 1;
	buildbelong(k << 1, l, mid);
	buildbelong(k << 1 | 1, mid + 1, r);
}

void changebelong(int k, int l, int r, int L, int R, int newvalue)
{
	if (L <= l && r <= R)
	{
		tag[k] = newvalue;
		return;
	}
	pushdownbelong(k);
	int mid = l + r >> 1;
	if (L <= mid)
	{
		changebelong(k << 1, l, mid, L, R, newvalue);
	}
	if (R > mid)
	{
		changebelong(k << 1 | 1, mid + 1, r, L, R, newvalue);
	}
}

int querybelong(int k, int l, int r, int pos)
{
	if (l == r)
	{
		return tag[k];
	}
	pushdownbelong(k);
	int mid = l + r >> 1;
	if (pos <= mid)
	{
		return querybelong(k << 1, l, mid, pos);
	}
	else
	{
		return querybelong(k << 1 | 1, mid + 1, r, pos);
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		change(root[i], 1, n, x, 1);
		rev[i] = 0;
	}
	buildbelong(1, 1, n);
	for (int i = 1; i <= m; i++)
	{
		int cas, l, r;
		scanf("%d%d%d", &cas, &l, &r);
		int ll = querybelong(1, 1, n, l);
		int rr = querybelong(1, 1, n, r);
		if (ll == rr)
		{
			std::pair<int, int> x1, x2;
			int v = rev[ll];
			x1 = split(root[ll], l - ll, v);
			x2 = split(x1.second, r - l + 1, v);
			if (sum[x1.first])
			{
				root[ll] = x1.first;
				rev[ll] = v;
				changebelong(1, 1, n, ll, ll + sum[x1.first] - 1, ll);
			}
			if (sum[x2.first])
			{
				root[l] = x2.first;
				rev[l] = cas;
				changebelong(1, 1, n, l, l + sum[x2.first] - 1, l);
			}
			if (sum[x2.second])
			{
				root[r + 1] = x2.second;
				rev[r + 1] = v;
				changebelong(1, 1, n, r + 1, r + 1 + sum[x2.second] - 1, r + 1);
			}
		}
		else
		{
			int now = 0;
			for (int j = ll + sum[root[ll]]; j != rr; j = j + sum[root[j]])
			{
				merge(now, root[j]);
			}
			int v;
			std::pair<int, int> tmp;
			v = rev[ll];
			tmp = split(root[ll], l - ll, v);
			if (sum[tmp.first])
			{
				root[ll] = tmp.first;
				rev[ll] = v;
				changebelong(1, 1, n, ll, ll + sum[tmp.first] - 1, ll);
			}
			merge(now, tmp.second);
			v = rev[rr];
			tmp = split(root[rr], r - rr + 1, v);
			if (sum[tmp.second])
			{
				root[r + 1] = tmp.second;
				rev[r + 1] = v;
				changebelong(1, 1, n, r + 1, r + 1 + sum[tmp.second] - 1, r + 1);
			}
			merge(now, tmp.first);
			root[l] = now;
			rev[l] = cas;
			changebelong(1, 1, n, l, r, l);
		}
	}
	int pos;
	scanf("%d", &pos);
	int kk = querybelong(1, 1, n, pos);
	if (rev[kk])
	{
		printf("%d\n", query(root[kk], 1, n, sum[root[kk]] - (pos - kk + 1) + 1));
	}
	else
	{
		printf("%d\n", query(root[kk], 1, n, pos - kk + 1));
	}
	return 0;
}

