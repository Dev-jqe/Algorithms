//Problem : BZOJ3143 游走
//Author : Jqe
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const int MAXN = 605,MAXM = 400005;
int n,m,a,b,cnt;
int head[MAXN],nxt[MAXM],to[MAXM],frm[MAXM];
int ind[MAXN];
double mp[MAXN][MAXN];
double f[MAXN],g[MAXM];
double res;
void add(int x,int y)
{
	nxt[++cnt] = head[x];
	to[cnt] = y;
	frm[cnt] = x;
	head[x] = cnt;
}
void gauss()
{
	for (int i = 1;i <= n;i++)
	{
		int loc = i;
		for (int o = i + 1;o <= n;o++) if (fabs(mp[o][i]) > fabs(mp[loc][i])) loc = o;
		for (int o = 1;o <= n + 1;o++) swap(mp[loc][o],mp[i][o]);
		for (int j = i + 1;j <= n;j++)
			for (int o = n + 1;o >= i;o--)
				mp[j][o] -= mp[i][o] * mp[j][i] / mp[i][i];
	}
	for (int i = n;i >= 1;i--)
	{
		double x = mp[i][n + 1];
		for (int j = i + 1;j <= n;j++) x -= mp[i][j] * f[j];
		f[i] = x / mp[i][i];
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i = 1;i <= m;i++)
	{
		scanf("%d%d",&a,&b);
		add(a,b);
		add(b,a);
		ind[a]++;
		ind[b]++;
	}
	n--;mp[1][n + 1] = -1.0;
	for (int i = 1;i <= n;i++)
	{
		mp[i][i] = -1.0;
		for (int o = head[i];o;o = nxt[o])
			if (to[o] != n + 1)
				mp[i][to[o]] = 1.0 / ind[to[o]];
	}
	gauss();
	for (int i = 2;i <= cnt;i += 2)
		g[i / 2] = f[frm[i]] / (double)ind[frm[i]] + f[to[i]] / (double)ind[to[i]];
	sort(g + 1,g + m + 1);
	for (int i = m;i >= 1;i--) res += (double) i * g[m - i + 1];
	printf("%.3lf\n",res);
	return 0;
}
