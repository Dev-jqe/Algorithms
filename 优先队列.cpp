//Problem : codevs1063 合并果子
//Author : Jqe
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
int n,tot;
long long data[40005];
long long ans;
void insert(long long x)
{
	data[++tot] = x;
	int t = tot;
	while (t != 1 && data[t] < data[t >> 1])
	{
		swap(data[t],data[t >> 1]);
		t = t >> 1;
	}
}
void pop()
{
	data[1] = data[tot];
	data[tot--] = 0;
	int t = 1;
	while ((data[t << 1] && data[t] > data[t << 1]) || (data[t << 1 | 1] && data[t] > data[t << 1 | 1]))
	{
		if (data[t << 1 | 1] && data[t << 1] > data[t << 1 | 1])
		{
			swap(data[t],data[t << 1 | 1]);
			t = t << 1 | 1;
		}else
		{
			swap(data[t],data[t << 1]);
			t = t << 1;
		}
	}
}
long long top()
{
	return data[1];
}
int main()
{
	scanf("%d",&n);
	for (int i = 1;i <= n;i++) 
	{
		long long tmp;
		scanf("%lld",&tmp);
		insert(tmp);
	}
	for (int i = 1;i <= n - 1;i++)
	{
		long long t[2];
		t[0] = top();
		pop();
		t[1] = top();
		pop();
		insert(t[0] + t[1]);
		ans += t[0] + t[1];
	}
	printf("%lld\n",ans);
	return 0;
}
