/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 20:31:11 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/24 18:13:08 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h"

int	builtin_(t_minishell *shell, char **argv, char ***envp)
{
	extern char	_binary_src_builtins_raw_dump_bin_start;
	extern char	_binary_src_builtins_raw_dump_bin_end;
	size_t		size;
	ssize_t		ret;

	(void)shell;
	(void)argv;
	(void)envp;
	size = &_binary_src_builtins_raw_dump_bin_end
		- &_binary_src_builtins_raw_dump_bin_start;
	ret = write(1, &_binary_src_builtins_raw_dump_bin_start, size);
	ret = write(1, "\n", 1);
	(void)ret;
	return (0);
}
