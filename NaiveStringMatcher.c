#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void NaiveStringMatcher(char* text, char* pattern);
void FastNaiveStringMatcher(char* text, char* pattern);

int main()
{
	char* T = "abcabaabcabac";
	char* P = "abaa";
	NaiveStringMatcher(T, P);
	FastNaiveStringMatcher(T, P);

	return 0;
}

void NaiveStringMatcher(char* text, char* pattern)
{
	int n = strlen(text);
	int m = strlen(pattern);

	for(int i = 0; i <= n - m; i++)
	{
		if(text[i] == pattern[0])
		{
			bool flag = true;
			for(int j = 0; j < m; j++)
			{
				if(text[i + j] != pattern[j])
				{
					flag = false;
					break;
				}
			}
			if(flag)
			{
				printf("Pattern occurs with shift %d\n", i);
			}
		}
	}
}

/**假设pattern中每个字符都不相等
 */
void FastNaiveStringMatcher(char* text, char* pattern)
{
	int n = strlen(text);
	int m = strlen(pattern);

	for(int i = 0, j = 0; i < n; i++)
	{
		if(text[i] == pattern[j])
		{
			j++;
		}else if(j != 0)
		{
			j = 0;
			--i;
		}
		if(j == m)
		{
			printf("Pattern occurs with shift %d\n", i - m + 1);
		}
	}
}
