#include "minishell.h"

//	handle exit command
int	ft_exit(t_tree *tree, t_env *envi, t_exec *exec)
{
	int	i;

	i = 0;
	while (tree->data[i])
		i++;
	if (!ft_strncmp(tree->data[0], "exit", 5) && i == 1)
	{
		ft_putstr_fd("exit\n", 2);
		envi->exitcode = 0;
		ft_exit_free(tree, exec, envi);
		exit(envi->exitcode);
	}
	ft_exit_multi_arg(tree, envi, i, exec);
	ft_exit_one_arg(tree, envi, i, exec);
	return (envi->exitcode);
}

//	handle unset command
int	ms_unset(char **argv, t_env *envi)
{
	int	i;
	int	exitcode;

	if (!argv)
		return (printf(BHRED "[ms_unset] NULL-pointing argv..\n" BHWHT));
	if (!argv[1])
		return (0);
	exitcode = 0;
	i = 1;
	while (argv[i])
	{
		if (!ft_strncmp(argv[i], "PWD", 4))
			return (0);
		else if (!is_unset_key(argv[i]))
			exitcode = unset_error_msg(argv[i]);
		else
			rm_from_envp(argv[i], &envi->ms_envp);
		i++;
	}
	if (ms_envp_to_var(envi->ms_envp, &envi->var) == MALLOC_FAIL)
		return (-1);
	return (exitcode);
}

//	handle cd command
t_err	ms_cd(char **argv, t_env *envi)
{
	if (!argv)
		return (printf(BHRED "[ms_cd] NULL-pointing argv..\n" BHWHT));
	if (!*argv)
		return (printf(BHRED "[ms_cd] empty argv..\n" BHWHT));
	if (!argv[1])
		return (0);
	if (chdir(argv[1]))
		return (ms_perror("Minishell: cd", argv[1], NULL, 1));
	if (update_pwd_oldpwd(argv[1], envi) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	if (ms_envp_to_var(envi->ms_envp, &envi->var) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	return (NO_ERROR);
}

//	handle export command
int	ms_export(char **argv, t_env *envi)
{
	int		i;
	char	*key;
	int		exitcode;

	if (!argv[1])
		return (single_export(envi->ms_envp));
	exitcode = 0;
	i = 1;
	while (argv[i])
	{
		if (export_get_env_key(argv[i], &key) == MALLOC_FAIL)
			return (-1);
		if (!is_export_key(key))
		{
			ft_free_str(&key);
			exitcode = export_error_msg(argv[i]);
		}
		else
			parse_and_add_to_envp(argv[i], &envi->ms_envp, key);
		i++;
	}
	if (ms_envp_to_var(envi->ms_envp, &envi->var) == MALLOC_FAIL)
		return (-1);
	return (exitcode);
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

//	restore sigint and sigquit to default
void	restore_signals(void)
{
	struct sigaction	sig;

	ft_bzero(&sig, sizeof(struct sigaction));
	sig.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
}

//	process sigint and sigquit
void	process_signal(int sig, int *exitcode, int fd[2])
{
	if (sig == SIGINT)
	{
		if (fd)
			ft_close_fd(fd);
		*exitcode = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	else if (sig == SIGQUIT)
	{
		if (fd)
			ft_close_fd(fd);
		*exitcode = 131;
		ft_putstr_fd("Quit: 3\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}
