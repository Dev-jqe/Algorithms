//Problem : codeves1080 线段数联系
//Author : Jqe
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
int n,m;
long long sec[100005];
int lowbit(int x) {return x & -x;}
void add(int x,int v)
{
	for (;x <= n;x += lowbit(x)) sec[x] += v;
}
long long sum(int x)
{
	long long res = 0;
	for (;x;x -= lowbit(x)) res += sec[x];
	return res;
}
long long query(int l,int r)
{
	return sum(r) - sum(l - 1);
}
int main()
{
	scanf("%d",&n);
	for (int i = 1;i <= n;i++)
	{
		int tmp;
		scanf("%d",&tmp);
		add(i,tmp);
	}
	scanf("%d",&m);
	for (int i = 1;i <= m;i++)
	{
		int opt,a,b;
		scanf("%d%d%d",&opt,&a,&b);
		if (opt == 1) add(a,b);
		else printf("%lld\n",query(a,b));
	}
}
