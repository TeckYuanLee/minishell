#include "minishell.h"

//	
void	ft_helper_pipe_inbetween(t_tree *tree, t_env *ms_env, t_exec *exec)
{
	while (tree->leaf)
	{
		ft_redirs_loop(tree, exec, ms_env);
		tree = get_next_node(tree);
	}
	if (tree->type == CMD)
	{
		if (!tree->data[0] || !ft_strncmp(tree->data[0], "", 1))
		{
			ft_close_fd(exec->fd_in);
			ft_close_fd(exec->fd_out);
			free_envi(ms_env, 0);
		}
		if (exec->fd_in[0])
			dup2(exec->fd_in[0], STDIN_FILENO);
		dup2(exec->fd_out[1], STDOUT_FILENO);
		ft_close_fd(exec->fd_in);
		ft_close_fd(exec->fd_out);
		ft_check_builtin_child(tree, ms_env);
		ft_get_paths(ms_env, tree->data);
	}
}

//	when pipe is in the middle of readline
int	ft_pipe_inbetween(t_env *ms_env, t_tree *tree, t_exec *exec)
{
	pid_t	pid;
	int		status;

	exec->index++;
	if (pipe(exec->fd_out) < 0)
		ft_error_exec(3, 0, ms_env);
	if (prev_heredoc_exists(tree) == 1)
		wait(&status);
	pid = fork();
	if (pid < 0)
		ft_error_exec(1, exec->fd_out, ms_env);
	if (!pid)
		ft_helper_pipe_inbetween(tree, ms_env, exec);
	if (tree->leaf && tree->leaf->type == HERE_DOC)
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) == 1)
			return (33);
	}
	ft_close_fd(exec->fd_in);
	return (0);
}

//	do pipe command, builtin, and get path
void	ft_helper_pipe_start(t_tree *tree, t_env *ms_env, t_exec *exec)
{
	while (tree->leaf)
	{
		ft_redirs_loop(tree, exec, ms_env);
		tree = get_next_node(tree);
	}
	if (tree->type == CMD)
	{
		if (!tree->data[0] || !ft_strncmp(tree->data[0], "", 1))
		{
			ft_close_fd(exec->fd_in);
			ft_close_fd(exec->fd_out);
			free_envi(ms_env, 0);
		}
		dup2(exec->fd_out[1], STDOUT_FILENO);
		ft_close_fd(exec->fd_out);
		ft_check_builtin_child(tree, ms_env);
		ft_get_paths(ms_env, tree->data);
	}
	else
	{
		ft_close_fd(exec->fd_in);
		ft_close_fd(exec->fd_out);
	}
}

//	start the pipe command
int	ft_pipe_start(t_env *ms_env, t_tree *tree, t_exec *exec)
{
	pid_t	pid;
	int		status;

	exec->index++;
	if (pipe(exec->fd_out) < 0)
		ft_error_exec(3, exec->fd_out, ms_env);
	pid = fork();
	if (pid < 0)
		ft_error_exec(1, 0, ms_env);
	if (!pid)
	{
		ms_signals("restore");
		ft_helper_pipe_start(tree, ms_env, exec);
	}
	status = 0;
	if (tree->leaf && tree->leaf->type == HERE_DOC)
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) != 81)
			return (34);
	}
	return (0);
}
