#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void quick_sort(int a[], int p, int r);
int partition(int a[], int p, int r);
int randomized_partition(int a[], int p, int r);
void randomized_quick_sort(int a[], int p, int r);

int main()
{
	int a[] = {2,8,7,1,3,5,6,4};
	randomized_quick_sort(a, 0, 7);
	for(int i = 0; i <= 7; i ++)
	{
		printf("%d ", a[i]);
	}

	return 0;
}

void quick_sort(int a[], int p, int r)
{
	if(p < r)
	{
		int q = partition(a, p, r);
		quick_sort(a, p, q - 1);
		quick_sort(a, q + 1, r);
	}
}

void randomized_quick_sort(int a[], int p, int r)
{
	if(p < r)
	{
		int q = randomized_partition(a, p, r);
		randomized_quick_sort(a, p, q - 1);
		randomized_quick_sort(a, q + 1, r);
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
