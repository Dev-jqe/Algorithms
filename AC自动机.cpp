//Problem : HDU2222 Keywords Search
//Author : Jqe
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
using namespace std;
queue <int> que; 
char str[1000005];
int T,n,root,tot;
int ch[500005][30];
int fail[500005],strend[500005];
bool mark[500005]; 
void ac_ist()
{
	int len = strlen(str + 1),u = root;
	for (int i = 1;i <= len;i++)
	{
		if (!ch[u][str[i] - 'a'])
		{
			ch[u][str[i] - 'a'] = ++tot;
		}
		u = ch[u][str[i] - 'a'];
	}
	strend[u]++;
}
void ac_mcn()
{
	for (int i = 0;i < 26;i++) ch[0][i] = 1;
	que.push(root);
	fail[1] = 0;
	while (!que.empty())
	{
		int t = que.front();
		que.pop();
		for (int i = 0;i < 26;i++)
		{
			if (!ch[t][i]) continue;
			int k = fail[t];
			while (!ch[k][i]) k = fail[k];
			fail[ch[t][i]] = ch[k][i];
			que.push(ch[t][i]);
		}
	}
}
void ac_mth()
{
	int ans = 0,len = strlen(str + 1),u = 1;
	for (int i = 1;i <= len;i++)
	{
		int t = str[i] - 'a';
		mark[u] = 1;
		while (!ch[u][t]) u = fail[u];
		u = ch[u][t];
		if (!mark[u])
			for (int j = u;j;j = fail[j])
			{
				ans += strend[j];
				strend[j] = 0; 
			}
	}
	printf("%d\n",ans);
}
void init()
{
	root = 1,tot = 1;
	memset(ch,0,sizeof(ch));
	memset(fail,0,sizeof(fail));
	memset(strend,0,sizeof(strend));
	memset(mark,0,sizeof(mark));
}
int main()
{
	scanf("%d",&T);
	for (int mi = 1;mi <= T;mi++)
	{
		init();
		scanf("%d",&n);
		for (int i = 1;i <= n;i++)
		{
			scanf("%s",str + 1);
			ac_ist();
		}
		ac_mcn();
		scanf("%s",str + 1);
		ac_mth();
	}
	return 0;
}
