#include "minishell.h"

//	WIFSIGNALED & WTERMSIG
int	ft_pipe_start_util(t_tree *tree, pid_t pid)
{
	int	status;

	status = 0;
	if (tree->left_node && tree->left_node->type == HERE_DOC)
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) != 81)
			return (34);
	}
	return (0);
}

//	do pipe command, builtin, and get path
void	ft_helper_pipe_start(t_tree *tree, t_env *envi, t_exec *exec)
{
	while (tree->left_node)
	{
		ft_redirs_loop(tree, exec, envi);
		tree = get_next_node(tree);
	}
	if (tree->type == CMD)
	{
		if (!tree->data[0] || !ft_strncmp(tree->data[0], "", 1))
		{
			ft_close_fd(exec->fd_in);
			ft_close_fd(exec->fd_out);
			free_envi(envi);
			exit(0);
		}
		dup2(exec->fd_out[1], STDOUT_FILENO);
		ft_close_fd(exec->fd_out);
		ft_check_builtin_child(tree, envi, exec);
		ft_get_paths(envi, tree->data);
	}
	else
	{
		ft_close_fd(exec->fd_in);
		ft_close_fd(exec->fd_out);
	}
}

//	start the pipe command
int	ft_pipe_start(t_env *envi, t_tree *tree, t_exec *exec)
{
	pid_t	pid;
	int		i;

	exec->index++;
	if (pipe(exec->fd_out) < 0)
		ft_error_exec(3, exec->fd_out, envi);
	pid = fork();
	if (pid < 0)
		ft_error_exec(1, 0, envi);
	if (!pid)
	{
		restore_signals();
		ft_helper_pipe_start(tree, envi, exec);
	}
	i = ft_pipe_start_util(tree, pid);
	if (i == 34)
		return (34);
	return (0);
}
