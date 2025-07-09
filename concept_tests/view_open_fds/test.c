#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/*
    S_ISREG(m)

    is it a regular file?

    S_ISDIR(m)

    directory?

    S_ISCHR(m)

    character device?

    S_ISBLK(m)

    block device?

    S_ISFIFO(m)

    FIFO (named pipe)?

    S_ISLNK(m)

    symbolic link? (Not in POSIX.1-1996.)

    S_ISSOCK(m)

    socket? (Not in POSIX.1-1996.) 
*/

int main(int argc, char **argv)
{
	struct stat buff = {0};
	int i;

	i = 0;
	while (i < 1024)
	{
		if (argv[1] && argv[1][0] == '-' && isatty(i) && ++i)
			continue;
		fstat(i, &buff);
		if (S_ISREG(buff.st_mode))
			printf("%d is regular file\n", i);
		if (S_ISDIR(buff.st_mode))
			printf("%d is directory\n", i);
		if (S_ISFIFO(buff.st_mode))
			printf("%d is FIFO\n", i);
		if (S_ISBLK(buff.st_mode))
			printf("%d is Block device\n", i);
		if (S_ISCHR(buff.st_mode))
			printf("%d is character device\n", i);
		if (S_ISLNK(buff.st_mode))
			printf("%d is link file\n", i);
		if (S_ISSOCK(buff.st_mode))
			printf("%d is socket\n", i);
		i++;
		buff = (struct stat){0};
	}
}