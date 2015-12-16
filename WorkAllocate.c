#include <stdlib.h>
#include <stdio.h>

int n;
int tmpc = 0;
int bestc = 10000;
int x[10];
int best[10];

void WorkAllocate(int i, int n, int c[n][n]);
void swap(int *a, int *b);
int main()
{
	n = 5;
	int c[5][5] = {{50,43,1,58,60}, 
		{87,22,5,62,71}, 
	{62,98,97,27,38}, 
	{56,57,96,73,71}, 
	{92,36,43,27,95}};
	for(int i = 0; i < n; i++)
	{
		x[i] = i;
	}
	WorkAllocate(0, n, c);
	printf("bestc: %d\n", bestc);
	for(int i = 0; i < n; i++)
	{
		printf("job %d allocate worker %d\n", i + 1, best[i] + 1);
	}
	return 0;
}

void WorkAllocate(int i, int n, int c[n][n])
{
	if(i >= n)
	{
		if(bestc > tmpc)
		{
			bestc = tmpc;
			printf("bestc: %d\n", bestc);
			for(int k = 0; k < n; k++)
			{
				best[k] = x[k];
			}
		}
	}else
	{
		for(int j = i; j < n; j++)
		{
			swap(&x[j], &x[i]);
			tmpc += c[i][x[i]];
			WorkAllocate(i + 1, n, c);
			tmpc -= c[i][x[i]];
			swap(&x[j], &x[i]);
		}
	}
}

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
