/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_handle_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 01:32:37 by telee             #+#    #+#             */
/*   Updated: 2022/08/17 01:32:37 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	close fd in and out
void	close_all(t_exec *exec)
{
	close_fd(exec->fd_out);
	close_fd(exec->fd_in);
}

int	close_fd(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
	return (0);
}

//	wait for children process to finish
int	wait_child(t_exec *exec, t_env *ms_env)
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
			tcsetattr(2, TCSANOW, &ms_env->termios_p);
			process_signal(WTERMSIG(status), &ms_env->exitcode, 0);
			signal_found = 1;
		}
		exec->index--;
	}
	if (signal_found || exec->builtin_check == 1)
		return (ms_env->exitcode);
	return (WEXITSTATUS(status));
}

//	building tree roots
int	build_tree(t_env *ms_env, t_tree *tree, t_exec *exec)
{
	int	i;

	ms_env->exitcode = 0;
	i = 0;
	while (tree)
	{
		if (tree->type == NO_PIPE && exec->index == 0)
		{
			start_nopipe(ms_env, tree, exec);
			ms_env->exitcode = wait_child(exec, ms_env);
			return (0);
		}
		i = handle_end_nopipe(ms_env, exec, tree);
		if (i == 33 || i == 34)
			return (i);
		i = handle_start_pipe(ms_env, exec, tree);
		if (i == 33 || i == 34)
			return (i);
		exec->fd_in[0] = exec->fd_out[0];
		exec->fd_in[1] = exec->fd_out[1];
		tree = get_next_node(tree);
	}
	ms_env->exitcode = wait_child(exec, ms_env);
	close_all(exec);
	return (0);
}
