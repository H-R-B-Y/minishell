
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

extern char **__environ;

int main(void)
{
	char *t[2] = {"/home/hbreeze/bin/",0};
	int p = execve(t[0], t, __environ);
	printf("%d", p);

}
