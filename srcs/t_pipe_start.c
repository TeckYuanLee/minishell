#include "minishell.h"

void	ft_helper_pipe_inbetween(t_tree *tree, t_envi *envi, t_executor *exec)
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
		if (exec->fd_in[0])
			dup2(exec->fd_in[0], STDIN_FILENO);
		dup2(exec->fd_out[1], STDOUT_FILENO);
		ft_close_fd(exec->fd_in);
		ft_close_fd(exec->fd_out);
		ft_check_builtin_child(tree, envi, exec);
		ft_get_paths(envi, tree->data);
	}
}

int	ft_pipe_inbetween(t_envi *envi, t_tree *tree, t_executor *exec)
{
	pid_t	pid;
	int		status;

	exec->index++;
	if (pipe(exec->fd_out) < 0)
		ft_error_exec(3, 0, envi);
	if (prev_heredoc_exists(tree) == 1)
		wait(&status);
	pid = fork();
	if (pid < 0)
		ft_error_exec(1, exec->fd_out, envi);
	if (!pid)
		ft_helper_pipe_inbetween(tree, envi, exec);
	if (tree->left_node && tree->left_node->type == HERE_DOC)
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) == 1)
			return (33);
	}
	ft_close_fd(exec->fd_in);
	return (0);
}

int	ft_check_builtin_child(t_tree *tree, t_envi *envi, t_executor *exec)
{
	int	i;

	i = 0;
	if (!ft_strncmp(tree->data[0], "echo", 4))
		i = ft_builtin_echo(envi, tree);
	else if (!ft_strncmp(tree->data[0], "cd", 3))
	{
		envi->exitcode = ms_cd(tree->data, envi);
		i++;
	}
	i = ft_check_builtin_add(tree, envi, i);
	if (!ft_strncmp(tree->data[0], "exit", 5))
	{
		envi->exitcode = ft_exit(tree, envi, exec);
		i++;
	}
	if (i != 0)
	{
		free_envi(envi);
		exit(envi->exitcode);
	}
	else
		return (i);
}

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

void	ft_helper_pipe_start(t_tree *tree, t_envi *envi, t_executor *exec)
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

int	ft_pipe_start(t_envi *envi, t_tree *tree, t_executor *exec)
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
