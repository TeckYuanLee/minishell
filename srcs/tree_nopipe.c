/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_nopipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 01:32:53 by telee             #+#    #+#             */
/*   Updated: 2022/08/17 16:13:52 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	wait for signal at end of nopipe instructions
int	ft_nopipe_end_util(t_tree *tree, pid_t pid, int status)
{
	if (tree->leaf && tree->leaf->type == HERE_DOC)
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) == 1)
			return (33);
	}
	return (0);
}

//	child process of nopipe
void	ft_nopipe_child(t_tree *tree, t_env *ms_env, t_exec *exec)
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
		dup2(exec->fd_in[0], STDIN_FILENO);
		ft_close_fd(exec->fd_in);
		ft_close_fd(exec->fd_out);
		ft_check_builtin_child(tree, ms_env);
		ft_get_paths(ms_env, tree->data);
	}
}

//	process the end of nopipe instructions
int	ft_nopipe_end(t_tree *tree, t_env *ms_env, t_exec *exec)
{
	pid_t	pid;
	int		status;

	status = 0;
	exec->index++;
	exec->fd_in[0] = exec->fd_out[0];
	exec->fd_in[1] = exec->fd_out[1];
	if (prev_heredoc_exists(tree) == 1)
		wait(&status);
	pid = fork();
	if (pid < 0)
		ft_error_exec(1, 0, ms_env);
	if (!pid)
		ft_nopipe_child(tree, ms_env, exec);
	if (ft_nopipe_end_util(tree, pid, status) == 33)
		return (33);
	ft_close_fd(exec->fd_in);
	return (0);
}

//	if command and no data to write, return
int	ft_check_nonwriteable(t_tree *tree, t_env *ms_env, t_exec *exec)
{
	exec->builtin_check = 0;
	while (tree)
	{
		if (tree->type == CMD)
		{
			if (!tree->data[0])
				break ;
			ft_start_builtin(tree, ms_env, exec);
			break ;
		}
		tree = get_next_node(tree);
	}
	return (0);
}

//	start tree roots when type is nopipe
int	ft_nopipe_start(t_env *ms_env, t_tree *tree, t_exec *exec)
{
	pid_t	pid;

	exec->index++;
	pid = fork();
	if (pid < 0)
		ft_error_exec(1, 0, ms_env);
	if (!pid)
	{
		ms_signals("restore");
		while (tree->leaf)
		{
			ft_redirs_loop(tree, exec, ms_env);
			tree = get_next_node(tree);
		}
		if (tree->type == CMD)
		{
			if (!tree->data[0] || !ft_strncmp(tree->data[0], "", 1))
				free_envi(ms_env, 0);
			ft_check_builtin(tree, ms_env);
			ft_get_paths(ms_env, tree->data);
		}
	}
	ft_check_nonwriteable(tree, ms_env, exec);
	return (0);
}
