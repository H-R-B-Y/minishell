#include "../../include/minishell.h"

void init_pwd(t_minishell *shell, char ***envp)
{
	char **pwd;
	char *dup;
	
	pwd = (char **)ft_calloc(3, sizeof(char *));
	pwd[0] = getcwd(0, 0);
	if (!pwd[0])
		perror_exit(shell, "cd");
	pwd[1] = str_vec_join((char *[3]){"PWD=", pwd[0], 0});
	if (!pwd[1])
	{
		ft_arrclear((void **)pwd, free);
		perror_exit(shell, "cd");
	}
	if (_sgetanon(shell->environment, "OLDPWD") < 0)
	{
		dup = ft_strdup("OLDPWD");
		if (dup == NULL)
			return ;
		update_env(&shell->unassigned_env, dup, "OLDPWD", _sgetidx);
	}
	set_n_envp(envp, pwd + 1, 1);
	ft_arrclear((void **)pwd, free);
}
