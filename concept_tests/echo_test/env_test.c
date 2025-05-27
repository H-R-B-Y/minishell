
#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main (void)
{
	unsigned long int i;

	i = 0;
	// while (environ[i])
	// 	printf("%s\n", environ[i++]);
	void *t = malloc(sizeof(unsigned char) * 10);
	exit(0);
}