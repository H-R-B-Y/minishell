/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:57:17 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/28 19:46:09 by cquinter         ###   ########.fr       */
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
	{.match = "unset", .fnc = &builtin_unset}};

	return (builtinmap);
}

int	get_run_builtincmd(t_minishell *shell)
{
	const struct s_buitinmapping	*fncmap;
	size_t							i;
	char							**argv;
	t_astnode						*node;

	node = shell->current_tree;
	argv = node->cmdv;
	set_n_envp(&shell->cmd_env, argv, node->cmd_i);
	fncmap = mapped_builtins();
	i = 0;
	while (i < BLTINCOUNT)
	{
		if (!ft_strcmp(argv[node->cmd_i], fncmap[i].match))
			return (fncmap[i].fnc(shell, argv + node->cmd_i, node->envp));
		i++;
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
