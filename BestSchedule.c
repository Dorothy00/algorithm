#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int N = 10;  // 任务数
int K = 3;  // 机器数
int t[30]; // 每个任务需要的时间
int best[30]; // 每个任务选择使用的机器
int tmpBest[30]; // 当前每个任务选择使用的机器
int bestTime = INT_MAX; // 最佳调度时间
int c[3]; // 每个机器上当前花费的时间

void BestSchedule(int dep);
int main()
{
	printf("Please enter each job's cost time: ");
	for(int i = 0; i < N; i++)
	{
		scanf("%d", &t[i]);		
	}
	for(int i = 0; i < K; i++)
	{
		c[i] = 0;
	}
	BestSchedule(0);
	printf("Best schedule time is: %d\n", bestTime);
	for(int i = 0; i < N; i++)
	{
		printf("job %d worked in machine %d\n", i + 1, best[i]);
	}
	return 0;
}

void BestSchedule(int dep)
{
	if(dep >= N)
	{
		int tmpBestTime = c[0];
		for(int i = 1; i < K; i++)
		{
			if(tmpBestTime < c[i])
			{
				tmpBestTime = c[i];
			}
		}
		if(tmpBestTime < bestTime)
		{
			bestTime = tmpBestTime;
			for(int i = 0; i < N; i++)
			{
				best[i] = tmpBest[i];
			}
		}
	}else
	{
		for(int i = 0; i < K; i++)
		{
			c[i] += t[dep];
			tmpBest[dep] = i + 1;
			if(c[i] < bestTime)
			{
				printf("i: %d", i);
				BestSchedule(dep + 1);
			}
			c[i] -= t[dep];
		}
	}
}
