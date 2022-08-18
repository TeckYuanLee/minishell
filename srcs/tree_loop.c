/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 01:32:45 by telee             #+#    #+#             */
/*   Updated: 2022/08/19 02:02:45 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	handle append and heredoc
int	ft_redirs_loop_two(t_tree *tree, t_exec *exec, t_env *ms_env)
{
	if (tree->type == REDIR_APP)
	{
		exec->fd_out[1] = open(tree->data[0], \
			O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (access(tree->data[0], W_OK))
			ft_redir_error(tree, exec->fd_out[1], ms_env);
		dup2(exec->fd_out[1], STDOUT_FILENO);
		close(exec->fd_out[1]);
	}
	if (tree->type == HERE_DOC && tree->leaf->type != HERE_DOC)
	{
		tcsetattr(2, TCSANOW, &ms_env->termios_p);
		set_term_settings();
		ms_signals("heredoc");
		if (tree->prev->type == PIPE && !prev_heredoc_exists(tree))
			close(exec->fd_in[0]);
		exec->fd_in[0] = make_heredoc(tree->data[0]);
		dup2(exec->fd_in[0], STDIN_FILENO);
		close(exec->fd_in[0]);
		unlink(".heredoc");
	}
	return (0);
}

//	handle in and out redirection
int	ft_redirs_loop(t_tree *tree, t_exec *exec, t_env *ms_env)
{
	if (tree->type == REDIR_IN)
	{
		exec->fd_in[0] = open(tree->data[0], O_RDONLY);
		if (access(tree->data[0], F_OK))
			ft_redir_error(tree, 100, ms_env);
		if (access(tree->data[0], R_OK))
			ft_redir_error(tree, exec->fd_in[0], ms_env);
		dup2(exec->fd_in[0], STDIN_FILENO);
		close(exec->fd_in[0]);
	}
	if (tree->type == REDIR_OUT)
	{
		exec->fd_out[1] = open(tree->data[0], \
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (access(tree->data[0], W_OK))
			ft_redir_error(tree, exec->fd_out[1], ms_env);
		dup2(exec->fd_out[1], STDOUT_FILENO);
		close(exec->fd_out[1]);
	}
	ft_redirs_loop_two(tree, exec, ms_env);
	return (0);
}

//	handle heredoc for pipe when execute index == 0
int	ft_handle_loop_two(t_env *ms_env, t_exec *exec, t_tree *tree)
{
	int	i;

	i = 0;
	if (tree->type == PIPE && exec->index == 0)
	{
		i = start_pipe(ms_env, tree, exec);
		if (i == 33)
		{
			ft_handle_heredoc(exec, ms_env);
			return (i);
		}
		if (i == 34)
			return (i);
	}
	return (0);
}

//	handle heredoc for pipe and nopipe
int	ft_handle_loop(t_env *ms_env, t_exec *exec, t_tree *tree)
{
	int	i;

	i = 0;
	if (tree->type == NO_PIPE && exec->index > 0)
	{
		i = ft_nopipe_end(tree, ms_env, exec);
		if (i == 33)
		{
			ft_handle_heredoc(exec, ms_env);
			return (i);
		}
	}
	if (tree->type == PIPE && exec->index > 0)
	{
		i = mid_pipe(ms_env, tree, exec);
		if (i == 33)
		{
			ft_handle_heredoc(exec, ms_env);
			return (i);
		}
		if (i == 666)
			return (i);
	}
	return (0);
}
