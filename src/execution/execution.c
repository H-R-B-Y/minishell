/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:13:07 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/02 01:12:35 by cquinter         ###   ########.fr       */
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
		if (ft_strchr_idx(node->tokens[i][0].raw, '=') < ft_strchr_idx(node->tokens[i][0].raw, '"') &&
			ft_strchr_idx(node->tokens[i][0].raw, '=') < ft_strchr_idx(node->tokens[i][0].raw, '\'') &&
			ft_strchr_idx(node->tokens[i][0].raw, '=') < ft_strchr_idx(node->tokens[i][0].raw, '\\') &&
			ft_strchr_idx(node->tokens[i][0].raw, '=') < ft_strchr_idx(node->tokens[i][0].raw, ' ') &&
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

 * status control with return for set_n_env and exec_cmd
 * free ft_dup if not
 * 
 


node having both genv and lenv? it is the node that needs them... to avoid passing the entire shell everytime
built ins
	DONE:*  updated builtin_echo to print each argv on the same line, fixed bug with nlflag
		 * "+ ft_strlen(name) + 1" added to sgetenv fts returns to run as getenv
		 * updated env (global and local) variabes at exec_cmd
	
	TO REVIEW:
		* s_get_interalenv(shell, "HOME"); at built_in cd
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

/*
sets n cmd envp starting at argv
quotes must be handled already

TO confirm: free(temp) or free_arr((void **)temp)
*/
int	set_n_envp(char ***envp, char **argv, size_t n)
{
	ssize_t		anon;
	size_t		var_i;
	char		*var_name;
	char		**temp;
	
	var_i = 0;
	printf("argv va1 = %s\n", argv[var_i]);
	while (var_i < n)
	{
		var_name = ft_strndup(argv[var_i], ft_strchr(argv[var_i], '=') - argv[var_i]);
		printf("varname = %s\n\n", var_name);
		if (!var_name)
			return (perror("minishell: unable to update environment HERE"), -1);
		anon = _sgetanon(*envp, var_name); //////// HERE THE BUGG  chech if env is null or not allocated. 
		if (anon == -1) //// handle it here
		{
			if (!*envp)
			{
				*envp = (char **)ft_calloc(2, sizeof(void *));
				if (!*envp)
					return (free(var_name), perror("minishell: strdup: unable to update env"), -1);
				*envp[0] = ft_strdup(argv[var_i]);
				if (!*envp[0])
					return (free(var_name), free(*envp), perror("minishell: strdup: unable to update env"), -1);
			}
			else
			{
				char *to_add = ft_strdup(argv[var_i]);
				if (!to_add)
					return (free(var_name), perror("minishell: strdup"), -1);
				temp = *envp;
				// ft_arriter((void **)*envp, print_and_ret);
				*envp = (char **)ft_arradd_back((void **)temp, (void *)to_add);
				ft_arriter((void **)*envp, print_and_ret);
				if (!*envp)
				{
					*envp = temp;
					free(to_add);
					return (free(var_name), perror("minishell: unable to update environment HERE 2"), -1);
				}
				free(temp);
			}
		}
		else
		{
			*temp = *envp[anon];
			*envp[anon] = ft_strdup(argv[var_i]);
			if (!*envp[anon])
			{
				*envp[anon] = *temp;
				free(var_name);
				return (perror("minishell: unable to update environment HERE 3"), -1);
			}
		}
		free(var_name);
		var_i++;
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
		{
			exec_path = get_exec_path(path, envp); // make it static[1024]  and size 1024 - 1 for NULL
			printf("at exec_command: child PID is %d executing %s\n", pid, exec_path);
		}
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

// void print_env_entry(char *entry)
// {
//     printf("%s\n", entry);
// }


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
