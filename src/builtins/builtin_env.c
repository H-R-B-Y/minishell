/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <cquinter@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:34:33 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/05 14:56:09 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h"

int	builtin_env(t_minishell *shell, char **argv, char ***envp)
{
	char	**env;
	char	*sep;
	size_t	i;

	if (!argv[1] && !(*envp))
		return (ft_arriter((void *)shell->environment, print_and_ret), 0);
	env = (char **)ft_arrmap((void **)shell->environment,
			(void *)ft_strdup, free);
	if (!env)
		return (perror("minishell: builtin_env"), 1);
	if (set_n_envp(&env, *envp, ft_arrlen((void *)(*envp))) == -1)
		return (ft_arrclear((void *)env, free), 1);
	i = 1;
	while (argv[i])
	{
		sep = ft_strchr(argv[i], '=');
		if (!sep)
			return (ft_arrclear((void *)env, free), ft_fprintf(2,
				"%s: env: Unable to run program\n", shell->name), 1);
		if (set_n_envp(&env, argv + i, 1) == -1)
			return (ft_arrclear((void *)env, free), 1);
		i++;
	}
	ft_arriter((void *)env, print_and_ret);
	return (ft_arrclear((void *)env, free), 0);
}
