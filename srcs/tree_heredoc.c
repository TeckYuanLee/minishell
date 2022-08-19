/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 01:32:41 by telee             #+#    #+#             */
/*   Updated: 2022/08/17 01:32:41 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	heredoc exists in previous node
int	prev_heredoc_exists(t_tree *tree)
{
	if (!tree)
		return (0);
	tree = tree->prev;
	while (tree && tree->type != HERE_DOC)
		tree = tree->leaf;
	if (!tree)
		return (0);
	return (1);
}

int	make_heredoc(char *delim)
{
	int		fd;
	char	*line;

	fd = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		else if (!ft_strncmp(line, delim, ft_strlen(delim) + 1))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	return (open(".heredoc", O_RDONLY));
}

//	handle heredoc function
void	handle_heredoc(t_exec *exec, t_env *ms_env)
{
	ms_env->exitcode = wait_child(exec, ms_env);
	close_fd(exec->fd_out);
	close_fd(exec->fd_in);
}
