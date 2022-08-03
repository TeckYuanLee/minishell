#include "minishell.h"

static t_bool	delimiter_found(char *delimiter, char *line)
{
	if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
		return (TRUE);
	return (FALSE);
}

int	make_here_doc(char *delimiter)
{
	int		fd;
	char	*line;

	fd = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		else if (delimiter_found(delimiter, line))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	return (open(".here_doc", O_RDONLY));
}

//	free env variables
void	free_envi(t_env *envi)
{
	clean_tree(envi->loc_tree_ptr);
	free(envi->exec);
	ft_free_split(&envi->var);
	free_envp(envi->ms_envp);
	close(0);
	close(1);
}
