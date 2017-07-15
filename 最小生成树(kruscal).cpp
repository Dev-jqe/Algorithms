//Problem : luogu3366 最小生成树
//Author : Jqe
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
struct vec
{
	int x,y,len;
};
vec sec[200005];
int fa[100005],siz[100005];
int n,m;
long long ans;
int getfa(int x)
{
	if (fa[x] == x) return x;
	return fa[x] = getfa(fa[x]);
}
void merge(int x,int y)
{
	int s1 = getfa(x),s2 = getfa(y);
	if (s1 == s2) return;
	if (siz[s1] < siz[s2])
	{
		fa[s1] = s2;
		siz[s2] += siz[s1];
	}else
	{
		fa[s2] = s1;
		siz[s1] += siz[s2];
	}
}
bool cmp(vec x,vec y)
{
	return x.len < y.len;
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i = 1;i <= n;i++) fa[i] = i,siz[i] = 1;
	for (int i = 1;i <= m;i++)
		scanf("%d%d%d",&sec[i].x,&sec[i].y,&sec[i].len);
	sort(sec + 1,sec + m + 1,cmp);
	for (int i = 1;i <= m;i++)
		if (getfa(sec[i].x) != getfa(sec[i].y))
		{
			ans += sec[i].len;
			merge(sec[i].x,sec[i].y);
		}
	printf("%lld\n",ans);
}
