#include <stdlib.h>
#include <stdio.h>

void LCSLength(char *x, int n, char *y, int m, char c[n + 1][m + 1]);
void PrintLCS(char *x, int n, int m, char c[n + 1][m + 1], int i, int j);

int main()
{
	char x[7] = {'A', 'B', 'C', 'B', 'D', 'A', 'B'};
	char y[6] = {'B', 'D', 'C', 'A', 'B', 'A'};
	char c[8][7];
	LCSLength(x, 7, y, 6, c);
	PrintLCS(x, 7, 6, c, 8, 7);
	return 0;
}
void LCSLength(char *x, int n, char *y, int m, char c[n + 1][m + 1])
{
	for(int i = 0; i <= n; i++)
	{
		c[i][0] = 0;
	}
	for(int j = 1; j <= m; j++)
	{
		c[0][j] = 0;
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			if(x[i - 1] == y[j - 1])
			{
				c[i][j] = c[i - 1][j - 1] + 1;
			}else if(c[i - 1][j] > c[i][j - 1])
			{
				c[i][j] = c[i - 1][j];
			}else
			{
				c[i][j] = c[i][j - 1];
			}
		}
	}
}

void PrintLCS(char *x, int n, int m, char c[n + 1][m + 1], int i, int j)
{
	if(i < 0 || j < 0)
	{
		return;
	}
	if(c[i][j] == c[i - 1][j])
	{
		PrintLCS(x, n, m, c, i - 1, j);
	}else if(c[i][j] == c[i][j - 1])
	{
		PrintLCS(x, n, m, c, i, j - 1);
	}else
	{
		PrintLCS(x, n, m, c, i - 1, j - 1);
		printf("%c ", x[i - 1]);
	}
}
