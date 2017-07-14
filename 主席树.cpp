//Problem : POJ2104 K-th Number
//Author : Jqe
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const int inf = 1000000000,MAXN = 100005;
int n,m,sum;
int vec[100005],root[100005],siz[33*MAXN],ch[33*MAXN][2];
void vec_insert(int pre,int &now,int l,int r,int v)
{
	now = ++sum;
	siz[now] = siz[pre] + 1;
	if (l == r) return;
	ch[now][0] = ch[pre][0];
	ch[now][1] = ch[pre][1];
	int mid = l + r >> 1;
	if (v <= mid) vec_insert(ch[pre][0],ch[now][0],l,mid,v);
	else vec_insert(ch[pre][1],ch[now][1],mid + 1,r,v);
}
int vec_query(int pre,int sub,int l,int r,int k)
{
	if (l == r) return l;
	int mid = l + r >> 1; 
	if (siz[ch[sub][0]] - siz[ch[pre][0]] >= k) return vec_query(ch[pre][0],ch[sub][0],l,mid,k);
	return vec_query(ch[pre][1],ch[sub][1],mid + 1,r,k - siz[ch[sub][0]] + siz[ch[pre][0]]);
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i = 1;i <= n;i++) scanf("%d",&vec[i]);
	for (int i = 1;i <= n;i++) vec_insert(root[i - 1],root[i],-inf,inf,vec[i]);
	for (int i = 1;i <= m;i++)
	{
		int l,r,k;
		scanf("%d%d%d",&l,&r,&k);
		printf("%d\n",vec_query(root[l - 1],root[r],-inf,inf,k));
	}
	return 0;
}
