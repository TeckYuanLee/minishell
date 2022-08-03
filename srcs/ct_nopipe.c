#include "minishell.h"

//	close the nopipe instructions
void	ft_helper_nopipe_end(t_tree *tree, t_env *envi, t_exec *exec)
{
	if (!tree->data[0] || !ft_strncmp(tree->data[0], "", 1))
	{
		ft_close_fd(exec->fd_in);
		ft_close_fd(exec->fd_out);
		free_envi(envi);
		exit(0);
	}
	dup2(exec->fd_in[0], STDIN_FILENO);
	ft_close_fd(exec->fd_in);
	ft_close_fd(exec->fd_out);
	ft_check_builtin_child(tree, envi, exec);
	ft_get_paths(envi, tree->data);
}

//	wait for signal at end of nopipe instructions
int	ft_nopipe_end_util(t_tree *tree, pid_t pid, int status)
{
	if (tree->left_node && tree->left_node->type == HERE_DOC)
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) == 1)
			return (33);
	}
	return (0);
}

//	child process of nopipe
void	ft_nopipe_child(t_tree *tree, t_env *envi, t_exec *exec)
{
	while (tree->left_node)
	{
		ft_redirs_loop(tree, exec, envi);
		tree = get_next_node(tree);
	}
	if (tree->type == CMD)
		ft_helper_nopipe_end(tree, envi, exec);
}

//	process the end of nopipe instructions
int	ft_nopipe_end(t_tree *tree, t_env *envi, t_exec *exec)
{
	pid_t	pid;
	int		status;

	status = 0;
	exec->index++;
	exec->fd_in[0] = exec->fd_out[0];
	exec->fd_in[1] = exec->fd_out[1];
	if (prev_heredoc_exists(tree) == 1)
		wait(&status);
	pid = fork();
	if (pid < 0)
		ft_error_exec(1, 0, envi);
	if (!pid)
		ft_nopipe_child(tree, envi, exec);
	if (ft_nopipe_end_util(tree, pid, status) == 33)
		return (33);
	ft_close_fd(exec->fd_in);
	return (0);
}

//	start of nopipe instructions
void	ft_helper_nopipe_start(t_tree *tree, t_env *envi)
{
	if (!tree->data[0] || !ft_strncmp(tree->data[0], "", 1))
	{
		free_envi(envi);
		exit(0);
	}
	ft_check_builtin(tree, envi);
	ft_get_paths(envi, tree->data);
}

//	start tree roots when type is nopipe
int	ft_nopipe_start(t_env *envi, t_tree *tree, t_exec *exec)
{
	pid_t	pid;

	exec->index++;
	pid = fork();
	if (pid < 0)
		ft_error_exec(1, 0, envi);
	if (!pid)
	{
		restore_signals();
		while (tree->left_node)
		{
			ft_redirs_loop(tree, exec, envi);
			tree = get_next_node(tree);
		}
		if (tree->type == CMD)
			ft_helper_nopipe_start(tree, envi);
	}
	ft_check_nonwriteable(tree, envi, exec);
	return (0);
}