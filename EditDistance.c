#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define COPY 'c'
#define DELETE 'd'
#define INSERT 'i'
#define REPLACE 'r'
#define TWIDDLE 't'
#define KILL 'k'

int EditDistance(char *x, char *y, int m, int n, int c[m + 1][n + 1], char op[m + 1][n + 1]);
void PrintOpSequence(int m, int n, char op[m + 1][n + 1], int i, int j, int kill_pos);

int main()
{
	char *x = "algorithm";
	char *y = "altruistic";
	int c[10][11];
	char op[10][11];
	int kill_pos = EditDistance(x, y, 9, 10, c, op);
	PrintOpSequence(9, 10, op, 9, 10, kill_pos);
	printf("\nEdit Distance is: %d", c[9][10]);
	return 0;
}

int EditDistance(char *x, char *y, int m, int n, int c[m + 1][n + 1], char op[m + 1][n + 1])
{
	printf("Please input the cost of copy, delete, insert, replace, twiddle, kill repectively: ");
	int c_copy;
	int c_delete;
	int c_insert;
	int c_replace;
	int c_twiddle;
	int c_kill;

	scanf("%d", &c_copy);
	scanf("%d", &c_delete);
	scanf("%d", &c_insert);
	scanf("%d", &c_replace);
	scanf("%d", &c_twiddle);
	scanf("%d", &c_kill);
	
	for(int i = 0; i <= m; i ++)
	{
		c[i][0] = i * c_delete;
		op[i][0] = DELETE;
	}
	for(int j = 0; j <= n; j ++)
	{
		c[0][j] = j * c_insert;
		op[0][j] = INSERT;
	}
	for(int i = 1; i <= m; i++)
	{
		for(int j = 1; j<= n; j++)
		{
			c[i][j] = INT_MAX;
			int cost_replace = c[i - 1][j - 1] + c_replace;
			int cost_twiddle = c[i - 2][j - 2] + c_twiddle;
			int cost_delete = c[i - 1][j] + c_delete;
			int cost_insert = c[i][j - 1] + c_insert;

			if(x[i - 1] == y[j - 1])
			{
				c[i][j] = c[i - 1][j - 1] + c_copy;
				op[i][j] = COPY;
			}
			if(x[i - 1] != y[j - 1] && c[i][j] > cost_replace)
			{
				c[i][j] = cost_replace;
				op[i][j] = REPLACE;
			}
			if(i >= 2 && j >= 2 && x[i] == y[j - 1] && x[i - 1] == y[j] && c[i][j] > cost_twiddle)
			{
				c[i][j] = cost_twiddle;
				op[i][j] = TWIDDLE;
			}
			if(c[i][j] > cost_delete)
			{
				c[i][j] = cost_delete;
				op[i][j] = DELETE;
			}
			if(c[i][j] > cost_insert)
			{
				c[i][j] = cost_insert;
				op[i][j] = INSERT;
			}
		}
	}
	int kill_pos;
	c[m][n] = INT_MAX;
	for(int i = 0; i <= m; i ++)
	{
		int cost = c[i][n] + c_kill;
		if(cost < c[m][n])
		{
			c[m][n] = cost;
			kill_pos = i;
		}
	}
	op[m][n] = KILL;
	
	return kill_pos;
}

void PrintOpSequence(int m, int n, char op[m + 1][n + 1], int i, int j, int kill_pos)
{
	if(i == 0 && j == 0)
	{
		return;
	}
	if(op[i][j] == COPY || op[i][j] == REPLACE)
	{
		PrintOpSequence(m, n, op, i - 1, j - 1, kill_pos);
	}
	if(op[i][j] == TWIDDLE)
	{
		PrintOpSequence(m, n, op, i - 2, j - 2, kill_pos);
	}
	if(op[i][j] == DELETE)
	{
		PrintOpSequence(m, n, op, i - 1, j, kill_pos);
	}
	if(op[i][j] == INSERT)
	{
		PrintOpSequence(m, n, op, i, j - 1, kill_pos);
	}
	if(op[i][j] == KILL)
	{
		PrintOpSequence(m, n, op, kill_pos, j, kill_pos);
	}
	switch(op[i][j])
	{
		printf("%c ", op[i][j]);
		case COPY:
			printf("copy ");
			break;
		case TWIDDLE:
			printf("twiddle ");
			break;
		case DELETE:
			printf("delete ");
			break;
		case REPLACE:
			printf("replace ");
			break;
		case INSERT:
			printf("insert ");
			break;
		case KILL:
			printf("kill");
	}
	printf("\n");
}
