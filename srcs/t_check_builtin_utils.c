#include "minishell.h"

//	get path from env
char	*get_path_env(char *temp)
{
	char	*path;

	path = ft_strtrim(temp, "PATH=");
	free (temp);
	if (!path)
		return (NULL);
	return (path);
}

//	print env error message
int	env_error_msg( t_envi *envi)
{
	(void)envi;
	ft_putstr_fd("minishell: env", 2);
	ft_putstr_fd(": argument(s) unsupported\n", 2);
	ft_putstr_fd("env: usage: env\n", 2);
	exit (1);
}

//	print all env values retrieved by minishell
int	ms_env(char **argv, t_envi *envi)
{
	t_ms_envp	*ms_envp;

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

//	get pwd from env
char	*ft_get_pwd_env(char *temp)
{
	char	*cwd;

	cwd = ft_strtrim(temp, "PWD=");
	free (temp);
	if (!cwd)
		return (NULL);
	return (cwd);
}

//	look for pwd from list of envp
char	*ft_get_pwd(char **envp)
{
	int		i;
	int		len;
	char	*temp;
	char	*cwd;

	i = 0;
	while (envp[i] != NULL)
	{
		if (!ft_strncmp(envp[i], "PWD", 3))
		{
			len = ft_strlen(envp[i]);
			temp = (char *)malloc(sizeof(char) * (len + 1));
			if (!temp)
				return (NULL);
			temp = ft_memcpy(temp, envp[i], ft_strlen(envp[i]));
			temp[len] = '\0';
			cwd = ft_get_pwd_env(temp);
			if (!cwd)
				return (NULL);
			return (cwd);
		}
		i++;
	}
	return (NULL);
}

//	check for the char 'n'
int	ft_check_n(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i + 1])
	{
		if (str[i + 1] != 'n')
			return (1);
		i++;
	}
	return (0);
}

//	echo readline
int	ft_print_echo(t_tree *tree, int i, int err)
{
	int	j;

	while (tree->data[i])
	{
		j = ft_strlen(tree->data[i]);
		err = write(STDOUT_FILENO, tree->data[i], j);
		if (tree->data[i + 1] && err != -1)
			err = write(STDOUT_FILENO, " ", 1);
		if (err == -1)
			return (err);
		i++;
	}
	return (err);
}

//	check if there is '-n' for echo
int	ft_handle_echo(t_tree *tree, int i, int check, int err)
{
	int	ret;

	ret = 0;
	while (tree->data[i] && !(ft_strncmp(tree->data[i], "-n", 2)) && err == 0)
	{
		check++;
		ret = ft_check_n(tree->data[i++]);
		if (ret)
			break ;
	}
	err = ft_print_echo(tree, i, err);
	if (err == -1)
		return (err);
	if (!check)
		err = write(STDOUT_FILENO, "\n", 1);
	return (err);
}
