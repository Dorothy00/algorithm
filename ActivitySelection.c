#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void ActivitySelection(int s[], int f[], bool a[], int n);
int main()
{
	int s[11] = {1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12};
	int f[11] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
	bool a[11];
	ActivitySelection(s, f, a, 11);
	for(int i = 0; i < 11; i++)
	{
		printf("[%d, %d]: %d\n", s[i], f[i], a[i]);
	}
	return 0;
}

/*
 * 活动选择问题 
 * */
void ActivitySelection(int s[], int f[], bool a[], int n)
{
	a[0] = true;
	int j = 0;
	for(int i = 1; i < n; i ++)
	{
		if(s[i] > f[j])
		{
			a[i] = true;
			j = i;
		}else
		{
			a[i] = false;
		}
	}
}
