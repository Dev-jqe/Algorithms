//Problem : BZOJ1036 树的统计
//Author : Jqe
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const int MAXN = 30005;
int siz[MAXN],son[MAXN],fa[MAXN],top[MAXN],pos[MAXN],idx[MAXN],que[MAXN],dep[MAXN];
int head[MAXN],to[2 * MAXN],nxt[2 * MAXN];
int data[4 * MAXN][2];
int sec[MAXN];
int cnt,sum,n,q;
void add(int x,int y)
{
	nxt[++cnt] = head[x];
	to[cnt] = y;
	head[x] = cnt;
}
void build(int k,int l,int r)
{
	if (l == r)
	{
		data[k][0] = data[k][1] = sec[idx[l]];
		return;
	}
	int mid = l + r >> 1;
	build(k << 1,l,mid);
	build(k << 1 | 1,mid + 1,r);
	data[k][0] = max(data[k << 1][0],data[k << 1 | 1][0]);
	data[k][1] = data[k << 1][1] + data[k << 1 | 1][1];
}
void vec_change(int k,int l,int r,int x,int v)
{
	if (l == r)
	{
		data[k][0] = data[k][1] = v;
		return;
	}
	int mid = l + r >> 1;
	if (x <= mid) vec_change(k << 1,l,mid,x,v);
	else vec_change(k << 1 | 1,mid + 1,r,x,v);
	data[k][0] = max(data[k << 1][0],data[k << 1 | 1][0]);
	data[k][1] = data[k << 1][1] + data[k << 1 | 1][1];
}
int vec_query(int k,int l,int r,int x,int y,int opt)
{
	if (x <= l && r <= y) return data[k][opt];
	int mid = l + r >> 1,res = 0;
	if (opt == 0)
	{
		res = -30000;
		if (x <= mid) res = max(res,vec_query(k << 1,l,mid,x,y,opt));
		if (y > mid) res = max(res,vec_query(k << 1 | 1,mid + 1,r,x,y,opt));
	}else if (opt == 1)
	{
		if (x <= mid) res += vec_query(k << 1,l,mid,x,y,opt);
		if (y > mid) res += vec_query(k << 1 | 1,mid + 1,r,x,y,opt);
	}
	return res;
}
void init()
{
	int qt = 0;
	que[++qt] = 1;
	for (int i = 1;i <= qt;i++)
	{
		int u = que[i];
		siz[u] = 1;
		for (int o = head[u];o;o = nxt[o])
		{
			if (to[o] == fa[u]) continue;
			que[++qt] = to[o];
			fa[to[o]] = u;
			dep[to[o]] = dep[u] + 1;
		}
	}
	for (int i = qt;i >= 1;i--)
	{
		int u = que[i];
		if (siz[u] > siz[son[fa[u]]]) son[fa[u]] = u;
		siz[fa[u]] += siz[u];
	}
	for (int i = 1;i <= qt;i++)
	{
		int u = que[i];
		if (top[u]) continue;
		int t = u;
		while (t)
		{
			top[t] = u;
			idx[pos[t] = ++sum] = t;
			t = son[t];
		}
	}
	build(1,1,qt);
}
int tree_query(int a,int b,int opt)
{
	int res;
	if (opt == 0) res = -30000;else res = 0;
	while (top[a] != top[b])
	{
		if (dep[top[a]] < dep[top[b]]) swap(a,b);
		if (opt == 0) res = max(res,vec_query(1,1,n,pos[top[a]],pos[a],opt));
		else res += vec_query(1,1,n,pos[top[a]],pos[a],opt);
		a = fa[top[a]];
	}
	if (dep[a] > dep[b]) swap(a,b);
	if (opt == 0)
	{
		res = max(res,vec_query(1,1,n,pos[a],pos[b],opt));
	}else if (opt == 1)
	{	
		res += vec_query(1,1,n,pos[a],pos[b],opt);
	}
	return res;
}
int main()
{
	int a,b;
	scanf("%d",&n);
	for (int i = 1;i <= n - 1;i++)
	{
		scanf("%d%d",&a,&b);
		add(a,b);
		add(b,a);
	}
	for (int i = 1;i <= n;i++) scanf("%d",&sec[i]);
	init();
	char opt[20];
	scanf("%d",&q);
	for (int i = 1;i <= q;i++)
	{
		scanf("%s",opt);
		if (opt[1] == 'H')
		{
			scanf("%d%d",&a,&b);
			vec_change(1,1,n,pos[a],b);
		}else
		if (opt[1] == 'M')
		{
			scanf("%d%d",&a,&b);
			printf("%d\n",tree_query(a,b,0));
		}else
		if (opt[1] == 'S')
		{
			scanf("%d%d",&a,&b);
			printf("%d\n",tree_query(a,b,1));
		}
	}
	return 0;
}
