#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int LIS(int* arr, int* L, int n);
void outputLIS(int* arr, int* L, int index, int lis);
int LIS2(int *arr, int *P, int n);
int BiSearch(int *B, int len, int t);
int main()
{
	int a[6] = {5, 6, 7, 1, 2, 8};
	int L[6];
	int lis = LIS(a, L, 6);
	outputLIS(a, L, 5, lis);
	printf("\n");
	int P[6];
//	int b[9] = {2, 1, 5, 3, 6, 4, 8, 9, 7};
	int b[5] = {2, 1, 5, 3, 6};
	int len = LIS2(a, P, 6);
	printf("len: %d", len);
	return 0;
}

int LIS(int* arr, int* L, int n)
{
	int len = 1;
	for(int i = 0; i < n; i++)
	{
		L[i] = 1;
	}
	for(int i = 1; i < n; i++)
	{
		for(int j = i - 1; j >= 0; j--)
		{
			if(arr[j] < arr[i] && L[i] < L[j] + 1)
			{
				L[i] = L[j] + 1;
				if(L[i] > len)
				{
					len = L[i];
				}
			}
		}
	}
	return len;
}

void outputLIS(int* arr, int* L, int index, int lis)
{
	bool is_lis = false;
	if(index < 0 || lis == 0)
	{
		return;
	}
	if(L[index] == lis)
	{
		lis --;
		is_lis = true;
	}
	outputLIS(arr, L, --index, lis);
	if(is_lis)
	{
		printf("%d ", arr[index + 1]);
	}
}

int LIS2(int *arr, int *P, int n)
{
	int B[n + 1];
	int len = 1;
	B[0] = 1;
	B[1] = arr[0];
	for(int i = 1; i < n; i++)
	{
		if(arr[i] > B[len])
		{
			B[++len] = arr[i];
		}else
		{
			int pos = BiSearch(B, len, arr[i]);
			B[pos] = arr[i];
		}
	}
	return len;
}

int BiSearch(int *B, int len, int t)
{
	int low = 1;
	int high = len;
	int mid;
	while(low <= high)
	{
		mid = (low + high) / 2;
		if(t >= B[mid])
		{
			low = mid + 1;		
		}else if(t < B[mid])
		{
			high = mid - 1;
		}
	}
	return low;
}
