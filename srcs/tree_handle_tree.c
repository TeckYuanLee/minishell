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

int	ft_close_fd(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
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
			tcsetattr(2, TCSANOW, &envi->termios_p);
			process_signal(WTERMSIG(status), &envi->exitcode, 0);
			signal_found = 1;
		}
		exec->index--;
	}
	if (signal_found || exec->builtin_check == 1)
		return (envi->exitcode);
	return (WEXITSTATUS(status));
}

//	building tree roots
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
		exec->fd_in[0] = exec->fd_out[0];
		exec->fd_in[1] = exec->fd_out[1];
		tree = get_next_node(tree);
	}
	envi->exitcode = ft_wait_on_children(exec, envi);
	ft_close_all(exec);
	return (0);
}
