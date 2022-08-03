#include "minishell.h"

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