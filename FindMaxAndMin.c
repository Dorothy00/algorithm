#include <stdio.h>

void find_max_and_min(int a[], int length, int* max, int* min);
// do test
int main()
{
	int a[] = {0, 8, 10, 0, 9, 2, -1, 5};
	int* max;
	int* min;
	find_max_and_min(a, 8, max, min);
	printf("max %d\n", *max);
	printf("min %d\n", *min);

	return 0;
}

void find_max_and_min(int a[], int length, int* max, int* min)
{
	int maxmum;
	int minmum;
	int i;
	if(length % 2 == 0)
	{
		maxmum = a[0];
		minmum = a[1];
		i = 2;
	}else
	{
		maxmum = a[0];
		minmum = a[0];
		i = 1;
	}
	for(; i < length; i = i + 2)
	{
		int tmp_min = a[i];
		int tmp_max = a[i];
		if(a[i] < a[i + 1])
		{
			tmp_max = a[i + 1];
		}else
		{
			tmp_min = a[i + 1];
		}
		if(minmum > tmp_min)
		{
			minmum = tmp_min;
		}
		if(maxmum < tmp_max)
		{
			maxmum = tmp_max;
		}
	}
	max = &maxmum;
	min = &minmum;
}
