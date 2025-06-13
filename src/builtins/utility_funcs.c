/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:57:17 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/04 18:21:22 by hbreeze          ###   ########.fr       */
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
	node->envp = (char **)ft_arrmap((void **)shell->environment,
		(void *)ft_strdup, free);
	if (!node->envp)
		return (ft_arrclear((void **)argv, free), 
			perror("minishell: ft_arrmap"), 0);
	set_n_envp(&node->envp, argv, node->cmd_i);
	fncmap = mapped_builtins();
	i = 0;
	while (i < BLTINCOUNT)
	{
		if (!ft_strcmp(argv[0], fncmap[i].match))
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
