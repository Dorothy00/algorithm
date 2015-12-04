#include <stdio.h>
#include <stdlib.h>

typedef struct A
{
	int start;
	int end;
}Activity;

typedef struct T
{
	Activity activity;
	int flag;   // 0 is start, 1 is end
}Time;

int GreedyActivitySelector(Activity activities[], int n);
void QuickSort(Time times[], int p, int r);
int partition(Time times[], int p, int r);

int main()
{
	int start[11] = {1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12};
	int end[11] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
	Activity activities[11];
	for(int i = 0; i < 11; i++)
	{
		activities[i].start = start[i];
		activities[i].end = end[i];
	}
	GreedyActivitySelector(activities, 11);
}

/*教室活动安排，可以简化为区间图着色问题
 * n个活动，按开始和结束时间分为2n个时间点。从2n个时间点中依次选择，
 * 如果是开始的时间点，将busy数加1，否则将busy数减1，free数加1
 */
int GreedyActivitySelector(Activity activities[], int n)
{
	Time times[2 * n];
	for(int i = 0; i < n; i++)
	{
		times[i * 2].activity = activities[i];
		times[i * 2].flag = 0;
		times[i * 2 + 1].activity = activities[i];
		times[i * 2 + 1].flag = 1;
	}
	QuickSort(times, 0, 2 * n - 1);	
	int free = 0;
	int busy = 0;
	for(int i = 0; i < 2 * n; i++)
	{
		if(!times[i].flag)
		{
			busy ++;
			if(free)
			{
				free --;	
			}
		}else
		{
			busy --;
			free ++;
		}
	}

	return free;
}

void QuickSort(Time times[], int p, int r)
{
	if(p < r)
	{
		int q = partition(times, p, r);
		QuickSort(times, p, q - 1);
		QuickSort(times, q + 1, r);
	}
}

int partition(Time times[], int p, int r)
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
	int x = times[r].flag ? times[r].activity.end : times[r].activity.start;
	for(int j = p; j < r; j++)
	{
		int y = times[j].flag ? times[j].activity.end : times[j].activity.start;
		if(y <= x)
		{
			i ++;
			Time tmp = times[i];
			times[i] = times[j];
			times[j] = tmp;
		}
	}
	Time tmp = times[i + 1];
	times[i + 1] = times[r];
	times[r] = tmp;

	return i + 1;
}
