#include <stdio.h>
#include <stdlib.h>

typedef struct I
{
	float start;
	float end;
}Interval;

void MiniUnitIntervals(float x[], int n);

int main()
{
	float x[8] = {1.5f, 2.1f, 2.4f, 2.7f, 3.6f, 4.8f, 5.1f, 6.2f};
	MiniUnitIntervals(x, 8);
	return 0;
}
void MiniUnitIntervals(float x[], int n)
{
	Interval intervals[n];
	int size = 0;
	intervals[0].start = x[0];
	intervals[0].end = x[0] + 1;
	size ++;
	Interval curr_interval = intervals[0];
	for(int i = 1; i < n; i++)
	{
		if(x[i] > curr_interval.end)
		{
			intervals[size].start = x[i];
			intervals[size].end = x[i] + 1;
			curr_interval = intervals[size];
			size ++;
		}
	}
	printf("Mini Unit Intervals are: \n");
	for(int i = 0; i < size; i ++)
	{
		printf("[%.2f, %.2f]\n", intervals[i].start, intervals[i].end);
	}
}
