#include <stdio.h>

void count_sort(int a[], int b[], int length, int max);

int main()
{
	int a[11] = {6,0,2,0,1,3,4,6,1,3,2};	
	int b[11] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	count_sort(a, b, 11, 6);
	for(int i = 0; i < 11; i++)
	{
		printf("%d ", b[i]);
	}

	return 0;
}

void count_sort(int a[], int b[], int length, int max)
{
	int c[max + 1];
	for(int i = 0; i <= max; i++)
	{
		c[i] = 0;
	}
	for(int i = 0; i < length; i++)
	{
		c[a[i]] ++;
	}
	for(int j = 1; j <= max; j++)
	{
		c[j] += c[j - 1];
	}
	for(int k = length - 1; k >= 0; k--)
	{
		b[c[a[k]] - 1] = a[k];
		c[a[k]] --;
	}
}
