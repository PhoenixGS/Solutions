#include <cstdio>
#include <cstring>
#include <map>
#include <iostream>
#include <string>

int ch[100000][60];
int x[100000];
std::map<std::string, int> Map;
int ans;
int knum;
int n;
int last;

void add(int k, int t)
{
	if (t == 0)
	{
		return;
	}
	if (! ch[k][x[t]])
	{
		knum++;
		ch[k][x[t]] = knum;
		ans++;
	}
	add(ch[k][x[t]], t - 1);
}

int main()
{
    Map["AC"] = 0;
	Map["2C"] = 1;
	Map["3C"] = 2; Map["4C"] = 3;  
    Map["5C"] = 4;
	Map["6C"] = 5;
	Map["7C"] = 6;
	Map["8C"] = 7;  
    Map["9C"] = 8;
	Map["10C"] = 9;
	Map["JC"] = 10;
	Map["QC"] = 11;  
    Map["KC"] = 12;
	Map["AD"] = 13;
	Map["2D"] = 14;
	Map["3D"] = 15;  
    Map["4D"] = 16;
	Map["5D"] = 17;
	Map["6D"] = 18;
	Map["7D"] = 19;  
    Map["8D"] = 20;
	Map["9D"] = 21;
	Map["10D"] = 22;
	Map["JD"] = 23;  
    Map["QD"] = 24;
	Map["KD"] = 25;
	Map["AH"] = 26;
	Map["2H"] = 27;  
    Map["3H"] = 28;
	Map["4H"] = 29;
	Map["5H"] = 30;
	Map["6H"] = 31;  
    Map["7H"] = 32;
	Map["8H"] = 33;
	Map["9H"] = 34;
	Map["10H"] = 35;  
    Map["JH"] = 36;
	Map["QH"] = 37;
	Map["KH"] = 38;
	Map["AS"] = 39;  
    Map["2S"] = 40;
	Map["3S"] = 41;
	Map["4S"] = 42;
	Map["5S"] = 43;  
    Map["6S"] = 44;
	Map["7S"] = 45;
	Map["8S"] = 46;
	Map["9S"] = 47;  
    Map["10S"] = 48;
	Map["JS"] = 49;
	Map["QS"] = 50;
	Map["KS"] = 51; 	
	while (scanf("%d", &n) == 1 && n)
	{
		knum = 0;
		memset(ch, 0, sizeof(ch));
		ans = 0;
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &last);
			for (int j = 1; j <= last; j++)
			{
				std::string st;
				std::cin >> st;
				x[j] = Map[st];
			}
			add(0, last);
		}
		printf("%d\n", ans);
	}
	return 0;
}
