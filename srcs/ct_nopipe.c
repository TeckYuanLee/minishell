#include "minishell.h"

//	wait for signal at end of nopipe instructions
int	ft_nopipe_end_util(t_tree *tree, pid_t pid, int status)
{
	if (tree->left_node && tree->left_node->type == HERE_DOC)
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) == 1)
			return (33);
	}
	return (0);
}

//	child process of nopipe
void	ft_nopipe_child(t_tree *tree, t_env *envi, t_exec *exec)
{
	while (tree->left_node)
	{
		ft_redirs_loop(tree, exec, envi);
		tree = get_next_node(tree);
	}
	if (tree->type == CMD)
	{
		if (!tree->data[0] || !ft_strncmp(tree->data[0], "", 1))
		{
			ft_close_fd(exec->fd_in);
			ft_close_fd(exec->fd_out);
			free_envi(envi, 0);
		}
		dup2(exec->fd_in[0], STDIN_FILENO);
		ft_close_fd(exec->fd_in);
		ft_close_fd(exec->fd_out);
		ft_check_builtin_child(tree, envi, exec);
		ft_get_paths(envi, tree->data);
	}
}

//	process the end of nopipe instructions
int	ft_nopipe_end(t_tree *tree, t_env *envi, t_exec *exec)
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
		ft_error_exec(1, 0, envi);
	if (!pid)
		ft_nopipe_child(tree, envi, exec);
	if (ft_nopipe_end_util(tree, pid, status) == 33)
		return (33);
	ft_close_fd(exec->fd_in);
	return (0);
}

//	check for export, cd, unset, exit
int	ft_start_builtin(t_tree *tree, t_env *envi, t_exec *exec)
{
	if (!ft_strncmp(tree->data[0], "export", 7) && tree->data[1])
	{
		envi->exitcode = ms_export(tree->data, envi);
		exec->builtin_check = 1;
	}
	else if (!ft_strncmp(tree->data[0], "cd", 3))
	{
		envi->exitcode = ms_cd(tree->data, envi);
		exec->builtin_check = 1;
	}
	else if (!ft_strncmp(tree->data[0], "unset", 6))
	{
		envi->exitcode = ms_unset(tree->data, envi);
		exec->builtin_check = 1;
	}
	else if (!ft_strncmp(tree->data[0], "exit", 5))
	{
		envi->exitcode = ft_exit(tree, envi, exec);
		exec->builtin_check = 1;
	}
	return (0);
}

//	if command and no data to write, return
int	ft_check_nonwriteable(t_tree *tree, t_env *envi, t_exec *exec)
{
	exec->builtin_check = 0;
	while (tree)
	{
		if (tree->type == CMD)
		{
			if (!tree->data[0])
				break ;
			ft_start_builtin(tree, envi, exec);
			break ;
		}
		tree = get_next_node(tree);
	}
	return (0);
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
		{
			if (!tree->data[0] || !ft_strncmp(tree->data[0], "", 1))
				free_envi(envi, 0);
			ft_check_builtin(tree, envi);
			ft_get_paths(envi, tree->data);
		}
	}
	ft_check_nonwriteable(tree, envi, exec);
	return (0);
}
