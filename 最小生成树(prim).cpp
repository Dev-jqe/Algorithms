//Problem : luguo3366 最小生成树
//Author : Jqe
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
using namespace std;
const int MAXN = 5005,MAXM = 400005;
struct pot
{
	int dis,x;
	pot (int _x = 0,int _dis = 0) :x(_x),dis(_dis) {}
};
bool operator < (const pot x,const pot y)
{
	return x.dis > y.dis;
}
priority_queue <pot> que;
int head[MAXN],dis[MAXN];
int to[MAXM],nxt[MAXM],wei[MAXM];
bool ins[MAXN];
int n,m,cnt;
long long ans;
void add(int x,int y,int len)
{
	nxt[++cnt] = head[x];
	to[cnt] = y;
	head[x] = cnt;
	wei[cnt] = len;
}
void prim()
{
	memset(dis,0x1f,sizeof(dis));
	dis[1] = 0;
	que.push(pot(1,0));
	while (!que.empty())
	{
		pot u = que.top();
		que.pop();
		if (ins[u.x]) continue;
		ans += dis[u.x];
		ins[u.x] = true;
		for (int i = head[u.x];i;i = nxt[i])
		{
			if (wei[i] < dis[to[i]])
			{
				dis[to[i]] = wei[i];
				que.push(pot(to[i],wei[i]));
			}
		}
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i = 1;i <= m;i++)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		add(a,b,c);
		add(b,a,c);
	}
	prim();
	printf("%lld\n",ans);
	return 0;
}

