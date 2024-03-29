/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 01:32:56 by telee             #+#    #+#             */
/*   Updated: 2022/08/21 21:32:52 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	
void	mid_pipe_utils(t_tree *tree, t_env *ms_env, t_exec *exec)
{
	while (tree->leaf)
	{
		handle_redir_io(tree, exec, ms_env);
		tree = get_next_node(tree);
	}
	if (tree->type == CMD)
	{
		if (!tree->data[0] || !ft_strncmp(tree->data[0], "", 1))
		{
			close_fd(exec->fd_in);
			close_fd(exec->fd_out);
			free_envi(ms_env, 0);
		}
		if (exec->fd_in[0])
			dup2(exec->fd_in[0], STDIN_FILENO);
		dup2(exec->fd_out[1], STDOUT_FILENO);
		close_fd(exec->fd_in);
		close_fd(exec->fd_out);
		check_builtin_child(tree, ms_env);
		get_paths(ms_env, tree->data);
	}
}

//	when pipe is in the middle of readline
int	mid_pipe(t_env *ms_env, t_tree *tree, t_exec *exec)
{
	pid_t	pid;
	int		status;

	exec->index++;
	if (pipe(exec->fd_out) < 0)
		exec_error(3, 0, ms_env);
	if (prev_heredoc_exists(tree) == 1)
		wait(&status);
	pid = fork();
	if (pid < 0)
		exec_error(1, exec->fd_out, ms_env);
	if (!pid)
		mid_pipe_utils(tree, ms_env, exec);
	if (tree->leaf && tree->leaf->type == HERE_DOC)
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) == 1)
			return (33);
	}
	close_fd(exec->fd_in);
	return (0);
}

//	do pipe command, builtin, and get path
void	start_pipe_utils(t_tree *tree, t_env *ms_env, t_exec *exec)
{
	while (tree->leaf)
	{
		handle_redir_io(tree, exec, ms_env);
		tree = get_next_node(tree);
	}
	if (tree->type == CMD)
	{
		if (!tree->data[0] || !ft_strncmp(tree->data[0], "", 1))
		{
			close_fd(exec->fd_in);
			close_fd(exec->fd_out);
			free_envi(ms_env, 0);
		}
		dup2(exec->fd_out[1], STDOUT_FILENO);
		close_fd(exec->fd_out);
		check_builtin_child(tree, ms_env);
		get_paths(ms_env, tree->data);
	}
	else
	{
		close_fd(exec->fd_in);
		close_fd(exec->fd_out);
	}
}

//	start the pipe command
int	start_pipe(t_env *ms_env, t_tree *tree, t_exec *exec)
{
	pid_t	pid;
	int		status;

	exec->index++;
	if (pipe(exec->fd_out) < 0)
		exec_error(3, exec->fd_out, ms_env);
	pid = fork();
	if (pid < 0)
		exec_error(1, 0, ms_env);
	if (!pid)
	{
		ms_signals("restore");
		start_pipe_utils(tree, ms_env, exec);
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
