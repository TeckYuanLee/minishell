#include "minishell.h"

//	print error message for unset
int	unset_error_msg(char *str)
{
	if (str[0] == '-' && str[1] != '\0')
	{
		ft_putstr_fd("minishell: unset: -", 2);
		ft_putchar_fd(str[1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		ft_putstr_fd("unset: usage: unset [name ...]\n", 2);
		return (2);
	}
	ft_putstr_fd("minishell: unset: '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

//	print error message for export command
int	export_error_msg(char *str)
{
	if (str[0] == '-' && str[1] != '\0')
	{
		ft_putstr_fd("minishell: export: -", 2);
		ft_putchar_fd(str[1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		ft_putstr_fd("export: usage: export [name[=value] ...]\n", 2);
		return (2);
	}
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

//	execute perror
int	ms_perror(char *perror_str, char *string, char *string2, int rv)
{
	char	*temp;
	char	*temp2;

	if (perror_str)
	{
		if (string)
		{
			temp = ft_strjoin(perror_str, ": ");
			if (!temp)
				return (-1);
			temp2 = ft_strjoin(temp, string);
			free(temp);
			if (!temp2)
				return (-1);
			if (string2)
				return (add_string2(temp2, string2, rv));
			perror(temp2);
			free(temp2);
		}
		else
			perror(perror_str);
	}
	return (rv);
}

//	print env error message
int	env_error_msg( t_env *envi)
{
	(void)envi;
	ft_putstr_fd("minishell: env", 2);
	ft_putstr_fd(": argument(s) unsupported\n", 2);
	ft_putstr_fd("env: usage: env\n", 2);
	exit (1);
}

//	file inwards redirection error
int	ft_redir_in_error(t_tree *tree, t_env *envi)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(tree->data[0], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	free_envi(envi);
	exit(1);
	return (-1);
}

//	lnr angles usage error message
int	ft_redir_error(t_tree *tree, int fd, t_env *envi)
{
	close(fd);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(tree->data[0], 2);
	ft_putstr_fd(": Permission denied\n", 2);
	free_envi(envi);
	exit(1);
	return (-1);
}

//	function execution error message
int	ft_error_exec(int code, int *fd, t_env *envi)
{
	if (fd != 0)
		close(*fd);
	free_envi(envi);
	ft_putstr_fd("minishell: ", 2);
	if (code == 1)
		ft_putstr_fd("fork error\n", 2);
	else if (code == 3)
		ft_putstr_fd("pipe error\n", 2);
	if (code >= 1 && code <= 3)
		exit(71);
	if (code == 4)
	{
		ft_putstr_fd("execve error\n", 2);
		exit(126);
	}
	else if (code == 5)
		ft_putstr_fd("malloc error\n", 2);
	else if (code == 6)
		ft_putstr_fd("acces error\n", 2);
	exit(1);
	return (-1);
}
