/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:57:17 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/13 13:09:04 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"
#include "../../include/minishell.h"

static const struct s_buitinmapping	*mapped_builtins(void)
{
	static const struct s_buitinmapping	builtinmap[BLTINCOUNT]
		= {{.match = "cd", .fnc = &builtin_cd},
	{.match = "echo", .fnc = &builtin_echo},
	{.match = "env", .fnc = &builtin_env},
	{.match = "exit", .fnc = &builtin_exit},
	{.match = "export", .fnc = &builtin_export},
	{.match = "pwd", .fnc = &builtin_pwd},
	{.match = "unset", .fnc = &builtin_unset},
	{.match = " ", .fnc = &builtin_}};

	return (builtinmap);
}

t_builtincmd _get_builtincmd(t_astnode *node)
{
	const struct s_buitinmapping	*fncmap;
	size_t							i;
	
	fncmap = mapped_builtins();
	i = 0;
	while (i < BLTINCOUNT)
	{
		if (!ft_strcmp(node->cmdv[node->cmd_i], fncmap[i].match))
			return (fncmap[i].fnc);
		i++;
	}
	return (NULL);
}

int	exec_builtincmd(t_minishell *shell, t_astnode *node, t_builtincmd cmd)
{
	if (cmd)
	{
		if (map_fds(node) < 0)
		{
			shell->return_code = 1;
			return (-1);
		}
		set_cmd_envp(shell, node, cmd);
		shell->return_code = cmd(shell,
			node->cmdv + node->cmd_i, &node->envp);
		rd_list_restore(node->rd_rstr_info);
		return (0);
	}
	return (0);
}

void	free_strvec(void *a)
{
	ft_arrclear(a, free);
}

void	*print_and_ret(void *p)
{
	printf("%s\n", (char *)p);
	return (p);
}

void	*export_print_and_ret(void *p)
{
	char	*str;

	str = p;
	ft_putstr_fd("declare -x ", 1);
	while (*str)
	{
		if (*str == '=')
		{
			printf("=\"%s\"\n", ++str);
			return (p);
		}
		ft_putchar_fd(*str++, 1);
	}
	ft_putchar_fd('\n', 1);
	return (p);
}
