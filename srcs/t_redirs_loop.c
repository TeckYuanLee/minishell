#include "minishell.h"

int	ft_redirs_loop(t_tree *tree, t_executor *exec, t_envi *envi)
{
	if (tree->type == REDIR_IN)
	{
		exec->fd_in[0] = open(tree->data[0], O_RDONLY);
		if (access(tree->data[0], F_OK))
			ft_redir_in_error(tree, envi);
		if (access(tree->data[0], R_OK))
			ft_redir_error(tree, exec->fd_in[0], envi);
		dup2(exec->fd_in[0], STDIN_FILENO);
		close(exec->fd_in[0]);
	}
	if (tree->type == REDIR_OUT)
	{
		exec->fd_out[1] = open(tree->data[0], \
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (access(tree->data[0], W_OK))
			ft_redir_error(tree, exec->fd_out[1], envi);
		dup2(exec->fd_out[1], STDOUT_FILENO);
		close(exec->fd_out[1]);
	}
	ft_redirs_loop_two(tree, exec, envi);
	return (0);
}

void	free_envi(t_envi *envi)
{
	clean_tree(envi->loc_tree_ptr);
	free(envi->exec);
	ft_free_split(&envi->var);
	free_envp(envi->ms_envp);
	close(0);
	close(1);
}

int	ft_redir_in_error(t_tree *tree, t_envi *envi)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(tree->data[0], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	free_envi(envi);
	exit(1);
	return (-1);
}

int	ft_redir_error(t_tree *tree, int fd, t_envi *envi)
{
	close(fd);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(tree->data[0], 2);
	ft_putstr_fd(": Permission denied\n", 2);
	free_envi(envi);
	exit(1);
	return (-1);
}

int	ft_error_exec(int code, int *fd, t_envi *envi)
{
	if (fd != 0)
		close(*fd);
	free_envi(envi);
	ft_putstr_fd("minishell: ", 2);
	if (code == 1)
		ft_putstr_fd("fork error\n", 2);
	else if (code == 3)
		ft_putstr_fd("pipe error\n", 2);
	if (code >= 1 && code <= 3)
		exit(71);
	if (code == 4)
	{
		ft_putstr_fd("execve error\n", 2);
		exit(126);
	}
	else if (code == 5)
		ft_putstr_fd("malloc error\n", 2);
	else if (code == 6)
		ft_putstr_fd("acces error\n", 2);
	exit(1);
	return (-1);
}
