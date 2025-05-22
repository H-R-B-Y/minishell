/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:33:52 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/22 13:24:26 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
## chdir
``

## getcwd
`#include <unistd.h>`

## opendir
`#include <dirent.h>`

open dir opens a new directory stream for the directory descibed by arg. the stream is pointed at the first entry in the directory.

## readdir
`#include <dirent.h>`

returns a pointer to a directory entry struct representing the next entry in the directory stream.


## closedir
`#include <dirent.h>`

closes a directory stream. 

*/
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

extern char **environ;

int main ()
{
	chdir("test");
	char *t = getcwd(0, 0);
	printf("%s\n", t);
	execve("/usr/bin/bash", (char *[2]){"/usr/bin/bash", 0}, environ);
	return (0);
}
