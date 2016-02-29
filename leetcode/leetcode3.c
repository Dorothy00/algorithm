#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void LNRS_hash(char *str);
void LNRS_dp(char *str);
void LNRS_dp_hash(char *str);
void LNRS_dp_hash_opt(char *str);

int main()
{
	char *str = "abcdecabedf";
	LNRS_hash(str);
	LNRS_dp(str);
	LNRS_dp_hash(str);
	LNRS_dp_hash_opt(str);
	LNRS_hash("aa");
	LNRS_dp_hash("aa");
	LNRS_dp_hash_opt("aa");
	return 0;
}

void LNRS_hash(char *str)
{
	int maxindex = 0;
	int maxlength = 0;
	int visit[256];
	memset(visit, 0, sizeof(visit));
	int size = strlen(str);

	for(int i = 0; i < size; i++)
	{
		visit[str[i]] = 1;
		for(int j = i + 1; j < size; j++)
		{
			if(visit[str[j]])
			{
				if((j - i) > maxlength)
				{
					maxlength = j - i;
					maxindex = i;
				}
				break;
			}else
			{
				visit[str[j]] = 1;
			}
		}
	}
	
	printf("Longest not repeated string is: \n");
	for(int i = maxindex; i < maxindex + maxlength; i++)
	{
		printf("%c ", str[i]);
	}
}

/*
 * 动态规划方法求解最长不重复子串
 * 求解以每个元素结尾的最长不重复子串，最后找到最长不重复子串
 * 对于当前元素，向后寻找是否有与其重复的元素，如果有则以当前元素结尾的最长不重复子串为当前元素下标减去重复元素下标
 * 如果没有重复元素则一直向后寻找到以当前元素的下一元素结尾的最长不重复子串的开始处
 * */
void LNRS_dp(char *str)
{
	int size = strlen(str);
	int maxindex = 0, maxlength = size ? 1 : 0;
	int dp[size];
	dp[0] = 1;

	int i, j;
	for(i = 1; i < size; i++)
	{
		int lowest = i - 1 + 1 - dp[i - 1];
		for(j = i - 1; j >= lowest; j--)
		{
			if(str[i] == str[j])
			{
				dp[i] = i - j;
				break;
			}
		}
		if(j < lowest)
		{
			dp[i] = dp[i - 1] + 1;
		}
		if(dp[i] > maxlength)
		{
			maxlength = dp[i];
			maxindex = i + 1 - maxlength;
		}
	}

	printf("\nLongest not repeated string is: \n");
	for(int k = maxindex; k < maxindex + maxlength; k++)
	{
		printf("%c ", str[k]);
	}
}

/*
 * 动态规划加hash的方法求解
 * 用visit数组保存每个元素出现的位置，这样就不用每次回头去找当前元素有没有重复出现过
 * */
void LNRS_dp_hash(char *str)
{
	int size = strlen(str);
	int visit[256];
	int dp[size];
	int maxindex = 0, maxlength = size ? 1 : 0;
	memset(visit, -1, sizeof(visit));
	memset(dp, 0, sizeof(dp));
	dp[0] = 1;
	visit[str[0]] = 0;

	for(int i = 1; i < size; i++)
	{
		if(visit[str[i]] == -1)
		{
			dp[i] = dp[i - 1] + 1;
			visit[str[i]] = i;
		}else
		{
			/* 假设当前元素下标为k，当前元素已出现的下标为r，以后一元素结尾的最长子串(记为s1)的开始元素下标为h ＝ i - 1 + 1 -dp[i - 1]
			 * 如果k < h, 则k和h之间可能有和s1中重复的元素，以k结尾的最长子串的长度不能拿k － r来计算，而应是s1 + 1
			 * */
			if(visit[str[i]] < (i - 1 + 1 - dp[i - 1]))
				dp[i] = dp[i - 1] + 1;
			else
				dp[i] = i - visit[str[i]];
			visit[str[i]] = i;
		}
		if(dp[i] > maxlength)
		{
			maxlength = dp[i];
			maxindex = i + 1 - maxlength;
		}
	}
	printf("\nLongest not repeated string is: \n");
	for(int k = maxindex; k < maxindex + maxlength; k++)
	{
		printf("%c ", str[k]);
	}
}

/* 
 * 将LNRS_dp_hash中的dp[size]优化为O(1)的空间
 * */
void LNRS_dp_hash_opt(char *str)
{
	int size = strlen(str);
	int visit[256];
	memset(visit, -1, sizeof(visit));
	int maxindex = 0, maxlength = size ? 1 : 0; // 当输入空字符串时maxlength为0
	int curindex = 0, curlength = size ? 1 : 0;
	visit[str[0]] = 0;

	for(int i = 1; i < size; i++)
	{
		if(visit[str[i]] == -1)
		{
			curlength++;
			visit[str[i]] = i;
		}else
		{
			if(visit[str[i]] < curindex)
			{
				curlength++;
			}else
			{
				curlength = i - visit[str[i]];
				curindex = visit[str[i]] + 1;
			}
			visit[str[i]] = i;
		}
		if(curlength >= maxlength)
		{
			maxlength = curlength;
			maxindex = curindex;
		}
	}
	printf("\nLongest not repeated string is: \n");
	for(int k = maxindex; k < maxindex + maxlength; k++)
	{
		printf("%c ", str[k]);
	}
}

/* 好吧，在leetcode上看到直接用hashmap的方法更加简洁
 * 不用visit数组存储，而用hashmap保存访问过的元素
 * */

