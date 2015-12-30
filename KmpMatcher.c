#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void ComputePrefixFunction(char *pattern, int SP[]); 
void KmpMatcher(char *text, char *pattern);

int main()
{
	char *text = "bacbababaababacab";
	char *pattern = "ababaca";
	KmpMatcher(text, pattern);

	return 0;
}

void KmpMatcher(char *text, char *pattern)
{
	int n = strlen(text);
	int m = strlen(pattern);
	int SP[m];
	ComputePrefixFunction(pattern, SP);
	int q = 0;
	for(int i = 0; i < n; i++)
	{
		while(q > 0 && text[i] != pattern[q])
		{
			q = SP[q];
		}
		if(text[i] == pattern[q])
		{
			q++;
		}
		if(q == m)
		{
			printf("Pattern occurs with shift %d\n", i + 1 - m);
		}
	}
}

void ComputePrefixFunction(char *pattern, int SP[]) 
{
	int m = strlen(pattern);
	SP[0] = 0;    // index 0 --> 1 suffix
	int k = 0;    // prefix
	for(int q = 1; q < m; q++)
	{
		while(k > 0 && pattern[k] != pattern[q])
		{
			k = SP[k];	
		}
		if(pattern[q] == pattern[k])
		{
			k++;
		}
		SP[q] = k;
	}
}
