#include <stdlib.h>
#include <stdio.h>

void InsertSort(int n, int a[]);
int main()
{
	int a[8] = {8, 7, 6, 5, 4, 3, 2, 1};
	InsertSort(8, a);
	for(int i = 0; i < 8; i++)
	{
		printf("%d ", a[i]);
	}
	return 0;
}

void InsertSort(int n, int a[])
{
	for(int i = 1; i < n; i++)
	{
		int key = a[i];
		int k = i - 1;
		while(k >= 0 && a[k] > key) 
		{
			a[k + 1] = a[k];
			k--;
		}
		a[k + 1] = key;
	}
}
