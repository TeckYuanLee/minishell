#include "minishell.h"

//	heredoc exists in previous node
int	prev_heredoc_exists(t_tree *tree)
{
	if (!tree)
		return (0);
	tree = tree->up_node;
	while (tree && tree->type != HERE_DOC)
		tree = tree->left_node;
	if (!tree)
		return (0);
	return (1);
}

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

//	handle append and heredoc
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
		tcsetattr(2, TCSANOW, &envi->termios_p);
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
