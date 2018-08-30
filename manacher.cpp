//luogu P3805
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 3 * 1e7;
char s[MAXN],t[MAXN];
int res[MAXN];
int len,mid,maxr,ans;
int main()
{
	scanf("%s",s + 1);
	len = strlen(s + 1),mid = 1,maxr = 1,ans = 1;
	t[0] = '@'; t[1] = '*';
	for (int i = 1;i <= len;i++) t[i * 2] = s[i],t[i * 2 + 1] = '*';
	len = len * 2 + 1;
	t[len + 1] = 0; 
	res[1] = 0;
	for (int i = 2;i <= len;i++) 
	{
		if (i < maxr)
		{
			int j = mid * 2 - i;
			res[i] = min(res[j],maxr - i);
		}else res[i] = 0;
		while (t[i + res[i] + 1] == t[i - res[i] - 1]) res[i]++;
		if (i + res[i] > maxr)
		{
			maxr = i + res[i];
			mid = i;
		}
		ans = max(ans,res[i]);
	}
	printf("%d\n",ans);
	return 0;
}
