/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_my_pid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:18:34 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/27 21:01:14 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

pid_t	get_my_pid(void)
{
	char	*current[3];
	char	*last_slash;
	int		output;

	current[0] = getcwd(0, 0);
	chdir("/proc/self");
	current[1] = getcwd(0, 0);
	last_slash = ft_strrchr(current[1], '/');
	current[2] = ft_strdup(last_slash + 1);
	output = ft_atoi(current[2]);
	(chdir(current[0]), free(current[0]), free(current[1]), free(current[2]));
	return (output);
}
