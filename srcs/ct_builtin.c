#include "minishell.h"

//	check for child process's builtin
int	ft_check_builtin_child(t_tree *tree, t_env *envi, t_exec *exec)
{
	int	i;

	i = 0;
	if (!ft_strncmp(tree->data[0], "echo", 4))
		i = ft_builtin_echo(envi, tree);
	else if (!ft_strncmp(tree->data[0], "cd", 3))
	{
		envi->exitcode = ms_cd(tree->data, envi);
		i++;
	}
	i = ft_check_builtin_add(tree, envi, i);
	if (!ft_strncmp(tree->data[0], "exit", 5))
	{
		envi->exitcode = ft_exit(tree, envi, exec);
		i++;
	}
	if (i != 0)
	{
		free_envi(envi);
		exit(envi->exitcode);
	}
	else
		return (i);
}

//	print all env values retrieved by minishell
int	ms_env(char **argv, t_env *envi)
{
	t_item	*ms_envp;

	if (argv[1])
	{
		free_envi(envi);
		env_error_msg(envi);
	}
	ms_envp = envi->ms_envp;
	while (ms_envp->key)
	{
		if (ms_envp->value)
			printf("%s=%s\n", ms_envp->key, ms_envp->value);
		ms_envp++;
	}
	return (0);
}

int	ft_check_builtin_add(t_tree *tree, t_env *envi, int i)
{
	if (!ft_strncmp(tree->data[0], "pwd", 4))
		i = ft_pwd_builtin(envi);
	else if (!ft_strncmp(tree->data[0], "export", 6))
	{
		envi->exitcode = ms_export(tree->data, envi);
		i++;
	}
	else if (!ft_strncmp(tree->data[0], "unset", 6))
	{
		envi->exitcode = ms_unset(tree->data, envi);
		i++;
	}
	else if (!ft_strncmp(tree->data[0], "env", 4))
	{
		envi->exitcode = ms_env(tree->data, envi);
		i++;
	}
	return (i);
}

//	when builtin command is at the end of readline
int	ft_check_builtin_end(t_tree *tree, t_env *envi, int i)
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

//	check for builtin commands
int	ft_check_builtin(t_tree *tree, t_env *envi)
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
