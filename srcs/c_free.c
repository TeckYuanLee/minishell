#include "minishell.h"

//	free env variables
void	free_envi(t_env *envi, int exitcode)
{
	clean_tree(envi->loc_tree_ptr);
	free(envi->exec);
	ft_free_split(&envi->var);
	free_envp(envi->ms_envp);
	close(0);
	close(1);
	if (exitcode != -100)
		exit(exitcode);
}

//	free whatever malloc up to the failed one /////
void	ft_free_partial_split(char ***split, int failed_i)
{
	int	i;

	i = 0;
	while (i < failed_i)
		free((*split)[i++]);
	free(*split);
	*split = NULL;
}

//	simply free string /////
void	ft_free_str(char **str)
{
	if (!*str)
		return ;
	free(*str);
	*str = NULL;
}

//	/////
void	ft_free_split(char ***split)
{
	int	i;

	i = -1;
	if (!*split)
		return ;
	while ((*split)[++i])
	{
		free((*split)[i]);
		(*split)[i] = NULL;
	}
	free(*split);
	*split = NULL;
}