#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

void RabinKarpMatcher(int T[], int n, int P[], int m, int q, int d);
int main()
{
	int T[19] = {2, 3, 5, 9, 0, 2, 3, 1, 4, 1, 5, 2, 6, 7, 3, 9, 9, 2, 1};
	int P[5] = {3, 1, 4, 1, 5};
	RabinKarpMatcher(T, 19, P, 5, 13, 10);

	return 0;
}

/**
 * T[0...n-1]: 输入集
 * P[0...m-1]: 匹配集
 * q: 模数
 * d: 进制数
 */
void RabinKarpMatcher(int T[], int n, int P[], int m, int q, int d)
{
	if(n < m)
	{
		return;
	}
	int t[n - m + 1];
	t[0] = 0;
	int p = 0;
	int h = (int)pow((float)d, (float)m - 1) % q;

	for(int i = 0; i < m; i++)
	{
		p = (d * p + P[i]) % q;
		t[0] = (d * t[0] + T[i]) % q; 
	}

	/* 计算t[s](s: 0...n-m) 与p是否相等*/
	for(int s = 0; s <= n - m; s++)
	{
		if(p == t[s])
		{
			bool flag = true;
			/* 检查T[s..s+m-1] 与 P[0...m-1] 是否相等 */
			for(int i = 0; i < m; i++)
			{
				if(P[i] != T[i + s])
				{
					flag = false;
					break;
				}
			}
			if(flag)
			{
				printf("Pattern occurs with shift %d\n", s);
			}
		}
		if(s < n - m)
		{
			t[s + 1] = (d * (t[s] - T[s] * h) + T[s + m]) % q;
			/* 防止取模后数值小于0 */
			while(t[s + 1] < 0)
			{
				t[s + 1] += q;
			}
		}
	}
}
