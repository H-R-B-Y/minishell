
#include "../../include/minishell.h"

/*
 * sets n cmd envp starting at argv
 * quotes must be handled already
*/
int	set_n_envp(char ***envp, char **argv, size_t n)
{
	size_t	i;
	char	*name;
	char	*dup;

	i = 0;
	while (i < n)
	{
		name = ft_strndup(argv[i], ft_strchr(argv[i], '=') - argv[i]);
		if (name == NULL)
			return (-1);
		dup = ft_strdup(argv[i]);
		if (dup == NULL)
			return (free(name), -1);
		if (update_env(envp, dup, name, _sgetanon) == -1)
			return (free(dup), free(name), -1);
		free(name);
		i++;
		
	}
	return (0);
}
