#include "minishell.h"

//	handle heredoc function
void	ft_handle_heredoc(t_exec *exec, t_env *envi)
{
	envi->exitcode = ft_wait_on_children(exec, envi);
	ft_close_fd(exec->fd_out);
	ft_close_fd(exec->fd_in);
}

//	close fd in and out
void	ft_close_all(t_exec *exec)
{
	ft_close_fd(exec->fd_out);
	ft_close_fd(exec->fd_in);
}

//	simply get next node
t_tree	*get_next_node(t_tree *tree)
{
	if (!tree)
	{
		printf(BHRED "Empty forrest?!?!?\n");
		return (NULL);
	}
	if (tree->left_node)
		tree = tree->left_node;
	else
		tree = next_root_node(tree);
	return (tree);
}

int	ft_close_fd(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
	return (0);
}

//	simply copy fd out into fd in
int	ft_copy_fd(t_exec *exec)
{
	exec->fd_in[0] = exec->fd_out[0];
	exec->fd_in[1] = exec->fd_out[1];
	return (0);
}

//	handle heredoc for pipe when execute index == 0
int	ft_handle_loop_two(t_env *envi, t_exec *exec, t_tree *tree)
{
	int	i;

	i = 0;
	if (tree->type == PIPE && exec->index == 0)
	{
		i = ft_pipe_start(envi, tree, exec);
		if (i == 33)
		{
			ft_handle_heredoc(exec, envi);
			return (i);
		}
		if (i == 34)
			return (i);
	}
	return (0);
}

//	handle heredoc for pipe and nopipe
int	ft_handle_loop(t_env *envi, t_exec *exec, t_tree *tree)
{
	int	i;

	i = 0;
	if (tree->type == NO_PIPE && exec->index > 0)
	{
		i = ft_nopipe_end(tree, envi, exec);
		if (i == 33)
		{
			ft_handle_heredoc(exec, envi);
			return (i);
		}
	}
	if (tree->type == PIPE && exec->index > 0)
	{
		i = ft_pipe_inbetween(envi, tree, exec);
		if (i == 33)
		{
			ft_handle_heredoc(exec, envi);
			return (i);
		}
		if (i == 666)
			return (i);
	}
	return (0);
}

//	wait for children process to finish
int	ft_wait_on_children(t_exec *exec, t_env *envi)
{
	int	status;
	int	signal_found;

	status = 0;
	signal_found = 0;
	while (exec->index > 0)
	{
		wait(&status);
		if (WIFSIGNALED(status))
		{
			restore_term_settings(&envi->termios_p);
			process_signal(WTERMSIG(status), &envi->exitcode, 0);
			signal_found = 1;
		}
		exec->index--;
	}
	if (signal_found || exec->builtin_check == 1)
		return (envi->exitcode);
	return (WEXITSTATUS(status));
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

//	handle loops and building tree roots
int	ft_handle_tree(t_env *envi, t_tree *tree, t_exec *exec)
{
	int	i;

	envi->exitcode = 0;
	i = 0;
	while (tree)
	{
		if (tree->type == NO_PIPE && exec->index == 0)
		{
			ft_nopipe_start(envi, tree, exec);
			envi->exitcode = ft_wait_on_children(exec, envi);
			return (0);
		}
		i = ft_handle_loop(envi, exec, tree);
		if (i == 33 || i == 34)
			return (i);
		i = ft_handle_loop_two(envi, exec, tree);
		if (i == 33 || i == 34)
			return (i);
		ft_copy_fd(exec);
		tree = get_next_node(tree);
	}
	envi->exitcode = ft_wait_on_children(exec, envi);
	ft_close_all(exec);
	return (0);
}
