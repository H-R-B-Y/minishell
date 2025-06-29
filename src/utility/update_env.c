#include "../../include/minishell.h"

int	update_env(char ***envp, char *dup, char *name, ssize_t (*f)(char **, char *))
{
	ssize_t	idx;
	char	**old;

	if (*envp == NULL)
	{
		*envp = ft_calloc(2, sizeof(char *));
		if (*envp == NULL)
			return (-1);
		return ((*envp)[0] = dup, 0);
	}
	idx = f(*envp, name);
	if (idx == -1)
	{
		old = *envp;
		*envp = (char **)ft_arradd_back((void **)old, dup);
		if (*envp == NULL)
			return (*envp = old, -1);
		free(old);
	}
	else
	{
		free((*envp)[idx]);
		(*envp)[idx] = dup;
	}
	return (0);
}
