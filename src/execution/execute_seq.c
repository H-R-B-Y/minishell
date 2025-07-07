
#include "../../include/minishell.h"

int	execute_seq(t_minishell *shell, t_astnode *node)
{
	execute_ast(shell, node->left_node);
	execute_ast(shell, node->right_node);
	return (shell->return_code);
}