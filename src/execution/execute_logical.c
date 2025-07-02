
#include "../../include/minishell.h"

int	execute_logical(t_minishell *shell, t_astnode *node)
{
	execute_ast(shell, node->left_node);
	if ((node->type == AST_AND && shell->return_code == 0) ||
		(node->type == AST_OR && shell->return_code != 0))
		execute_ast(shell, node->right_node);
	return (shell->return_code);
}