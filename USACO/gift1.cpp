/*
ID: thestar1
PROG: gift1
LANG: C++
*/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <map>
#include <string>

using namespace std;

int n;
string Name[100];
map<string, int> Map;

int main()
{
	freopen("gift1.in", "r", stdin);
	freopen("gift1.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		cin >> Name[i];
		Map[Name[i]] = 0;
	}
	string names;
	while (cin >> names)
	{
		int s, k;
		scanf("%d%d", &s, &k);
		if (k == 0)
		{
			continue;
		}
		int kk = s / k;
		Map[names] -= kk * k;
		for (int i = 1; i <= k; i++)
		{
			string ss;
			cin >> ss;
			Map[ss] += kk;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		cout << Name[i] << " " << Map[Name[i]] << endl;
	}
	return 0;
}
