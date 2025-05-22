/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:28:36 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/22 13:32:29 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <strings.h>

int main (int argc, char **argv, char **environ)
{
	int		nlflag;
	size_t	i;
	(void)environ;
	if (!argv[1])
		return (0);
	i = 1;
	nlflag = !strcmp(argv[i], "-n");
	i += nlflag;
	while (argv[i])
	{
		printf("%s%s", argv[i], (char *[2]){"", " "}[!!argv[i + 1]]);
		i++;
	}
	if (!nlflag)
		printf("\n");
	return (0);
}