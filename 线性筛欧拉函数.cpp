//Author : Jqe
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
vector <int> que;
bool vis[100005];
int phi[100005];
void getphi(int n)
{
	phi[1] = 1;
	for (int i = 2;i <= n;i++)
	{
		if (!vis[i]) 
		{
			phi[i] = i - 1;
			que.push_back(i);
		}
		for (int o = 0;o <= que.size() - 1;o++)
		{
			if (i * que[o] > n) break;
			vis[i * que[o]] = 1;
			if (i % que[o] == 0)
			{
				phi[i * que[o]] = phi[i] * que[o];
				break;
			}else phi[i * que[o]] = phi[i] * phi[que[o]];
		}
	}
}
int main()
{
	getphi(100000);
	for (int i = 1;i <= 100;i++) printf("%d ",phi[i]);
	return 0;
}
