#include <stdlib.h>
#include <stdio.h>

void MergeSort(int a[], int p, int r);
void Merge(int a[], int p, int q, int r);

int main()
{
	int a[8] = {8, 7, 6, 5, 4, 3, 2, 1};
	MergeSort(a, 0, 7);
	for(int i = 0; i < 8; i++)
	{
		printf("%d ", a[i]);
	}
	return 0;
}

void MergeSort(int a[], int p, int r)
{
	if(p < r)
	{
		int q = (p + r) / 2;
		MergeSort(a, p, q);
		MergeSort(a, q + 1, r);
		Merge(a, p, q, r);
	}
}

void Merge(int a[], int p, int q, int r)
{
	int n1 = q - p + 1;
	int n2 = r - q;
	int left[n1];
	int right[n2];
	for(int i = 0; i < n1; i++)
		left[i] = a[p + i];
	for(int j = 0; j < n2; j++)
		right[j] = a[q + j + 1];

	int i = 0, j = 0;
	while(i < n1 && j < n2)
	{
		if(left[i] < right[j])
		{
			a[p + i + j] = left[i];
			i ++;
		}else
		{
			a[p + i + j] = right[j];
			j ++;
		}
	}

	while(i < n1)
	{
		a[p + i + j] = left[i];
		i ++;
	}
	while(j < n2)
	{
		a[p + i + j] = right[j];
		j ++;
	}
}
