#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COLOR_NONE "\033[0m"
#define FONT_COLOR_RED "\033[0;31m"

void quick_sort(int a[], int p, int r);
int partition(int a[], int p, int r);
int randomized_partition(int a[], int p, int r);
void randomized_quick_sort(int a[], int p, int r);
void insert_sort(int a[], int p, int r);
void ameliorate_quick_sort(int a[], int p, int r, int k);

int main()
{
	while(1)
	{
		printf("====================Quick Sort========================\n");
		printf(" 1. quick_sort\n");
		printf(" 2. randomized_quick_sort\n");
		printf(" 3. ameliorate_quick_sort\n");
		printf(" 4. compare quick_sort and ameliorate_quick_sort\n");
		printf(" Please select(1, 2, 3, 4, -1 to quit): ");
		int select;
		scanf("%d", &select);
		if(select == -1)
		{
			printf("bye bye..");
			exit(0);
		}
		int length;
		printf("How many numbers do you want to sort? ");
		scanf("%d", &length);
		int data[length]; 
		printf(FONT_COLOR_RED"data before sorting is: \n"COLOR_NONE);
		srand((unsigned)time(NULL));
		int j = 0;
		for(int i = 0; i < length; i++)
		{
			j ++;
			data[i] = rand() % (length * 5);
			printf("%d ", data[i]);
			if(j % 10 == 0)
			{
				printf("\n");
			}
		}
		printf("\n");
		switch(select)
		{
			case 1:
				quick_sort(data, 0, length - 1);
				break;
			case 2:
				randomized_quick_sort(data, 0, length - 1);
				break;
			case 3:
				printf("Please enter k: ");
				int k;
				scanf("%d", &k);
				ameliorate_quick_sort(data, 0, length - 1, k);
				break;
			case 4:
				printf("Please enter k: ");
				int kk;
				scanf("%d", &kk);
				int data_copy[length];
				for(int i = 0; i < length; i++)
				{
					data_copy[i] = data[i];
				}
				clock_t start1 = clock();
				ameliorate_quick_sort(data, 0, length - 1, kk);
				clock_t end1 = clock();
				clock_t duration1 = end1 - start1;
				clock_t start2 = clock();
				quick_sort(data_copy, 0, length - 1);
				clock_t end2 = clock();
				clock_t duration2 = end2 - start2;
				printf(FONT_COLOR_RED"Run time of ameliorate_quick_sort is: %lu\n"COLOR_NONE, duration1);
				printf(FONT_COLOR_RED"Run time of quick_sort is: %lu\n"COLOR_NONE, duration2);
				break;

		}
		printf(FONT_COLOR_RED"After sorting is:\n"COLOR_NONE);
		int m = 0;
		for(int i = 0; i < length; i ++)
		{
			m ++;
			printf("%d ", data[i]);
			if(m % 10 == 0)
			{
				printf("\n");
			}
		}
		printf("\n");
	}
	return 0;
}

void insert_sort(int a[], int p, int r)
{
	if(p == r)
	{
		return;
	}

	for(int j = p + 1; j <= r; j ++ )
	{
		int key = a[j];
		int i = j - 1;
		while(i >= 0 && a[i] > key)
		{
			a[i + 1] = a[i];
			i --;
		}
		a[i + 1] = key;
	}
}

void ameliorate_quick_sort(int a[], int p, int r, int k)
{
	if((r - p + 1) <= k)
	{
		insert_sort(a, p, r);
	}else
	{
		int q = partition(a, p , r);
		ameliorate_quick_sort(a, p, q - 1, k);
		ameliorate_quick_sort(a, q + 1, r, k);
	}
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
