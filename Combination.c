#include <stdio.h>
#include <stdlib.h>

int CombNums(int n, int k);
void PrintComb(int a[], int n, int comb[], int m, int len);
void AllComb(int a[], int n);
int main()
{
	int c = CombNums(5, 3);
	printf("C(5,3)的组合数为：%d\n", c);
	int a[5] = {1, 2, 3, 4, 5};
	int* comb = (int*) malloc(sizeof(int) * 3);
	PrintComb(a, 5, comb, 3, 3);
	int b[3] = {1, 2, 3};
	AllComb(b, 3);
	return 0;
}

// 使用公式求组合数
int CombNums(int n, int k)
{
	int comb[n + 1][n + 1];
	for(int i = 0; i <= n; i++)
	{
		comb[i][1] = i;
		comb[i][0] = 1;
		comb[i][i] = 1;
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j < i; j++)
		{
			comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
		}
	}
	return comb[n][k];
}

/* 使用递归法打印组合数
 * 思路：从n个元素里选m个数
 * 从后往前选，选定下标i后，再在前i-1个里面选m-1个，依次递归，直到m为0
 * */
void PrintComb(int a[], int n, int comb[], int m, int len)
{
	if(m <= 0)
	{
		for(int i = 0; i < len; i++)
		{
			printf("%d ", comb[i]);
		}
		printf("\n");
		return;
	}
	for(int i = n - 1; i >= m -1; i--)
	{
		comb[m - 1] = a[i];
		PrintComb(a, i, comb, m - 1, len);
	}
}


/*
 * 打印全组合数
 * 思路：n个元素的组合数有2^n个，需要n位来表示。则这些组合数的序列依次为0、1、2、.... 2^n-1
 * 遍历这些序列，序列上的位值为1则打印数组上对应下标的值，否则不打印。
 */
void AllComb(int a[], int n)
{
	int nbit = 1 << n;
	for(int i = 0; i < nbit; i++)
	{
		for(int j = 0; j < n; j++)
		{
			if((1 << j) & i)
			{
				printf("%d ", a[j]);
			}
		}
		printf("\n");
	}
}
