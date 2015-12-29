#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void ComputeTransitionFunction(char *pattern, char*chset, int n, int ST[][n]);
void nextState(char *pattern, char *chset, char c, int curS, int* neS);
void FiniteAutomationMatcher(char *T, char *pattern, char* chset, int chsetNum, int ST[][chsetNum]);

int main()
{
	char *pattern = "ababaca";
	char *chset = "abc";
	int ST[8][3];
	char *text = "abababacaba";
	FiniteAutomationMatcher(text, pattern, chset, 3, ST);

	return 0;
}
/*
 * 有限自动机字符串匹配算法
 */
void FiniteAutomationMatcher(char *T, char *pattern, char* chset, int chsetNum, int ST[][chsetNum])
{
	ComputeTransitionFunction(pattern, chset, chsetNum, ST);

	int m = strlen(pattern);
	int n = strlen(T);
	int state = 0;
	for(int i = 0; i < n; i++)
	{
		int index = 0;
		for(int j = 0; j < chsetNum; j++)
		{
			if(chset[j] == T[i])
			{
				index = j;
				break;
			}
		}
		state = ST[state][index];
		if(state == m)
		{
			printf("Pattern occurs with shift %d\n", i - m + 1);
		}
	}
}

/*
 *计算状态转移函数
 */
void ComputeTransitionFunction(char *pattern, char*chset, int n, int ST[][n])
{
	const int m = strlen(pattern);
	for(int q = 0; q <= m; q++)
	{
		for(int c = 0; c < n; c++)
		{
			int neState;
			nextState(pattern, chset, chset[c], q, &neState);
			ST[q][c] = neState;
		}
	}
}

/*
 * 根据当前状态计算下一状态
 */
void nextState(char *pattern, char *chset, char c, int curS, int* neS)
{
	/* 输入字符与pattern中已匹配字符的下一字符相等，则下一输入字符后状态数加一（即匹配的字符数多了一个）*/	
	if(c == pattern[curS])
	{
		*neS = curS + 1;
	}else
	{
		int state;
		/*
		 * 字符不相等，则下一状态不可能比当前状态大
		 * 已匹配的字符数为curS个
		 * 从当前状态开始，将状态数递减，寻找一个状态使其满足：最后一个字符串为输入字符串，前面有“”状态数” - 1个字符串相匹配
		 * 下一状态至少为0，即一个都不匹配
		 * */
		for(state = curS; state > 0; state--)
		{
			if(c == pattern[state - 1])
			{
				int i;
				for(i = 0; i < state - 1; i++)
				{
					if(pattern[i] != pattern[curS - state + 1 + i])
					{
						break;
					}
				}
				/* 状态数 - 1 个字符全部匹配 */
				if(i == state - 1)
				{
					*neS = state;
					break;
				}
			}
		}
		/* 都不匹配 */
		if(state == 0)
		{
			*neS = state;
		}
	}
}
