/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:13:07 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/02 23:12:53 by cquinter         ###   ########.fr       */
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
$ MYVAR="1234"; echo "$MYVAR"$
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

void	set_path_and_cmd(char ***path, char **dash_cmd, char *cmd, char **envp)
{

	*path = ft_split(s_get_fromthis_env(envp, "PATH"), ':');
	if (!*path)
		perror_exit("ft_split");
	*dash_cmd = ft_strjoin("/", cmd);
	if (!*dash_cmd)
	{
		free_arr((void **)*path);
		perror_exit("ft_strjoin");
	}
}

char	*get_exec_path(char *cmd, char **envp)
{
	char	**path = NULL;
	char	*exec_path;
	char	*dash_cmd = NULL;
	int		i;

	set_path_and_cmd(&path, &dash_cmd, cmd, envp);
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

size_t get_cmd_idx(t_astnode *node)
{
	size_t	i;

	if (!node)
		return (-1);
	i = 0;
	while (i < node->token_count &&
		ft_strchr_idx(node->tokens[i][0].raw, '=') != (size_t)-1 &&
		ft_strchr_idx(node->tokens[i][0].raw, '=') != 0)
	{
		if (ft_strchr_idx(node->tokens[i][0].raw, '=') > ft_strchr_idx(node->tokens[i][0].raw, '"') ||
			ft_strchr_idx(node->tokens[i][0].raw, '=') > ft_strchr_idx(node->tokens[i][0].raw, '\'') ||
			ft_strchr_idx(node->tokens[i][0].raw, '=') > ft_strchr_idx(node->tokens[i][0].raw, '\\') ||
			ft_strchr_idx(node->tokens[i][0].raw, '=') > ft_strchr_idx(node->tokens[i][0].raw, ' ') ||
			!ft_isalpha(node->tokens[i][0].raw[0]))
			break;
		i++;
	}
	if (i == node->token_count)
		return (-1);
	return (i);
}

char	**cmdv_prep(t_astnode *node)
{
	char	**argv;
	size_t		i;

	argv = ft_calloc(node->token_count + 1, sizeof(char **));
	if (!argv)
		return (NULL);
	i = 0;
	node->cmd_i = get_cmd_idx(node);
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

 * set_n_env to set var=value to either genvp or lenvp not just the envp given as arg.
 *	* idea: wrap set_env to check and if/else set_n_env with the apropiate **envp
 * hangle $    if $ folled by quotes, jump it. if on its own, cmd
 * create a paralel linked list to index var, to be used by export when "expor var"
 * 
 
	DONE:*  updated builtin_echo to print each argv on the same line, fixed bug with nlflag
		 * "+ ft_strlen(name) + 1" added to sgetenv fts returns to run as getenv
		 * updated env (global and local) variabes at exec_cmd
	
	TO REVIEW:
		* 
2. built in progress
	* cd		done	linked (return 1 on success)env and local 
	* echo		done	linked (return 1 on success)env and loval - updated builtin_echo to print each argv on the same line, fixed bug with nlflag
	* env		bits	linked	online env working - PENDING : to add env var=xxxx and a program		
	* pwd		done	linked (return 1 on success)
	* exit		done - no clean up
	* export			exports n argvs ; does not export if not '='
	* unset				unsets n argvs


3.	mange
	SEQ
	SUBSHELL
	PIPE
	AND OR


**********************************************/

#include "../../include/libft.h"


static int	update_env(char ***envp, char *dup, char *name)
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
	idx = _sgetanon(*envp, name);
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
		if (update_env(envp, dup, name) == -1)
			return (free(dup), free(name), -1);
		free(name);
		i++;
	}
	return (0);
}

void	execute_command(char *path, char **argv, char**envp)
{
	int			pid;
	
	pid = fork();
	if (pid == 0)
	{
		char	*exec_path = NULL;
		if (ft_strchr(path, '/'))
			execve(path, argv, envp);
		else
			exec_path = get_exec_path(path, envp);
		if (!exec_path)
			perror_exit(path);
		else
			execve(exec_path, argv, envp);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	else
		perror("fork failed");
}

int	execute_ast(t_minishell *shell)
{
	// char	**g_env;
	// char	**l_env;
	if (!shell->current_tree)
			return (-1);
	// if (node->type == subshell)
	// 	execute_subshell(node);
	// else if (node->type == AND || OR)
	// 	execute_logical(node);
	// else if (node->type == PIPE)
	// 	execute_pipe(node)
	// else if (node->type == SEQ)
	// 	execute_sequence(node);
	if (shell->current_tree->type == AST_COMMAND)
	{
		shell->current_tree->cmdv = cmdv_prep(shell->current_tree); // handle variables
		shell->current_tree->genv_l = ft_arrlen((void **)shell->environment);
		if (shell->current_tree->cmd_i != (size_t)-1)
		{
			if (get_run_builtincmd(shell))
				return (printf("SUCCESS at exec_command: executed builtin %s\n", shell->current_tree->cmdv[0]), 
					free_arr((void **)shell->current_tree->cmdv), 0);
			else
			{
				execute_command(shell->current_tree->cmdv[shell->current_tree->cmd_i], 
					shell->current_tree->cmdv + shell->current_tree->cmd_i, 
					shell->current_tree->envp);
				ft_arrclear((void **)shell->current_tree->cmdv, free);
				return (0);
			}
				
		}
		return (set_n_envp(&shell->local_env, shell->current_tree->cmdv, shell->current_tree->token_count));
	}
	return (-1);
}
