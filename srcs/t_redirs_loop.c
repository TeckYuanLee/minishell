#include "minishell.h"

static t_bool	delimiter_found(char *delimiter, char *line)
{
	if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
		return (TRUE);
	return (FALSE);
}

int	make_here_doc(char *delimiter)
{
	int		fd;
	char	*line;

	fd = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		else if (delimiter_found(delimiter, line))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	return (open(".here_doc", O_RDONLY));
}

int	ft_redirs_loop_two(t_tree *tree, t_exec *exec, t_env *envi)
{
	if (tree->type == REDIR_APP)
	{
		exec->fd_out[1] = open(tree->data[0], \
			O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (access(tree->data[0], W_OK))
			ft_redir_error(tree, exec->fd_out[1], envi);
		dup2(exec->fd_out[1], STDOUT_FILENO);
		close(exec->fd_out[1]);
	}
	if (tree->type == HERE_DOC && tree->left_node->type != HERE_DOC)
	{
		restore_term_settings(&envi->termios_p);
		set_term_settings();
		init_here_doc_signals();
		if (tree->up_node->type == PIPE && !prev_heredoc_exists(tree))
			close(exec->fd_in[0]);
		exec->fd_in[0] = make_here_doc(tree->data[0]);
		dup2(exec->fd_in[0], STDIN_FILENO);
		close(exec->fd_in[0]);
		unlink(".here_doc");
	}
	return (0);
}

//	handle in and out redirection
int	ft_redirs_loop(t_tree *tree, t_exec *exec, t_env *envi)
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

//	free env variables
void	free_envi(t_env *envi)
{
	clean_tree(envi->loc_tree_ptr);
	free(envi->exec);
	ft_free_split(&envi->var);
	free_envp(envi->ms_envp);
	close(0);
	close(1);
}

//	file inwards redirection error
int	ft_redir_in_error(t_tree *tree, t_env *envi)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(tree->data[0], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	free_envi(envi);
	exit(1);
	return (-1);
}

//	lnr angles usage error message
int	ft_redir_error(t_tree *tree, int fd, t_env *envi)
{
	close(fd);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(tree->data[0], 2);
	ft_putstr_fd(": Permission denied\n", 2);
	free_envi(envi);
	exit(1);
	return (-1);
}

//	function execution error message
int	ft_error_exec(int code, int *fd, t_env *envi)
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
