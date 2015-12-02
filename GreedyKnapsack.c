#include <stdlib.h>
#include <stdio.h>

void GreedyKnapsack(int v[], int w[], float x[], int c, int n);
void QuickSort(int v[], int w[], int p, int r);
int partition(int v[], int w[], int p, int r);

int main()
{
	int v[3] = {25, 24, 15};
	int w[3] = {18, 15, 10};
	float x[3];
	GreedyKnapsack(v, w, x, 20, 3);
	for(int i = 0; i < 3; i++)
	{
		printf("%.2f ", x[i]);
	}

	return 0;
}

void GreedyKnapsack(int v[], int w[], float x[], int c, int n)
{
	QuickSort(v, w, 0, n - 1);
	for(int i = 0; i < n; i++)
	{
		x[i] = 0;
	}
	int i;
	for(i = 0; i < n; i++)
	{
		if(w[i] > c)
		{
			break;
		}
		c -= w[i];
		x[i] = 1;
	}
	if(i < n)
	{
		x[i] = (c * 1.0) / w[i];
	}
}

void QuickSort(int v[], int w[], int p, int r)
{
	if(p < r)
	{
		int q = partition(v, w, p, r);
		QuickSort(v, w, p, q - 1);
		QuickSort(v, w, q + 1, r);
	}
}

int partition(int v[], int w[], int p, int r)
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
	float x = (v[r] * 1.0) / w[r];
	for(int j = p; j < r; j++)
	{
		float v_rate = (v[j] * 1.0) / w[j];
		if(v_rate > x)
		{
			i ++;
			int tmp_v = v[j];
			v[j] = v[i];
			v[i] = tmp_v;
			int tmp_w = w[j];
			w[j] = w[i];
			w[i] = tmp_w;
		}
	}
	int tmp_v = v[i + 1];
	v[i + 1] = v[r];
	v[r] = tmp_v;
	int tmp_w = w[i + 1];
	w[i + 1] = w[r];
	w[r] = tmp_w;

	return i + 1;
}
