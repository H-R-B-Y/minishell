#include <stdio.h>
#include <unistd.h>

int main(void)
{
	char c;

	c = 'p';
	while(1)
		write(1, &c, 1);
	return 0;
}