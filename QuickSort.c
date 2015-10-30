#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
		printf(" 3. compare quick_sort and ameliorate_quick_sort\n");
		printf(" Please select(1, 2, 3, -1 to quit): ");
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
		printf("data before sorting is: \n");
		srand((unsigned)time(NULL));
		for(int i = 0; i < length; i++)
		{
			data[i] = rand() % 100;
			printf("%d ", data[i]);
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
			case 3:
				printf("Please enter k: ");
				int k;
				scanf("%d", &k);
				int time ameliorate_quick_sort(data, 0, length - 1, k);

		}
		printf("After sort...\n");
		for(int i = 0; i < length; i ++)
		{
			printf("%d ", data[i]);
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
