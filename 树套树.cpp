//Problem : LYOJ144 陌上花开
//Author : Jqe
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const int MAXN = 200005;
struct pot
{
	int x,y,z;
};
pot sec[MAXN];
int n,p,tot,ou_tot,root;
int ch[289 * MAXN][2],data[289 * MAXN],sum[MAXN],res[MAXN];
int ou_ch[4 * MAXN][2],ou_root[4 * MAXN];
int ans[MAXN];
bool cmp1(pot x,pot y)
{
	if (x.x != y.x) return x.x < y.x;
	if (x.y != y.y) return x.y < y.y;
	return x.z < y.z;
}
void vec_insert(int &k,int l,int r,int loc)
{
	if (k == 0) k = ++tot;
	data[k]++;
	if (l == r) return;
	int mid = l + r >> 1;
	if (loc <= mid) vec_insert(ch[k][0],l,mid,loc);
	if (loc > mid) vec_insert(ch[k][1],mid + 1,r,loc);
}
int vec_query(int k,int l,int r,int x,int y)
{
	if (k == 0) return 0;
	if (x <= l && r <= y) return data[k];
	int mid = l + r >> 1,res = 0;
	if (x <= mid) res += vec_query(ch[k][0],l,mid,x,y);
	if (y > mid) res += vec_query(ch[k][1],mid + 1,r,x,y);
	return res;
}
void tree_insert(int &k,int l,int r,int x)
{
	if (k == 0) k = ++ou_tot;
	vec_insert(ou_root[k],1,p,sec[x].z);
	if (l == r) return;
	int mid = l + r >> 1;
	if (sec[x].y <= mid) tree_insert(ou_ch[k][0],l,mid,x);
	else tree_insert(ou_ch[k][1],mid + 1,r,x);
}
int tree_query(int k,int l,int r,int x)
{
	if (k == 0) return 0;
	if (1 <= l && r <= sec[x].y) return vec_query(ou_root[k],1,p,1,sec[x].z);
	int mid = l + r >> 1,res = 0;
	if (1 <= mid) res += tree_query(ou_ch[k][0],l,mid,x);
	if (sec[x].y > mid) res += tree_query(ou_ch[k][1],mid + 1,r,x);
	return res;
}
bool check(int i,int j)
{
	if (sec[i].x != sec[j].x) return false;
	if (sec[i].y != sec[j].y) return false;
	if (sec[i].z != sec[j].z) return false;
	return true;
}
inline int readln()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int main()
{
	scanf("%d%d",&n,&p);
	for (int i = 1;i <= n;i++)
	{
		sec[i].x = readln();
		sec[i].y = readln();
		sec[i].z = readln();
	}
	sort(sec + 1,sec + n + 1,cmp1);
	int l = 1;
	for (int i = 1;i <= n;i++)
	{
		ans[i] = tree_query(root,1,p,i);
		if (i >= 2 && !check(i - 1,i)) l = i;
		sum[l]++;sum[i]--;
		tree_insert(root,1,p,i);
	}
	int tot = 0;
	for (int i = 1;i <= n;i++)
	{
		tot += sum[i];
		ans[i] += tot;
		res[ans[i]]++;
	}
	for (int i = 0;i <= n - 1;i++) printf("%d\n",res[i]);
	return 0;
}
