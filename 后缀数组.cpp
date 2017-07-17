//Problem : UOJ35 后缀排序
//Author : Jqe 
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const int MAXN = 100005;
char str[MAXN];
int c[MAXN],SA[MAXN],t1[MAXN],t2[MAXN],R[MAXN],HT[MAXN],rank[MAXN];
int n,m;

void SA_init()
{
	int p,*x = t1,*y = t2;
	for (int i = 0;i < m;i++) c[i] = 0;
	for (int i = 0;i < n;i++) c[x[i] = R[i]]++;
	for (int i = 0;i < m;i++) c[i] += c[i - 1];
	for (int i = n - 1;i >= 0;i--) SA[--c[x[i]]] = i;
	
	for (int k = 1;k <= n;k <<= 1)
	{
		p = 0;
		for (int i = n - k;i < n;i++) y[p++] = i;
		for (int i = 0;i < n;i++) if (SA[i] >= k) y[p++] = SA[i] - k;
		//
		for (int i = 0;i < m;i++) c[i] = 0;
		for (int i = 0;i < n;i++) c[x[y[i]]]++;
		for (int i = 1;i < m;i++) c[i] += c[i - 1];
		for (int i = n - 1;i >= 0;i--) SA[--c[x[y[i]]]] = y[i];
		//
		swap(x,y);
		p = 1;
		x[SA[0]] = 0;
		for (int i = 1;i < n;i++) x[SA[i]] = (y[SA[i]] == y[SA[i - 1]] && y[SA[i] + k] == y[SA[i - 1] + k] ? p - 1: p++);
		if (p >= n) break;
		m = p; 
	}
}
int check(int a,int b)
{
	int ans = 0;
	while (R[a++] == R[b++]) ans++;
	return ans;
}
void HT_init()
{
	for (int i = 0;i < n;i++) rank[SA[i]] = i;
	n--;
	int cur = 0;
	for (int i = 0;i < n;i++)
	{
		if (rank[i] == n) continue;
		if (cur) cur--;
		HT[rank[i]] = cur = cur + check(i + cur,SA[rank[i] + 1] + cur);
	}
}
int main()
{
	scanf("%s",str);
	n = strlen(str),m = 30;
	for (int i = 0;i < n;i++) R[i] = str[i] - 'a' + 2;
	R[n] = 0;
	n++;
	SA_init();
	HT_init();
	for (int i = 1;i <= n;i++) printf("%d ",SA[i] + 1);
	printf("\n");
	for (int i = 1;i < n;i++) printf("%d ",HT[i]); 
	return 0;
}
