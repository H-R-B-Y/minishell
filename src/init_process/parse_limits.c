/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_limits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 12:14:22 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/13 14:00:27 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/get_next_line.h"
/*
Max locked memory         2054737920           2054737920           bytes     
Max address space         unlimited            unlimited            bytes     
Max file locks            unlimited            unlimited            locks     
Max pending signals       622

Max open files            1048576
*/
static ssize_t	_get_ulimit_line(char *str)
{
	size_t	i;
	size_t	i2;
	ssize_t	out;

	i = 14;
	while (ft_iswhitespace(str[i]))
		i++;
	if (!ft_strncmp("unlimited", &str[i], 9))
		return (1048576); // Just use some arbitrary limit
	i2 = 0;
	while (ft_isdigit(str[i + i2]))
		i2++;
	str[i + i2] = '\0';
	out = ft_atoi(&str[i]);
	if (out < 0) // overflow in atoi will be negative, so just do something safe
		return (1024);
	return (out);
}

ssize_t	get_ulimitn(void)
{
	// Open the file
	int		fd;
	char	*line;
	ssize_t	output;
	short	done;

	fd = open("/proc/self/limits", O_RDONLY);
	if (fd < 0)
		return (perror("minishell: initialisation"), 0);
	line = get_next_line(fd);
	done = 0;
	while (line)
	{
		if (!done && !ft_strncmp("Max open files", line, 14) && ++done)
			output = _get_ulimit_line(line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (output);
}
