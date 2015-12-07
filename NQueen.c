#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

void NQueen(int x[], int n, int k);
bool PlaceTest(int x[], int n, int k);

int main()
{
	int x[4];
	NQueen(x, 4, 1);
	return 0;
}

/*n 皇后问题
 */
void NQueen(int x[], int n, int k)
{
	if(k > n)
	{
		for(int i = 0; i < n; i++)
		{
			printf("%d ", x[i]);
		}
		printf("\n");
	}else
	{
		for(int i = 1; i <= n; i++)
		{
			x[k - 1] =  i;
			if(PlaceTest(x, n, k))
			{
				NQueen(x, n, k + 1);
			}
		}
	}
}

bool PlaceTest(int x[], int n, int k)
{
	for(int i = 1; i < k; i ++)
	{
		if(x[i - 1] == x[k - 1] || abs(x[i - 1] - x[k - 1]) == abs(i - k))
		{
			return false;
		}
	}
	return true;
}
