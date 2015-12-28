#include <stdlib.h>
#include <stdio.h>

void Permutation(int a[], int n, int start);
void swap(int* a, int* b);
int main()
{
	int a[3] = {1, 2, 3};
	Permutation(a, 3, 0);
	return 0;
}

void Permutation(int a[], int n, int start)
{
	if(start >= n - 1)
	{
		for(int i = 0; i < n; i++)
		{
			printf("%d ", a[i]);
		}
		printf("\n");
	}else
	{
		for(int i = start; i < n; i++)
		{
			swap(&a[start], &a[i]);
			Permutation(a, n, start + 1);
			swap(&a[start], &a[i]);
		}
	}
}

void swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
