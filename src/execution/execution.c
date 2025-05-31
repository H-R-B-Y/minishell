/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:13:07 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/31 18:36:58 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
// #include "../../include/libft.h"
// #include <stdio.h>

/*
Not sure if i should be writing the executor now, or if
it would be better to put some structure

Also see here:
https://stackoverflow.com/questions/1158091/defining-a-variable-with-or-without-export

if you do:
$ MYVAR="1234" echo "$MYVAR"
this will print nothing because the var is defined in the command scope
but the variable being expanded is expanded in the shell scope.

if you do:
$ MYVAR="1234"; echo "$MYVAR"
This WILL print 1234 because the assignment is sequentially before the 
command so the variable is defined in the shells scope so the shell 
can expand the variable.


*/

void free_arr(void **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	perror_exit(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void	set_path_and_cmd(char ***path, char **dash_cmd, t_minishell *shell)
{
	t_astnode *node;

	node = shell->current_tree;
	*path = ft_split(s_get_fromthis_env(node->envp, "PATH"), ':');
	printf("at set path %s", *path[0]);
	if (!*path)
		perror_exit("ft_split");
	*dash_cmd = ft_strjoin("/", node->cmdv[0]);
	if (!*dash_cmd)
	{
		free_arr((void **)*path);
		perror_exit("ft_strjoin");
	}
}

char	*get_exec_path(t_minishell *shell)
{
	char	**path = NULL;
	char	*exec_path;
	char	*dash_cmd = NULL;
	int		i;

	set_path_and_cmd(&path, &dash_cmd, shell);
	i = 0;
	while (path[i])
	{
		exec_path = ft_strjoin(path[i], dash_cmd);
		if (!exec_path)
		{
			free(dash_cmd);
			free_arr((void **)path);
			perror_exit("ft_strjoin");
		}
		if (access(exec_path, X_OK) == 0)
			break ;
		free(exec_path);
		i++;
	}
	free(dash_cmd);
	if (!path[i])
		return(free_arr((void **)path), NULL);
	return(free_arr((void **)path), exec_path);
}

char	**cmdv_prep(t_astnode *node)
{
	char	**argv;
	size_t		i;

	argv = ft_calloc(node->token_count + 1, sizeof(char **));
	if (!argv)
		return (NULL);
	i = 0;
	while(i < node->token_count)
	{
		argv[i] = remove_quotes(node->tokens[i][0].raw);
		if (!argv)
		{
			free_arr((void **)argv);
			return (NULL);
		}
		i++;
	}
	return (argv);
}

/* TODO **************************************
2. 
getenv to sgetenv


node having both genv and lenv? it is the node that needs them... to avoid passing the entire shell everytime
built ins
	DONE:*  updated builtin_echo to print each argv on the same line, fixed bug with nlflag
		 * "+ ft_strlen(name) + 1" added to sgetenv fts returns to run as getenv
		 * updated env (global and local) variabes at exec_cmd
	
	TO REVIEW:
		* s_get_interalenv(shell, "HOME"); at built_in cd
2. built in progress
	* cd		done	env and local
	* echo		done	env and loval
	* env				env
	* pwd
	* exit		done - no clean up
	* export			exports n argvs ; does not export if not '='
	* unset				unsets n argvs


3.	mange
	SEQ
	SUBSHELL
	PIPE
	AND OR

	4. to ask/ do you need the \n at void	*print_and_ret(void *p)

**********************************************/

#include "../../include/libft.h"

void	execute_command(t_minishell *shell)
{
	int			pid;
	char		**argv;
	t_astnode	*node;
	size_t		genv_l;
	size_t		cmd_i;
	size_t		var_i;
	ssize_t		anon;
	char		*var_name;

	genv_l = ft_arrlen((void **)shell->environment);
	node = shell->current_tree;
	argv = node->cmdv;
	cmd_i = 0;
	while (ft_strchr(argv[cmd_i], '='))
		cmd_i++;
	node->envp = (char **)ft_calloc(genv_l + cmd_i + 1, sizeof(void *));
	if (!node->envp)
		return (free_arr((void **)shell->current_tree->cmdv), 
			perror("minishell: ft_calloc:"));
	ft_arrlcat((void **)node->envp, (void **)shell->environment, genv_l + 1);
	
	var_i = 0;
	while (var_i < cmd_i)
	{
		var_name = ft_strndup(argv[var_i], ft_strchr(argv[var_i], '=') - argv[var_i]);
		anon = _sgetanon(node->envp, var_name);
		if (anon == -1)
			ft_arrlcat((void **)node->envp, (void **)argv + var_i, genv_l + 2);
		else
		{
			free(node->envp[anon]);
			node->envp[anon] = ft_strdup(argv[var_i]);
		}
		free(var_name);
		var_i++;
	}
	
	ft_arriter((void**)node->envp, print_and_ret);
	pid = fork();
	if (pid == 0)
	{
		char	*exec_path = NULL;
		if (ft_strchr(argv[cmd_i], '/'))
			execve(argv[cmd_i], argv + cmd_i, node->envp);
		else
			exec_path = get_exec_path(shell); // make it static[1024]  and size 1024 - 1 for NULL
		if (!exec_path)
			perror_exit(argv[cmd_i]);
		else
		{
			printf("at exec_command: child PID is %d executing %s\n", pid, exec_path);
			execve(exec_path, argv, node->envp);
		}
	}
	else if (pid > 0)
	{
		waitpid(pid, NULL, 0);
		ft_arrclear((void **)argv, free);
	}
	else
		perror("fork failed");
}

// void print_env_entry(char *entry)
// {
//     printf("%s\n", entry);
// }


int	execute_ast(t_minishell *shell)
{
	// char	**g_env;
	// char	**l_env;
	shell->current_tree->cmdv = cmdv_prep(shell->current_tree); // handle variables
	
	// ft_arriter((void **)shell->environment, print_and_ret);
	

	// if (node->type == subshell)
	// 	execute_subshell(node);
	// else if (node->type == AND || OR)
	// 	execute_logical(node);
	// else if (node->type == PIPE)
	// 	execute_pipe(node)
	// else if (node->type == SEQ)
	// 	execute_sequence(node);
	if (!shell->current_tree)
		return (-1);
	if (shell->current_tree->type == AST_COMMAND)
	{
		if (get_run_builtincmd(shell))
			return (printf("SUCCESS at exec_command: executed builtin %s\n", shell->current_tree->cmdv[0]), 
				free_arr((void **)shell->current_tree->cmdv), 0);
		else
			return (execute_command(shell), 0);
	}
	return (-1);
}