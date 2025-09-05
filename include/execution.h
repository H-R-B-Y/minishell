/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:02:44 by cquinter          #+#    #+#             */
/*   Updated: 2025/09/05 21:11:21 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "./abstract_syntax_tree.h"
# include "./builtin.h"
# include <unistd.h>


#define	NPROCESSORS 20
#define INTERNAL_MAX 40
#include <limits.h>

typedef struct s_xpnd_info
{
	pthread_t	t_id;
	t_minishell	*shell;
	size_t		tknxthread;
	t_token		**token;
	char		**xpnded_words;

}	t_xpnd_info;

/**
 * @brief Get the executable path for a given command
 * 
 * @param shell Pointer to the shell object
 * @param cmd The command to check
 * @param envp The current environment context of the shell (for PATH)
 * @return char* Allocated execution path
 */
char	*get_exec_path(t_minishell *shell, char *cmd, char **envp);

/**
 * @brief Expand parameters from tokens in the cmdv and split into the argv
 * 
 * @param shell Pointer to the shell object
 * @param node The current node
 * @param argv Pointer to the argument list produced as a result of expansion
 * @param n Count of args
 */
void	xpnd_param_var(t_xpnd_info *info);

/**
 * @brief Expand wildcards from the argv and splits into words
 * 
 * @param shell Pointer to the shell object
 * @param node The current node
 * @param argv Pointer to the argument list produced as a result of expansion
 * @param n Count of args
 */
void	filename_expansion(t_minishell *shell, t_astnode *node,
			char ***argv, size_t *n);

/**
 * @brief Remove quotes and backslashes from the values in argv
 * 
 * @param shell Pointer to the shell object
 * @param node The current node
 * @param argv Pointer to the argument list produced as a result of expansion
 * @param n Count of args
 */
void	quote_removal(t_minishell *shell, t_astnode *node,
			char ***argv, size_t *n);

/**
 * @brief Prepare the arguements for a command
 * 
 * @param shell Pointer to the shell object
 * @param node The current node
 * @return char** The command vector
 */
char	**cmdv_prep(t_minishell *shell, t_astnode *node);

/**
 * @brief Data used to restore file descriptors 
 */
typedef struct s_restore_rds
{
	/// @brief The subtype of the redirect
	int	subtype;
	/// @brief The filedescriptor that was mapped too
	int	to_fd;
	/// @brief Restoration point for filedesc 1
	int	dupped1;
	/// @brief Restoration point for filedesc 2
	int	dupped2;
}	t_restore_rds;

typedef struct s_shell_expansion_fnc
{
	void	(*f)(t_xpnd_info *info);
}	t_shell_expansion_fnc;

int		t_oflag(const int redr_type);
void	_close_rstore_fds(t_restore_rds *info);
int		init_rd_rstr_info(t_restore_rds **info, t_redirect_desc *desc);

/**
 * @brief Prepare the filedescriptor restoration point for builtins
 * 
 * @param desc The redirect descriptor to create a restore point from
 * @param rd_restore the list of restore points
 * @return int ???
 */
int		rd_fd_restore(t_restore_rds *info);

/**
 * @brief Restore the filedescriptors from a list of restore points
 * 
 * @param info_lst The list of restore points
 */
void	rd_list_restore(t_list *info_lst);

/**
 * @brief Update or set a value in a given environment
 * 
 * @param envp Pointer to the environment array
 * @param dup ???
 * @param name The name of the value to update or set
 * @param f Function to lookup in the envp
 * @return int ???
 */
int		update_env(char ***envp,
			char *dup, char *name, ssize_t (*f)(char **, const char *));

/**
 * @brief Set a value in a given environment from an array of values
 * 
 * @param envp Pointer to a given environment
 * @param argv Array of values to set
 * @param n Number of values to set? or perhaps index to start setting from (idk)
 * @return int -1 on error
 */
int		set_n_envp(char ***envp, char **argv, size_t n);
int		set_any_env(t_minishell *shell, char **argv, size_t n);
/**
 * @brief handles envp for both built ins and expernal commands
 * 
 * Sets '_' and cmd only environment variables.
 * 
 * @param shell the shell struct
 * @param node the current node
 * @param b_in a pointer to b_in. Checked to set envp accordingly
 * @return char* the env string from the environment
 */
void	set_cmd_envp(t_minishell *shell, t_astnode *node,
			t_builtincmd b_in);

void	get_exec_cmd(t_minishell *shell, t_astnode *node, t_builtincmd b_in);

/**
 * @brief Execute a command node
 * 
 * @param shell Pointer to the shell data
 * @param node The current node
 * @return int -1 on error? (maybe)
 */
int		execute_command(t_minishell *shell, t_astnode *node);

/**
 * @brief Execute a pipe node
 * 
 * @param shell Pointer to the shell object
 * @param node The current node
 * @return int -1 on error?
 */
int		execute_pipe(t_minishell *shell, t_astnode *node);

/**
 * @brief Execute a subshell
 * 
 * @param shell Pointer to the shell object
 * @param node The current node
 * @return int -1 on error 
 */
int		execute_subshell(t_minishell *shell, t_astnode *node);

/**
 * @brief Execute a sequential node
 * 
 * @param shell Pointer to the shell object
 * @param node The current node
 * @return int -1 on error
 */
int		execute_seq(t_minishell *shell, t_astnode *node);

/**
 * @brief Execute a logical sequence
 * 
 * @param shell Pointer to the shell object
 * @param node The current node
 * @return int -1 on error
 */
int		execute_logical(t_minishell *shell, t_astnode *node);

/**
 * @brief Starting point to recursively execute the ast
 * 
 * @param shell Pointer to the shell object
 * @param node The node to execute 
 * @return int -1 on error
 */
int		execute_ast(t_minishell *shell, t_astnode *node);

#endif