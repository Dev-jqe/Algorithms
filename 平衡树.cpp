//Problem : BZOJ3224 ÆÕÍ¨Æ½ºâÊ÷ 
//Author : Jqe
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const int MAXN = 100005;
int ch[MAXN][2],data[MAXN],fa[MAXN],siz[MAXN],cnt[MAXN];
int root,sum,n;
int which(int x) {return ch[fa[x]][0] == x ? 0 : 1;}
void updata(int x) {siz[x] = siz[ch[x][0]] + siz[ch[x][1]] + cnt[x];}
void rotate(int x)
{
	int p = fa[x];
	int q = fa[p];
	int dir1 = which(x);
	int dir2 = which(p);
	int t = ch[x][dir1 ^ 1];
	
	fa[p] = x;
	fa[x] = q;
	fa[t] = p;
	
	if (q) ch[q][dir2] = x;
	ch[x][dir1 ^ 1] = p;
	ch[p][dir1] = t;
	
	updata(p);
	updata(x);
}
void splay(int x,int tar)
{
	while (fa[x] != tar)
	{
		if (fa[fa[x]] != tar)
		{
			if (which(fa[x]) == which(x)) rotate(fa[x]);
			else rotate(x); 
		}
		rotate(x);
	}
	if (tar == 0) root = x;
}
void insert(int x)
{
	int u = root,v = 0,dir;
	while (u)
	{
		siz[v = u]++; 
		if (x == data[u])
		{
			cnt[u]++;
			splay(u,0);
			return;
		}
		if (x < data[u])
		{
			u = ch[u][0];
			dir = 0;
		}else
		{
			u = ch[u][1];
			dir = 1;
		}
	}
	sum++;
	data[sum] = x;
	if (v) ch[v][dir] = sum;
	fa[sum] = v;
	siz[sum] = cnt[sum] = 1;
	splay(sum,0);
}
int find (int x)
{
	int u = root;
	while (u)
	{
		if (x == data[u]) 
		{
			splay(u,0);
			return u;
		}
		if (x < data[u]) u = ch[u][0];
		else u = ch[u][1];
	}
	return -1;
}
int find_max(int t)
{
	while (ch[t][1]) t = ch[t][1];
	splay(t,0);
	return t;
}
int find_min(int t)
{
	while (ch[t][0]) t = ch[t][0];
	splay(t,0);
	return t; 
}
void join(int x,int y)
{
	int t = find_max(x);
	splay(t,0);
	fa[y] = t;
	ch[t][1] = y;
	updata(t);
}
void erase(int x)
{
	int t = find(x);
	if (t <= -1) return;
	if (cnt[t] >= 2)
	{
		cnt[t]--;
		siz[t]--;
		return;
	}
	if (siz[t] == 1)
	{
		root = 0;
		return;
	}
	if (!ch[t][0] || !ch[t][1])
	{
		root = ch[t][0] + ch[t][1];
		fa[root] = 0;
		return;
	}
	fa[ch[t][0]] = fa[ch[t][1]] = 0;
	join(ch[t][0],ch[t][1]);
}
int check_rank(int x)
{
	int u = root,res = 0;
	while (u)
	{
		if (x == data[u])
		{
			return res + siz[ch[u][0]] + 1;
		}
		if (x < data[u])
		{
			u = ch[u][0];
		}
		else 
		{
			res += siz[ch[u][0]] + cnt[u];
			u = ch[u][1];
		}
	}
	return -1;
}
int check_numb(int x)
{
	if (x >= siz[root] + 1) return -1;
	int u = root;
	while (u)
	{
		if (siz[ch[u][0]] + 1 <= x && x <= siz[ch[u][0]] + cnt[u])
		{	
			splay(u,0);
			return data[u];
		}
		if (x < siz[ch[u][0]] + cnt[u])
		{
			u = ch[u][0];
		}else
		{
			x -= siz[ch[u][0]] + cnt[u];
			u = ch[u][1];
		}
	}
}
int check_pre(int x)
{
	int u = root,res = 0;
	while (u)
	{
		if (data[u] >= x) u = ch[u][0];else
		{
			res = data[u];
			u = ch[u][1];
		}
	}
	return res;
}
int check_sub(int x)
{
	int u = root,res = 0;
	while (u)
	{
		if (data[u] <= x) u = ch[u][1];else
		{
			res = data[u];
			u = ch[u][0];
		}
	}
	return res;
}
int main()
{
	scanf("%d",&n);
	for (int i = 1;i <= n;i++)
	{
		int opt,x;
		scanf("%d",&opt);
		if (opt == 1)
		{
			scanf("%d",&x);
			insert(x);	
		}else
		if (opt == 2)
		{
			scanf("%d",&x);
			erase(x); 
		}else
		if (opt == 3)
		{
			scanf("%d",&x);
			printf("%d\n",check_rank(x));
		}else
		if (opt == 4)
		{
			scanf("%d",&x);
			printf("%d\n",check_numb(x));	
		}else
		if (opt == 5)
		{
			scanf("%d",&x);
			printf("%d\n",check_pre(x));
		}else
		if (opt == 6)
		{
			scanf("%d",&x);
			printf("%d\n",check_sub(x)); 
		}
	}
	return 0;
}
