/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_openfds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 14:52:58 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/13 16:02:59 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_stdfds(void)
{
	static struct stat	s = {0};
	int					code;

	code = fstat(STDIN_FILENO, &s);
	if (code < 0)
		return (-1);
	ft_bzero(&s, sizeof(struct stat));
	code = fstat(STDOUT_FILENO, &s);
	if (code < 0)
		return (-1);
	return (0);
}
