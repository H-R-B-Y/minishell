/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:57:17 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/26 16:46:35 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

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

t_builtincmd	get_builtincmd(char *str)
{
	const struct s_buitinmapping	*fncmap;
	size_t							i;

	fncmap = mapped_builtins();
	i = 0;
	while (i < BLTINCOUNT)
	{
		if (!ft_strcmp(str, fncmap[i].match))
			return (fncmap[i].fnc);
		i++;
	}
	return ((void *)0);
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
