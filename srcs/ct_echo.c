#include "minishell.h"

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
		ret = ft_check_n(tree->data[i]);
		if (ret)
			break ;
		i++;
	}
	err = ft_print_echo(tree, i, err);
	if (err == -1)
		return (err);
	if (!check)
		err = write(STDOUT_FILENO, "\n", 1);
	// printf("yo\n");
	return (err);
}

//	execute echo command
int	ft_builtin_echo(t_env *envi, t_tree *tree)
{
	int	i;
	int	check;
	int	err;

	i = 1;
	check = 0;
	err = 0;
	err = ft_handle_echo(tree, i, check, err);
	// printf("yo\n");
	if (err == -1)
	{
		ft_putstr_fd("minishell: error in echo.\n", 2);
		envi->exitcode = 1;
	}
	else
		envi->exitcode = 0;
	return (1);
}
