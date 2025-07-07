
#include "../../include/minishell.h"

int	set_any_env(t_minishell *shell)
{
	char	**argv;
	char	*name;
	size_t	n;
	size_t	i;

	argv = shell->current_tree->cmdv;
	n = shell->current_tree->token_count;
	i = 0;
	while (i < n)
	{
		name = ft_strndup(argv[i], ft_strchr(argv[i], '=') - argv[i]);
		if (name == NULL)
			return (-1);
		if (s_get_envid(shell, name) >= 0 || _sgetidx(shell->unassigned_env, name) >= 0)
		{
			if (_sgetidx(shell->unassigned_env, name) >= 0)
				ft_dirtyswap((void *)&shell->unassigned_env,
					ft_arrdel_atindex((void *)shell->unassigned_env, _sgetidx(shell->unassigned_env, name), free), free);	
			set_n_envp(&shell->environment, argv + i, 1);
		}
		else
			set_n_envp(&shell->local_env, argv + i, 1);
		i++;
		free(name);
	}
	return (0);
}