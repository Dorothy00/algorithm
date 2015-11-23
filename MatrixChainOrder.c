#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void MatrixChainOrder(int p[], int len, int m[len - 1][len - 1], int s[len - 1][len - 1]);
void PrintOptimalParens(int n, int s[n][n],  int i, int j);
int main()
{
	int len = 7;
	int n = len - 1;
	int p[7] = {5, 10, 3, 12, 5, 50, 6};
	int m[7][7];
	int s[7][7];
	MatrixChainOrder(p, len, m, s);
	for(int i = 0; i <= n; i++)
	{
		for(int j = 0; j <= n; j++)
		{
			printf("%d ", s[i][j]);
		}
		printf("\n");
	}
	PrintOptimalParens(len, s, 1, 6);

	return 0;
}

void MatrixChainOrder(int p[], int len, int m[len][len], int s[len][len])
{
	int n = len - 1;
	for(int i = 0; i <= n; i++)
	{
		m[i][i] = 0;
	}
	for(int l = 2; l <= n; l++)
	{
		for(int i = 1; i <= n - l + 1; i++)
		{
			int j = i + l - 1;
			m[i][j] = INT_MAX;
			for(int k = i; k <= j - 1; k++)
			{
				int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
				if(q < m[i][j])
				{
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
	}
}

void PrintOptimalParens(int n, int s[n][n],  int i, int j)
{
	if(i == j)
	{
		printf("A%d", i);
	}else
	{
		printf("(");
		PrintOptimalParens(n, s, i, s[i][j]);
		PrintOptimalParens(n, s, s[i][j] + 1, j);
		printf(")");
	}
}
