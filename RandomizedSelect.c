#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int randomized_select(int a[], int p, int r, int i);
int randomized_partition(int a[], int p, int r);
int partition(int a[], int p, int r);

int main()
{
	int a[] = {-1, 7, 9, 4, 3, 1, 0};
	int ithsmallest = randomized_select(a, 0, 6, 5);
	printf("ithsmallest %d", ithsmallest);
	return 0;
}
int randomized_select(int a[], int p, int r, int i)
{
	if(p == r)
	{
		return a[p];
	}
	int q = randomized_partition(a, p, r);
	int k = q - p + 1;
	if(k == i)
	{
		return a[q];
	}
	if(i < k)
	{
		return randomized_select(a, p, q - 1, i);
	}else
	{
		return randomized_select(a, q + 1, r, i);
	}
}

int randomized_partition(int a[], int p, int r)
{
	srand((unsigned)time(NULL));
	int i = p + rand() % (r - p + 1);
	int tmp = a[i];
	a[i] = a[r];
	a[r] = tmp;
	return partition(a, p, r);
}

int partition(int a[], int p, int r)
{
	if(p == r)
	{
		return p;
	}
	if(p > r)
	{
		return -1;
	}

	int i = p - 1;
	int x = a[r];
	for(int j = p; j < r; j++)
	{
		if(a[j] <= x)
		{
			i ++;
			int tmp = a[i];
			a[i] = a[j];
			a[j] = tmp;
		}
	}
	int tmp = a[i + 1];
	a[i + 1] = a[r];
	a[r] = tmp;

	return i + 1;
}
