#include "minishell.h"

int	ft_check_builtin_end(t_tree *tree, t_envi *envi, int i)
{
	if (!ft_strncmp(tree->data[0], "env", 4))
	{
		envi->exitcode = ms_env(tree->data, envi);
		i++;
	}
	if (i != 0)
	{
		free_envi(envi);
		exit(envi->exitcode);
	}
	return (i);
}

void	ft_check_export(t_tree *tree, t_envi *envi)
{
	int	exit_code;

	if (!ft_strncmp(tree->data[0], "export", 7) && tree->data[1])
	{
		free_envi(envi);
		exit(0);
	}
	else if (!ft_strncmp(tree->data[0], "export", 7))
	{
		exit_code = ms_export(tree->data, envi);
		free_envi(envi);
		exit(exit_code);
	}
}

int	ft_pwd_builtin(t_envi *envi)
{
	char	*pwd;

	pwd = ft_get_pwd(envi->var);
	if (!pwd)
		ft_error_exec(5, 0, envi);
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
	free (pwd);
	envi->exitcode = 0;
	return (1);
}

int	ft_builtin_echo(t_envi *envi, t_tree *tree)
{
	int	i;
	int	check;
	int	err;

	i = 1;
	check = 0;
	err = 0;
	err = ft_handle_echo(tree, i, check, err);
	if (err == -1)
	{
		ft_putstr_fd("minishell: error in echo.\n", 2);
		envi->exitcode = 1;
	}
	else
		envi->exitcode = 0;
	return (1);
}

int	ft_check_builtin(t_tree *tree, t_envi *envi)
{
	int	i;

	i = 0;
	if (!ft_strncmp(tree->data[0], "echo", 5))
		i = ft_builtin_echo(envi, tree);
	else if (!ft_strncmp(tree->data[0], "cd", 3) || \
		!ft_strncmp(tree->data[0], "exit", 5))
	{
		free_envi(envi);
		exit(0);
	}
	else if (!ft_strncmp(tree->data[0], "pwd", 4))
		i = ft_pwd_builtin(envi);
	ft_check_export(tree, envi);
	if (!ft_strncmp(tree->data[0], "unset", 6))
		i = 33;
	i = ft_check_builtin_end(tree, envi, i);
	return (i);
}
