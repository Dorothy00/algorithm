#include <stdio.h>
#include <stdlib.h>

void Backtrack(int x[], int n, int k);
void swap(int* a, int* b);

int main()
{
	int x[3] = {1, 2, 3};
	Backtrack(x, 3, 1);
	return 0;
}

void Backtrack(int x[], int n, int k)
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
		for(int i = k - 1; i < n; i++)
		{
			swap(&x[k - 1], &x[i]);	
			Backtrack(x, n, k + 1);
			swap(&x[k - 1], &x[i]);
		}
	}
}

void swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
